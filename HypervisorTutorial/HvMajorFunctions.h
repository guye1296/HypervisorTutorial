#pragma once

#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>

#include "Utilities.h"


// Following functions must have C linkage
extern "C"
{
DRIVER_DISPATCH hvDefaultIrpHandler;
DRIVER_DISPATCH hvReadIrpHandler;
DRIVER_DISPATCH hvWriteIrpHandler;
DRIVER_DISPATCH hvCloseIrpHandler;
DRIVER_DISPATCH hvCreateIrpHandler;
DRIVER_DISPATCH hvDeviceControlIrpHandler;
}


#pragma alloc_text(PAGE, hvDefaultIrpHandler)
#pragma alloc_text(PAGE, hvCreateIrpHandler)
#pragma alloc_text(PAGE, hvWriteIrpHandler)
#pragma alloc_text(PAGE, hvReadIrpHandler)
#pragma alloc_text(PAGE, hvCloseIrpHandler)
#pragma alloc_text(PAGE, hvDeviceControlIrpHandler)

