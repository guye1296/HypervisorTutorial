#include "Utilities.h"

VOID printBuffer(
	_In_reads_(length) PVOID buffer,
	IN size_t length
)
{
	DbgPrint("0x");
	for (size_t i = 0; i < length; ++i) {
		DbgPrint("%02x", (reinterpret_cast<UINT8*>(buffer))[i]);
	}
	DbgPrint("\n");
}