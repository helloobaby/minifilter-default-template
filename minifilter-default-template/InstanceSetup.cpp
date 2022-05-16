#include"minifilter.h"

namespace minifilter {

    NTSTATUS InstanceSetup(
        _In_ PCFLT_RELATED_OBJECTS FltObjects,
        _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
        _In_ DEVICE_TYPE VolumeDeviceType,
        _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
    ) {

        PAGED_CODE();
        return STATUS_SUCCESS;
    }


}