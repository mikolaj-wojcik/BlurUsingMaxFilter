#pragma once

#include <cstddef>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <math.h>
#include "bmpStruct.h"


class ImageHandling
{
	int32_t width;
	int32_t height;
	std::string inputPath;
	std::string outputPath = "out.bmp";
	std::byte* pixelArray = nullptr;
	std::byte* outputArray = nullptr;
	//Can hold values between 0(darkest) - 1000(brighest)
	int32_t* brightnessArray = nullptr;
	int numberOfThreads =1;
	int ray;

	bmpFileHeader tempHead;
	bmpInfoHeader tempInfo;

	void clearBrightArray();

	void clearArray();

	void clearOutputArray();

	void threadedBrightness(int32_t* brightArray,int startRow, int endRow);

	double singleColorPixelBightness(std::byte color);

	double singlePixelBightness(std::byte blue, std::byte green, std::byte red);


	int32_t* calculateBrightness();

	void libFunction(std::byte* inputArr, std::byte* outputArr, int32_t* brightArr, int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo, int32_t startRow, int32_t fRay);

public:

	ImageHandling(){}

	~ImageHandling() {
		clearArray();
		clearBrightArray();
	}

	
	void callLibFunction();
	void setPath(std::string);
	void loadImage();
	void saveImage();
	void setNumberOfThreads(int num);
};

