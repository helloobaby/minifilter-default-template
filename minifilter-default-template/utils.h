#include"minifilter.h"

#include<ntstrsafe.h>

namespace utils {

	//
	//校验文件对象指针是否合法
	//

	__inline
	bool IsValidFileObjectPointer(PFILE_OBJECT p) {

		if (!p)
			return false;

		if (p->Type != 5)
			return false;

		if (RtlValidateUnicodeString(0, &p->FileName) == STATUS_INVALID_PARAMETER)
			return false;

		return true;

	}

	//
	// 从FltObjects中获得文件名(可以修改,因为是另外分配的缓冲区)
	// 用完后要释放内存
	// 缓冲区以空字符结尾
	//

	__inline
	WCHAR* ExtractFileNameFromFltObjects(PCFLT_RELATED_OBJECTS FltObjects) {
		if (!IsValidFileObjectPointer(FltObjects->FileObject))
			return nullptr;
		WCHAR* filebuf = (WCHAR*)ExAllocatePoolWithTag(NonPagedPool, FltObjects->FileObject->FileName.Length+2, 'litu');
		filebuf[FltObjects->FileObject->FileName.Length / 2] = L'\0';
		memcpy(filebuf, FltObjects->FileObject->FileName.Buffer, FltObjects->FileObject->FileName.Length);
		return filebuf;
	}







}