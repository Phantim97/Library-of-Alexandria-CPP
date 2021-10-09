Bitmap::Bitmap(int width, int height) : m_pPixels(new uint8_t[width * height * 3]{}) // height and width for each color and 3 colors for RGB
	{
		this->m_width = width;
		this->m_height = height;
	}
	Bitmap::~Bitmap()
	{
	}

	bool Bitmap::write(std::string filename)
	{
		BitmapFileHeader fileHeader; 
		BitmapInfoHeader infoHeader;

		//File header contains info about file (needs to take size of everything)
		fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width*m_height * 3;
		fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader); //starts where pixels do and where info ends

		//Info contains info about the bitmap
		infoHeader.width = m_width;
		infoHeader.height = m_height;

		//Creating a binary file
		std::ofstream file;
		file.open(filename, std::ios::out|std::ios::binary);

		if (!file)
		{
			return false;
		}

		//writes to file with a char pointer with also the size of that buffer
		file.write((char *)&fileHeader, sizeof(fileHeader));
		file.write((char *)&infoHeader, sizeof(infoHeader));
		file.write((char *)m_pPixels.get(), m_width * m_height * 3); //.get() to obtain a raw pointer

		file.close();

		//checks if file cannot be closed
		if (!file)
		{
			return false;
		}

		return true;
	}

	void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
	{
		uint8_t *pPixel = m_pPixels.get(); // get the data for the memory block

		//pointer arithmetic
		pPixel += (y*3)*m_width + (x*3);
		//references the bytes of the pixel
		pPixel[0] = blue;
		pPixel[1] = green;
		pPixel[2] = red;
		
	}
