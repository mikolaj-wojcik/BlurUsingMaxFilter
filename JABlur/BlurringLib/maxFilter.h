#pragma once

#include "paramsStruct.h"

#ifdef MAXFILTERLIBRARY_EXPORTS
#define MAXFILTERLIBRARY_API __declspec(dllexport)
#else
#define MAXFILTERLIBRARY_API __declspec(dllimport)
#endif



extern "C" MAXFILTERLIBRARY_API void maxFilter(
    parametersStruct p,
    std::byte* inputArr, std::byte* outputArr, int16_t* brightArr
    );