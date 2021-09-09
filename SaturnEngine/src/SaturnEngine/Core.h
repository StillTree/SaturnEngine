#pragma once

#ifdef _WIN64
#ifdef SATURN_DLL
#define SATURN_API _declspec(dllexport)
#else
#define SATURN_API _declspec(dllimport)
#endif
#else
#error Saturn Engine currently supports only Windows!
#endif