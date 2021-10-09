#pragma once

#include <cstdint>

class Bitmap
	{
	private:
		int m_width{ 0 };//C++11 allows for initializing private variables to a default value here
		int m_height{ 0 };
		std::unique_ptr<uint8_t[]> m_pPixels{ nullptr }; //uint8_t is alternative to unsigned char set to null also

	public:
		Bitmap(int width, int height);
		virtual ~Bitmap();

		bool write(std::string filename);
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t);
	};
