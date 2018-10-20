Bitmap Courier[256];



void alnLoadFonts()
{
	Bitmap courier;
	courier.Load("courier.bmp");
	int width = courier.Width / 256;
	int height = courier.Height;
	for (int i = 0; i<256; i++)
	{
		Courier[i].Load(width, height);
		Courier[i].FastDraw(-width * i, 0, courier);
	}
}

void Bitmap::WriteText(char*text, int x, int y)
{
	while (*text)
	{
		FastDraw(x, y, Courier[*text]);
		x += Courier[*text].Width;
		text++;
	}
}