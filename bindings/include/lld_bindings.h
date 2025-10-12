#pragma once

#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef uint8_t u8;
typedef uint64_t u64;

#ifndef BUSTER_EXTERN_C
#if defined (__cplusplus)
#define BUSTER_EXTERN_C extern "C"
#else
#define BUSTER_EXTERN_C extern
#endif
#endif

#ifndef BUSTER_STRING
#define BUSTER_STRING
typedef struct str
{
    char* pointer;
    u64 length;
} str;
#endif

typedef struct LLDResult
{
    str stdout_string;
    str stderr_string;
    bool success;
} LLDResult;

typedef u8* LldAllocationFn (void* context, u64 size, u64 alignment);

#define lld_api_args() char* const* argument_pointer, u64 argument_count, bool exit_early, bool disable_output, LldAllocationFn* allocate_fn, void* context
#define lld_api_function_decl(link_name) LLDResult lld_ ## link_name ## _link(lld_api_args())

BUSTER_EXTERN_C lld_api_function_decl(coff);
BUSTER_EXTERN_C lld_api_function_decl(elf);
BUSTER_EXTERN_C lld_api_function_decl(mingw);
BUSTER_EXTERN_C lld_api_function_decl(macho);
BUSTER_EXTERN_C lld_api_function_decl(wasm);
