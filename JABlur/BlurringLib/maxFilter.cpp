#include "pch.h"
#include "MaxFilter.h"





void maxFilter(
	parametersStruct p,
	std::byte* inputArr, std::byte* outputArr, int16_t* brightArr) {
	int fRay =(int32_t) p.ray;
	int startRow = (int32_t)p.startRow;
	int width = (int32_t)p.width;
	int height = (int32_t)p.height;
	int rowsTD = (int32_t)p.rowsToDo;
	int brightestIndex;
	int currentMaxBright;
	for (int h = startRow; h < startRow + rowsTD; h++) {
		for (int w = 0; w < width; w++) {
			brightestIndex = h * width + w;
			currentMaxBright = 0;
			for (int hRay = -fRay; hRay <= fRay; hRay++) {
				if (hRay + h >= height)
					break;
				if (hRay + h >= 0) {
					for (int wRay = -fRay; wRay <= fRay; wRay++) {
						if (wRay + w >= width)
							break;
						if (wRay + w >= 0) {
							if (brightArr[(hRay + h) * width + wRay + w] > currentMaxBright) {
								brightestIndex = (hRay + h) * width + wRay + w;
								currentMaxBright = brightArr[(hRay + h) * width + wRay + w];
							}
						}
					}
				}
			}
			outputArr[(h * width + w) * 3] = inputArr[brightestIndex * 3];
			outputArr[(h * width + w) * 3 + 1] = inputArr[brightestIndex * 3 + 1];
			outputArr[(h * width + w) * 3 + 2] = inputArr[brightestIndex * 3 + 2];
		}
	}
}