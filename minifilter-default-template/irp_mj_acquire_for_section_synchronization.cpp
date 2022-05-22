#include"minifilter.h"

#include"utils.h"
namespace minifilter
{
    namespace irp_mj_acquire_for_section_synchronization {
        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        )
        {
            WCHAR* FileName = utils::GetFileFullPathName(Data, FltObjects);
            if (!FileName)
                return FLT_PREOP_SUCCESS_WITH_CALLBACK;;

            if (wcsstr(FileName, L"sbb")) {
                return FLT_PREOP_COMPLETE;
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
            WCHAR* FileName = utils::GetFileFullPathName(Data,FltObjects);
            if (!FileName)
                return FLT_POSTOP_FINISHED_PROCESSING;

            if (wcsstr(FileName, L"sbb")) {
                dbg::print("FileMapping : %ws\n", FileName);
                return FLT_POSTOP_FINISHED_PROCESSING;
            }

            return FLT_POSTOP_FINISHED_PROCESSING;
        }

    }
}