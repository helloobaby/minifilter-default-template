/*++
    main module file
--*/

#include"minifilter.h"

PFLT_FILTER gFilterHandle;

extern "C"
NTSTATUS
DriverEntry (
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
{
    NTSTATUS status;

    status = FltRegisterFilter( DriverObject,
                                &minifilter::FilterRegistration,
                                &gFilterHandle );

    if (NT_SUCCESS( status )) {

        //
        //  Start filtering i/o
        //

        status = FltStartFiltering( gFilterHandle );

        if (!NT_SUCCESS( status )) {
            dbg::print("FltStartFiltering failed with status %x\n");
            FltUnregisterFilter( gFilterHandle );
            return status;
        }
    }
    else 
    {
        dbg::print("FltRegisterFilter failed with status %x\n",status);
        return status;
    }

#ifdef DBG
    
    dbg::print("minifilter loaded (complied at %s)\n", __TIMESTAMP__);
#endif // DBG

    return status;
}

