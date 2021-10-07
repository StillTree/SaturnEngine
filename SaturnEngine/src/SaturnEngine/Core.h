#pragma once

#ifdef _WIN64
#ifdef _WINDLL
#define SATURN_API _declspec(dllexport)
#else
#define SATURN_API _declspec(dllimport)
#endif
#else
#error Saturn Engine currently supports only Windows x64!
#endif


