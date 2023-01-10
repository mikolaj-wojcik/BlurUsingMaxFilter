#include "pch.h"
#include "MaxFilter.h"




void maxFilterCpp(
    std::byte* inputArr, std::byte* outputArr, int32_t* brightArr,
    int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo,
    int32_t startRow, int32_t fRay) {
	int brightestIndex;
	int currentMaxBright;
	for (int h = startRow; h < startRow + fNumOfRowsToToDo; h++) {
		for (int w = 0; w < fWitdh; w++) {
			brightestIndex = h * fWitdh + w;
			currentMaxBright = 0;
			for (int hRay = -fRay; hRay < fRay; hRay++) {
				if (hRay + h >= 0 && hRay + h < fHeight) {
					for (int wRay = -fRay; wRay < fRay; wRay++) {
						if (wRay + w >= 0 && wRay + w < fWitdh) {
							if (brightArr[(hRay + h) * fWitdh + wRay + w] > currentMaxBright) {
								brightestIndex = (hRay + h) * fWitdh + wRay + w;
								currentMaxBright = brightArr[(hRay + h) * fWitdh + wRay + w];
							}
						}
					}
				}
			}
			outputArr[(h * fWitdh + w) * 3] = inputArr[brightestIndex * 3];
			outputArr[(h * fWitdh + w) * 3 + 1] = inputArr[brightestIndex * 3 + 1];
			outputArr[(h * fWitdh + w) * 3 + 2] = inputArr[brightestIndex * 3 + 2];
		}
	}
}