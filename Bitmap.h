class Bitmap
{
public:
	unsigned int*Pixels;
	int Width, Height;
	int FreePixels;
	void Load(const char*);
	void Load(const char*, const char*);
	void Load(unsigned int*, int, int);
	void Load(int, int);
	unsigned int&GetReference(int x, int y) { return Pixels[y*Width + x]; }
	unsigned int*GetScanline(int y) { return &Pixels[y*Width]; }
	void Draw(int, int, Bitmap&);
	void DrawCentered(int, int, Bitmap&);
	void DrawDead(int, int, Bitmap&);
	void FastDraw(int, int, Bitmap&);
	void WriteText(char*, int, int);
	void Init() { Pixels = 0; FreePixels = 1; }
	void Crop(int, int, int, int);
	void AutoCrop();
	Bitmap() { Init(); }
	Bitmap(const char*);
	Bitmap(const char*, const char*);
	Bitmap(int, int);
	void Release() { if (Pixels&&FreePixels) Free(Pixels); }
	~Bitmap() { Release(); }
};

void Bitmap::Load(unsigned int*Buffer, int Width, int Height)
{
	this->Width = Width; this->Height = Height;
	Pixels = Buffer;
	FreePixels = 0;
}

void Bitmap::Load(int Width, int Height)
{
	this->Width = Width; this->Height = Height;
	Pixels = (unsigned int*)Malloc(Width*Height * 4);
}

// - Crop

void Bitmap::Crop(int x, int y, int width, int height)
{
	Bitmap newBmp(width, height);
	newBmp.FreePixels = 0;
	for (int j = 0; j<height; j++)
		memcpy(newBmp.GetScanline(j), &GetScanline(j + y)[x], width * 4);
	Free(Pixels);
	Pixels = newBmp.Pixels;
	Width = width; Height = height;
}

void Bitmap::AutoCrop()
{
	int maxx = 0;
	int minx = Width - 1;
	int maxy = 0;
	int miny = Height - 1;
	for (int j = 0; j<Height; j++)
		for (int i = 0; i<Width; i++)
			if (getA(GetReference(i, j)) != 255)
			{
				if (i<minx) minx = i;
				if (i>maxx) maxx = i;
				if (j<miny) miny = j;
				if (j>maxy) maxy = j;
			}
	Crop(minx, miny, maxx - minx + 1, maxy - miny + 1);
}

