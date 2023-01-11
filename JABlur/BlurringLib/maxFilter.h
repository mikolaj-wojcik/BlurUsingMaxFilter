#pragma once

#include <cstddef>
#include <cstdint>

#ifdef MAXFILTERLIBRARY_EXPORTS
#define MAXFILTERLIBRARY_API __declspec(dllexport)
#else
#define MAXFILTERLIBRARY_API __declspec(dllimport)
#endif



extern "C" MAXFILTERLIBRARY_API void maxFilter(
    std::byte* inputArr, std::byte* outputArr, int32_t* brightArr,
    int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo,
    int32_t startRow, int32_t fRay);