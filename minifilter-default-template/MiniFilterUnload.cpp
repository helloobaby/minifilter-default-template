#include"minifilter.h"

namespace minifilter {
    NTSTATUS Unload(
        _In_ FLT_FILTER_UNLOAD_FLAGS Flags
    ) {
        PAGED_CODE();
        FltUnregisterFilter(gFilterHandle);
        return STATUS_SUCCESS;
    }
}