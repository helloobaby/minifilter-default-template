#include"minifilter.h"

#include"utils.h"
namespace minifilter
{
    namespace irp_read {
        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        )
        {
            WCHAR* FileName = utils::ExtractFileNameFromFltObjects(FltObjects);
            CALL_ONCE_START;
            dbg::print("Read File %ws\n", FileName);
            dbg::print("[-]%ws\n",utils::GetFileFullPathName(Data));
            CALL_ONCE_END;
            FileName = _wcslwr(FileName);


            if (wcsstr(FileName, L"sbb.txt")) {
                
                dbg::print("FileObject : 0x%p\n",FltObjects->FileObject);

                return FLT_PREOP_SUCCESS_WITH_CALLBACK;
            }
            return FLT_PREOP_SUCCESS_WITH_CALLBACK;
        }
        FLT_POSTOP_CALLBACK_STATUS
            PostOperation( 
                _Inout_ PFLT_CALLBACK_DATA Data,
                _In_ PCFLT_RELATED_OBJECTS FltObjects,
                _In_opt_ PVOID CompletionContext,
                _In_ FLT_POST_OPERATION_FLAGS Flags
            )
        {
            return FLT_POSTOP_FINISHED_PROCESSING;
        }

    }
}