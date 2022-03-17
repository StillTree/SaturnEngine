#pragma once

// Macros for easier __declspec use

#ifdef ST_WINDOWS
#ifdef ST_BUILD_SHARED
#ifdef ST_LIBRARY
#define SATURN_API __declspec(dllexport)
#else
#define SATURN_API __declspec(dllimport)
#endif
#else
#define SATURN_API
#endif
#else
#error Saturn Engine currently supports only Windows!
#endif

//Should be preferred over built-in types just for consistency.

typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef float F32;
typedef double F64;
