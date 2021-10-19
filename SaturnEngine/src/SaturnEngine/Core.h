#pragma once

#ifdef ST_WINDOWS
#ifdef ST_LIBRARY
#define SATURN_API __declspec(dllexport)
#else
#define SATURN_API __declspec(dllimport)
#endif
#else
#error Saturn Engine currently supports only Windows!
#endif