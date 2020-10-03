#pragma once

#include <ntddk.h>


#define UNUSED_PARAMETER(x) do {(void)x;} while(0)


VOID printCharacters(
	_In_reads_(length) PCHAR buffer,
	IN size_t length
);
