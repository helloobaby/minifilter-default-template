#include"minifilter.h"

namespace minifilter {
    
    VOID InstanceTeardownStart(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
        ) {
        PAGED_CODE();
    }

}