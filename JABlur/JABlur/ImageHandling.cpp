#include "ImageHandling.h"


void ImageHandling::loadImage() {
	if (inputPath.empty())
		return;
	std::ifstream f;
	std::ofstream o;
	f.open(inputPath, std::ios::in | std::ios::binary);

	if (!f.is_open()) {
		//return;
	}

	bmpFileHeader fileHead;
	bmpInfoHeader infoHead;

	f.read((char*)&tempHead, sizeof(fileHead));
	f.read((char*)&tempInfo, sizeof(infoHead));

	width = tempInfo.bitmapWidth;
	height = tempInfo.bitmapHeight;

	std::cout << width << "\n" << height;

	clearArray();

	int padding = 4-((width * 3 * sizeof(std::byte)) % 4);
	if (padding == 4)
		padding = 0;
	int rowSize = (width * 3 * sizeof(std::byte)) + padding;
	pixelArray = new std::byte[width * height * 3];
	std::byte* arrForPadding = new std::byte[padding];
	

	f.seekg(tempHead.fileOffset);

	//f.read((char*)pixelArray, tempInfo.imageSize);

	for (long h = 0; h < height; h++) {
		for (long w = 0; w < width; w++) {
			std::byte singlePix[3];
			f.read(reinterpret_cast<char*>(singlePix), 3);
			//std::cout << (int)singlePix[0] << (int)singlePix[1] << (int)singlePix[2];
			pixelArray[(h * width * 3) + w * 3] = singlePix[0];
			pixelArray[(h * width * 3) + w * 3 + 1] = singlePix[1];
			pixelArray[(h * width * 3) + w * 3 + 2] = singlePix[2];
			//f.read((char*)pixelArray[(h * width * 3) + w * 3], 3);
			//f.read((char*)pixelArray[(h * width * 3) + w * 3 + 1], sizeof(std::byte));
			//f.read((char*)pixelArray[(h * width * 3) + w * 3 + 2], sizeof(std::byte));
		}
		f.read((char*)arrForPadding, padding);

	}


	f.close();

	delete arrForPadding;

	clearBrightArray();
	clearOutputArray();
	brightnessArray = calculateBrightness();
	outputArray = new std::byte[height * width * 3];

	//libFunction(pixelArray, outputArray, brightnessArray, width, height, height, 0, 10);
	callCppLibFunction();


	


}



void ImageHandling::saveImage(std::string path = "out.bmp") {

	if (outputArray == nullptr)
		return;
	int padding = 4- ((width * sizeof(std::byte) * 3) % 4);
	if (padding == 4)
		padding = 0;
	unsigned int imgSize = height * sizeof(std::byte) * (width  * 3 + padding);
	uint8_t pad = 0;

	std::ofstream x;

	bmpFileHeader newFileHeader;
	newFileHeader.fileType = 0x4D42;
	newFileHeader.fileSize = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader) + imgSize;
	newFileHeader.fileReserved1 = 0;
	newFileHeader.fileReserved2 = 0;
	newFileHeader.fileOffset = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader);

	bmpInfoHeader infoHeader;
	infoHeader.infoHeaderSize = sizeof(bmpInfoHeader);
	infoHeader.bitmapWidth = width;
	infoHeader.bitmapHeight = height;
	infoHeader.colorPlanes = 1;
	infoHeader.bitsPerPixel = 24;
	infoHeader.compressionMethod = 0;
	infoHeader.imageSize = (int)imgSize; //????????
	infoHeader.horizontalResolution = 0;
	infoHeader.verticalResolution = 0;
	infoHeader.colorNumber = 0;
	infoHeader.importantColor = 0;
	//x.close();

	x.open(path, std::ios::out | std::ios::binary);
	x.write((char*)&newFileHeader, sizeof(bmpFileHeader));
	x.write((char*)&infoHeader, sizeof(bmpInfoHeader));
	//x.write((char*)pixelArray, imgSize);

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			x.write((char*)&outputArray[(h * width * 3) + w * 3], sizeof(std::byte));
			x.write((char*)&outputArray[(h * width * 3) + w * 3 + 1], sizeof(std::byte));
			x.write((char*)&outputArray[(h * width * 3) + w * 3 + 2], sizeof(std::byte));
		}
		x.write((char*)&pad, padding);
	}



	x.close();
}


void ImageHandling::clearBrightArray() {
	if (brightnessArray != nullptr) {
		delete[] brightnessArray;
		brightnessArray = nullptr;
	}
}

void ImageHandling::clearOutputArray() {
	if (outputArray != nullptr) {
		delete[] outputArray;
		outputArray = nullptr;
	}
}

void ImageHandling::clearArray(){
	if (pixelArray != nullptr) {
		delete[] pixelArray;
		pixelArray = nullptr;
	}
}


void ImageHandling::setPath(std::string str){
	inputPath = str;
}


int32_t* ImageHandling::calculateBrightness() {
	if (pixelArray == nullptr) {
		return nullptr;
	}
	int size = width * height;
	int32_t* brightArray = new int32_t[size];

	int extraRowsForLastThread = 0;
	int rowsPerThread = 0;
	int rowsForLastThread = 0;
	if (numberOfThreads > 1) {
		extraRowsForLastThread = height % numberOfThreads;
		rowsPerThread = (height - extraRowsForLastThread) / (numberOfThreads);
		rowsForLastThread = rowsPerThread + extraRowsForLastThread;
	}
	else
		rowsForLastThread = height-1;

	std::vector<std::thread> threads;
	for (int i = 0; i < numberOfThreads - 1; i++) {
		
		threads.push_back(std::thread(&ImageHandling::threadedBrightness, this, brightArray, i * rowsPerThread, (i + 1) * rowsPerThread));
	}
	threads.push_back(std::thread(&ImageHandling::threadedBrightness, this, brightArray, (numberOfThreads - 1) * rowsPerThread, height));

	for (auto& trd : threads) {
		if(trd.joinable())
			trd.join();
	}
	clearBrightArray();
	//brightArray = brightArray;
	return brightArray;
}

void ImageHandling::threadedBrightness(int32_t* brightArray, int startRow, int endRow) {
	int startIndex = startRow * width;
	int endIndex = (endRow-1) * width;

	for (int i = startIndex; i < endIndex; i++) {
		int32_t pixBright = (int)(1000 * singlePixelBightness(pixelArray[3 * i], pixelArray[3 * i + 1], pixelArray[3 * i + 2]));
		brightArray[i] = pixBright;
	}
}


//Jasnoæ nale¿y do przedzia³u od 0 do 1
double ImageHandling::singlePixelBightness(std::byte blue, std::byte green, std::byte red){
	return 0.2126 * singleColorPixelBightness(red) + 0.7152 * singleColorPixelBightness(green) + 0.0722 * singleColorPixelBightness(blue);
}

double ImageHandling::singleColorPixelBightness(std::byte color) {
	double sRGBval = (int)color / 255.0f;
	if (sRGBval <= 0.03928) {
		return sRGBval / 12.98;
	}
	else {
		double valToPow = (sRGBval + 0.055) / 1.055;
		return pow(valToPow, 2.4);
	}
}

void ImageHandling::setNumberOfThreads(int num) {
	numberOfThreads = num;
}


void ImageHandling::callCppLibFunction() {
	typedef int(_stdcall* maxFilter)(std::byte*, std::byte*, int32_t*, int32_t, int32_t, int32_t, int32_t, int32_t);
	HINSTANCE dllHandler = NULL;
	dllHandler = LoadLibrary(L"BlurringLib.dll");
	maxFilter filter = (maxFilter)GetProcAddress(dllHandler, "maxFilterCpp");
	filter(pixelArray, outputArray, brightnessArray, width, height, height, 0, 10);

}















//########
//methodhod to be in library
//output array already initialized
//possible optimalization- break if currentMaxBright == 1000
void ImageHandling::libFunction(std::byte* inputArr, std::byte* outputArr, int32_t* brightArr, int32_t fWitdh, int32_t fHeight, int32_t fNumOfRowsToToDo, int32_t startRow, int32_t fRay) {
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