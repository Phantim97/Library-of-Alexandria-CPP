#include <iostream>
#include <string>

struct Image
{
	virtual void Draw() = 0;
};

struct Bitmap : Image
{
	Bitmap(const std::string &filename)
	{
		std::cout << "Loading bitmap from " << filename << '\n';
	}

	void Draw() override
	{
		std::cout << "Drawing bitmap\n";
	}
};

struct LazyBitmap : Image
{
private:
	std::string filename;
	Bitmap *bmp = nullptr;

public:
	LazyBitmap(const std::string &filename) : filename(filename)
	{
	}

	~LazyBitmap()
	{
		delete bmp;
	}

	void Draw() override
	{
		if (!bmp)
		{
			bmp = new Bitmap(filename);
		}

		bmp->Draw();
	}
};

int main()
{
	LazyBitmap bmp {"test.png"};
	bmp.Draw();
	return 0;
}