#pragma once

#include <cstddef>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <math.h>
#include <windows.h>
#include <chrono>
#include "bmpStruct.h"
#include "parametersToAssembly.h"


class ImageHandling
{
	bool libUsed = true;
	int32_t width;
	int32_t height;
	std::string inputPath;
	std::string outputPath = "out.bmp";
	std::byte* pixelArray = nullptr;
	std::byte* outputArray = nullptr;
	//Can hold values between 0(darkest) - 1000(brighest)
	int16_t* brightnessArray = nullptr;
	int numberOfThreads =1;
	int ray =1;

	bmpFileHeader tempHead;
	bmpInfoHeader tempInfo;

	void clearBrightArray();

	void clearArray();

	void clearOutputArray();

	void threadedBrightness(int16_t* brightArray,int startRow, int endRow);

	double singleColorPixelBightness(std::byte color);

	double singlePixelBightness(std::byte blue, std::byte green, std::byte red);


	int16_t* calculateBrightness();

	void libFunction(std::byte* inputArr, std::byte* outputArr, int16_t* brightArr, int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo, int32_t startRow, int32_t fRay);

	void callLibFunction();
	parametersStruct packToStruct(int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo, int32_t startRow, int32_t fRay);
public:

	ImageHandling(){}

	~ImageHandling() {
		clearArray();
		clearBrightArray();
	}

	double run();
	void setPath(std::string);
	bool loadImage();
	void saveImage(std::string);
	void setNumberOfThreads(int num);
	void changeLib(bool newVal);
	void setRay(int fRay);
};

