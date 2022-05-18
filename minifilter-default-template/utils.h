#include"minifilter.h"

#include<ntstrsafe.h>

#define IO_TYPE_FILE                    0x00000005

namespace utils {

	//
	// 将UNICODE_STRING转化为空字符结尾的宽字符串
	// 需要调用者释放内存

	__inline
	WCHAR* UnicodeString2WcharPointer(PUNICODE_STRING us) {
		if (RtlValidateUnicodeString(0,us) == STATUS_INVALID_PARAMETER)
			return nullptr;

		WCHAR* buf = (WCHAR*)ExAllocatePoolWithTag(NonPagedPool, us->Length + 2, 'litu');
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

	__inline WCHAR* GetFileFullPathName(PFLT_CALLBACK_DATA Data){
		NTSTATUS status = STATUS_SUCCESS;
		PFLT_FILE_NAME_INFORMATION NameInfo;
		status = FltGetFileNameInformation(Data,
			FLT_FILE_NAME_OPENED |
			FLT_FILE_NAME_QUERY_DEFAULT,
			&NameInfo);

		if (!NT_SUCCESS(status)) {
			dbg::print("[%s - %s]FltGetFileNameInformation failed with status %x\n",__FILE__,__LINE__, status);
			return nullptr;
		}
		return UnicodeString2WcharPointer(&NameInfo->Name);
	}




}