#pragma once

#include <cstdint>

#ifdef ST_WINDOWS
#ifdef ST_LIBRARY
#define SATURN_API __declspec(dllexport)
#else
#define SATURN_API __declspec(dllimport)
#endif
#else
#error Saturn Engine currently supports only Windows!
#endif

typedef int8_t I8;
typedef int16_t I16;
typedef int32_t I32;
typedef int64_t I64;

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
