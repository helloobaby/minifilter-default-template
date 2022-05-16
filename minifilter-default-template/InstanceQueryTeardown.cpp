#include"minifilter.h"

namespace minifilter {

    NTSTATUS InstanceQueryTeardown(
        _In_ PCFLT_RELATED_OBJECTS FltObjects,
        _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
    )
    {
        PAGED_CODE();
        return STATUS_SUCCESS;
    }

}