#pragma once

//#include <stdint.h>
#include <cstddef>
#include <cstdint>


#pragma pack(1)
struct parametersStruct {
	uint32_t width;
	uint32_t height;
	uint32_t rowsToDo;
	uint32_t ray;
	uint32_t startRow;
};

