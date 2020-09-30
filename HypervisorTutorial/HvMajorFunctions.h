#pragma once

#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>

#include "Utilities.h"


// Following functions must have C linkage
extern "C"
{
// @note: naming is against the convention due to `DriverEntry`
//        being the driver's entry point
DRIVER_DISPATCH hvDefaultIrpHandler;
DRIVER_DISPATCH hvReadIrpHandler;
DRIVER_DISPATCH hvWriteIrpHandler;
DRIVER_DISPATCH hvCloseIrpHandler;
DRIVER_DISPATCH hvCreateIrpHandler;
DRIVER_DISPATCH hvDeviceControlIrpHandler;
}


