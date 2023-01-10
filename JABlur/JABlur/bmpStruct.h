
#pragma once

#include <stdint.h>


#pragma pack(1)
struct bmpFileHeader {
	uint16_t fileType;
	uint32_t fileSize;  
	uint16_t fileReserved1;
	uint16_t fileReserved2;
	uint32_t fileOffset;	
};

#pragma pack(1)
struct bmpInfoHeader {
	uint32_t infoHeaderSize;
	int32_t bitmapWidth;
	int32_t bitmapHeight;
	uint16_t colorPlanes;
	uint16_t bitsPerPixel;
	uint32_t compressionMethod;
	uint32_t imageSize;
	int32_t horizontalResolution;
	int32_t verticalResolution;
	uint32_t colorNumber;
	uint32_t  importantColor;
};

