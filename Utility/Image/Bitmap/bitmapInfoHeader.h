#pragma once

#include <cstdint>

#pragma pack(2)

struct BitmapInfoHeader 
{
	int32_t headerSize{ 40 }; //size of struct in bytes
	int32_t width;
	int32_t height;
	int16_t planes{ 1 };
	int16_t bitsPerPixel{ 24 }; //1 byte (8 bits) per color RGB
	int32_t compression{ 0 };
	int32_t dataSize{ 0 };
	int32_t horizontalResolution{ 2400 };
	int32_t verticalResolution{ 2400 };
	int32_t colors{ 0 }; //may not be used
	int32_t importantColors{ 0 }; //may not be used
};
