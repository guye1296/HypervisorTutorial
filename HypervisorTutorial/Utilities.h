#pragma once

#include <ntddk.h>


#define UNUSED_PARAMETER(x) do {(void)x;} while(0)

// preprocessor hacks
#define STRING(x) #x
#define STRINGIFY(x) STRING(x)

#define _DEBUG_TRACE(level, format, ...) DbgPrint("[" #level "] " __FUNCTION__ ":" STRINGIFY(__LINE__) " : " format "\n", ##__VA_ARGS__)
#define DEBUG_TRACE_INFO(format, ...) _DEBUG_TRACE(INFO, format , ##__VA_ARGS__)
#define DEBUG_TRACE_ERROR(format, ...) _DEBUG_TRACE(ERROR, format, ##__VA_ARGS__)

#define HV_ASSERT(expression, message, ...) do { if(!(expression)) DEBUG_TRACE_ERROR(message, ##__VA_ARGS__); } while(0)


VOID printBuffer(
	_In_reads_(length) PVOID buffer,
	IN size_t length
);
