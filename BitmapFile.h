void LoadPart(unsigned int*src, unsigned int*dest, int srcH, int srcW, int screenHeight, int offset, int ignoreblack)
{
	if (offset<0) offset = srcH - 1 - abs(offset%srcH);
	if (ignoreblack)
	{
		for (int j = 0; j<screenHeight; j++)
			for (int i = 0; i<srcW; i++)
				if (src[(offset + j) % srcH*srcW + i] != rgbUpperClamped(0, 0, 0)) dest[j*srcW + i] = src[(offset + j) % srcH*srcW + i];
	}
	if (!ignoreblack)
	{
		for (int j = 0; j<screenHeight; j++)
			for (int i = 0; i<srcW; i++)
				dest[j*srcW + i] = src[(offset + j) % srcH*srcW + i];
	}
}

unsigned int*LoadBmp(const char*path, int&Width, int&Height)
{
	FILE*f;
	int err = fopen_s(&f, path, "rb");
	if (err) return 0;
	fseek(f, 0x12, SEEK_SET);
	fread(&Width, 4, 1, f);
	fseek(f, 0x16, SEEK_SET);
	fread(&Height, 4, 1, f);
	fseek(f, 0x36, SEEK_SET);
	unsigned int*pixels;
	pixels = (unsigned int*)Malloc(Width*Height * sizeof(int));
	for (int j = Height - 1; j >= 0; j--)
	{
		for (int i = 0; i<Width; i++)
		{
			pixels[j*Width + i] = rgb(fgetc(f), fgetc(f), fgetc(f));
		}
		int k = Width * 3;
		while (k % 4) { fgetc(f); k++; }
	}
	fclose(f);
	return pixels;
}

void Bitmap::Load(const char*path)
{
	Pixels = LoadBmp(path, Width, Height);
}

void Bitmap::Load(const char*path, const char*alphaPath)
{
	int alphaWidth, alphaHeight;
	unsigned int*alphaPixels = LoadBmp(alphaPath, alphaWidth, alphaHeight);
	Load(path);
	for (int i = 0; i<min(Width*Height, alphaWidth*alphaHeight); i++)
	{
		Pixels[i] = ARGB(getRGB(Pixels[i]), 255 - getL(alphaPixels[i]));
	}
	Free(alphaPixels);
}

Bitmap::Bitmap(const char*path) { Init(); Load(path); }

Bitmap::Bitmap(const char*path, const char*alphaPath)
{
	Init(); Load(path, alphaPath);
}
Bitmap::Bitmap(int Width, int Height) { Init(); Load(Width, Height); }