#include"minifilter.h"

#include<ntstrsafe.h>

namespace utils {

	//
	//У���ļ�����ָ���Ƿ�Ϸ�
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
	// ��FltObjects�л���ļ���(�����޸�,��Ϊ���������Ļ�����)
	// �����Ҫ�ͷ��ڴ�
	// �������Կ��ַ���β
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