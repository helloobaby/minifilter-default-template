#include"minifilter.h"

#include<ntstrsafe.h>

#define IO_TYPE_FILE                    0x00000005

#define UTIL_TAG 'litu'

namespace utils {

	//
	// 将UNICODE_STRING转化为空字符结尾的宽字符串
	// 需要调用者释放内存
	//

	__inline
	WCHAR* UnicodeString2WcharPointer(PUNICODE_STRING us) {
		if (RtlValidateUnicodeString(0, us) == STATUS_INVALID_PARAMETER) {
#ifdef DBG
			dbg::print("RtlValidateUnicodeString failed\n");
#endif
			return nullptr;
		}
		WCHAR* buf = (WCHAR*)ExAllocatePoolWithTag(NonPagedPool, us->Length + 2, UTIL_TAG);
		buf[us->Length / 2] = L'\0';
		memcpy(buf, us->Buffer, us->Length);
		return buf;
	}

	//
	//校验文件对象指针是否合法
	//

	__inline
	bool IsValidFileObjectPointer(PFILE_OBJECT p) {

		if (!p)
			return false;

		if (p->Type != IO_TYPE_FILE)
			return false;

		if (RtlValidateUnicodeString(0, &p->FileName) == STATUS_INVALID_PARAMETER)
			return false;

		return true;

	}

	//
	// 从FltObjects中获得文件名(可以修改,因为是另外分配的缓冲区)
	// 缓冲区以空字符结尾
	// 
	// 用完后要释放内存
	// 得到的路径不包含卷名,也就是(\Device\HarddiskVolumeX)
	//

	__inline
	WCHAR* ExtractFileNameFromFltObjects(PCFLT_RELATED_OBJECTS FltObjects) {
		if (!IsValidFileObjectPointer(FltObjects->FileObject))
			return nullptr;
		
		return UnicodeString2WcharPointer(&FltObjects->FileObject->FileName);
	}


	//
	//FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT
	//FLT_FILE_NAME_OPENED | FLT_FILE_NAME_QUERY_ALWAYS_ALLOW_CACHE_LOOKUP
	//FLT_FILE_NAME_OPENED | FLT_FILE_NAME_QUERY_DEFAULT
	// 
	//http://fsfilters.blogspot.com/2011/04/names-in-minifilters-flags-of.html
	//

	__inline WCHAR* GetFileFullPathName(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects){
		PAGED_CODE(); 

		NTSTATUS status = STATUS_SUCCESS;
		PFLT_FILE_NAME_INFORMATION NameInfo;
		status = FltGetFileNameInformation(Data,
			FLT_FILE_NAME_OPENED |
			FLT_FILE_NAME_QUERY_DEFAULT,
			&NameInfo);

		if (!NT_SUCCESS(status)) {
			UNICODE_STRING VolumeName{};
			UNICODE_STRING usFileName;
			WCHAR* wcFileName{};
			DWORD Size; //VolumeName length
			if (status == STATUS_FLT_INVALID_NAME_REQUEST) {	//再尝试一次从FileObject拿
				status = FltGetVolumeName(FltObjects->Volume, &VolumeName, &Size);
				if (status == STATUS_BUFFER_TOO_SMALL) {

					wcFileName = ExtractFileNameFromFltObjects(FltObjects);

					//
					//给VolumeName字符串分配内存(因为后面要拼接,所以要多分配)
					//+10是随便加的,只要确保缓冲区够就行
					//

					VolumeName.Buffer = (WCHAR*)ExAllocatePoolWithTag(NonPagedPool, Size+wcslen(wcFileName)*2+10,'litu');
					VolumeName.MaximumLength = Size + wcslen(wcFileName)*2+10;
					VolumeName.Length = VolumeName.MaximumLength - sizeof(UNICODE_NULL);

					status = FltGetVolumeName(FltObjects->Volume, &VolumeName, NULL);

					if (NT_SUCCESS(status)) {
						if (wcFileName) {
							RtlInitUnicodeString(&usFileName, wcFileName);
							RtlAppendUnicodeStringToString(&VolumeName, &usFileName);

							WCHAR* t = UnicodeString2WcharPointer(&VolumeName);
							RtlFreeUnicodeString(&VolumeName);
							ExFreePool(wcFileName);
							return t;
						}
					}
				}
			}



#if DBG
			dbg::print("last status %x\n",status);
#endif // DBG
			return nullptr;
		}

		WCHAR* t = UnicodeString2WcharPointer(&NameInfo->Name);
		FltReleaseFileNameInformation(NameInfo);
		return t;
	}





}