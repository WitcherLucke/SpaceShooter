unsigned int PixelBlend(unsigned int d, unsigned int s)
{
	const unsigned int a = (255 - (s >> 24)) + 1;
	const unsigned int dstrb = d & 0xFF00FF;
	const unsigned int dstg = d & 0xFF00;
	const unsigned int srcrb = s & 0xFF00FF;
	const unsigned int srcg = s & 0xFF00;
	unsigned int drb = srcrb - dstrb;
	unsigned int dg = srcg - dstg;
	drb *= a;
	dg *= a;
	drb >>= 8;
	dg >>= 8;
	unsigned int rb = (drb + dstrb) & 0xFF00FF;
	unsigned int g = (dg + dstg) & 0xFF00;
	d = rb | g;
	return d;
}

void DrawTransBitmapTiled(unsigned int*dest, unsigned int*src,
	int destX, int destY,
	int destWidth, int destHeight,
	int srcWidth, int srcHeight)
{
	for (int j = 0; j<srcHeight; j++)
		for (int i = 0; i<srcWidth; i++)
		{
			int fdestX = (destX + i) % destWidth;
			int fdestY = (destY + j) % destHeight;
			unsigned int&destRef = dest[fdestY*destWidth + fdestX];
			unsigned int&srcRef = src[j*srcWidth + i];
			int A = getA(srcRef);
			int destR = getR(destRef);
			int destG = getG(destRef);
			int destB = getB(destRef);
			int srcR = getR(srcRef);
			int srcG = getG(srcRef);
			int srcB = getB(srcRef);
			int R = (destR*A + srcR * (255 - A)) / 255;
			int G = (destG*A + srcG * (255 - A)) / 255;
			int B = (destB*A + srcB * (255 - A)) / 255;
			destRef = rgb(R, G, B);
		}
}

void DrawTransBitmap(unsigned int*dest, unsigned int*src,
	int destX, int destY,
	int destWidth, int destHeight,
	int srcWidth, int srcHeight)
{
	//return;
	if ((destX + srcWidth<destWidth) && (destY + srcHeight<destHeight) && (destX >= 0) && (destY >= 0))
		for (int j = 0; j < srcHeight; j++)
		{
			int addrDest = (destY + j)*destWidth + (destX + 0);
			int addrSrc = j * srcWidth + 0;
			for (int i = 0; i<srcWidth; i++)
			{
				unsigned int&destRef = dest[addrDest + i];
				unsigned int&srcRef = src[addrSrc + i];
				destRef = PixelBlend(destRef, srcRef);
			}
		}
	else
		for (int j = 0; j<srcHeight; j++)
		{
			int addrDest = (destY + j)*destWidth + (destX + 0);
			int addrSrc = j * srcWidth + 0;
			for (int i = 0; i<srcWidth; i++)
				if ((destX + i<destWidth) && (destY + j<destHeight) && (destX + i >= 0) && (destY + j >= 0))
				{
					unsigned int&destRef = dest[addrDest + i];
					unsigned int&srcRef = src[addrSrc + i];
					destRef = PixelBlend(destRef, srcRef);
				}
		}
}

void DrawTransBitmapEnemyDead(unsigned int*dest, unsigned int*src,
	int destX, int destY,
	int destWidth, int destHeight,
	int srcWidth, int srcHeight)
{
	for (int j = 0; j<srcHeight; j++)
		for (int i = 0; i<srcWidth; i++)
			if ((destX + i<destWidth) && (destY + j<destHeight) && (destX + i >= 0) && (destY + j >= 0))
			{
				unsigned int&destRef = dest[(destY + j)*destWidth + (destX + i)];
				unsigned int&srcRef = src[j*srcWidth + i];
				int A = 255 - (255 - getA(srcRef)) / 2;
				int destR = getR(destRef);
				int destG = getG(destRef);
				int destB = getB(destRef);
				int srcR = getR(srcRef);
				int srcG = getG(srcRef);
				int srcB = getB(srcRef);
				srcR = srcG = srcB = (srcR + srcG + srcB) / 3;
				int R = (destR*A + srcR * (255 - A)) >> 8;
				int G = (destG*A + srcG * (255 - A)) >> 8;
				int B = (destB*A + srcB * (255 - A)) >> 8;
				destRef = rgb(R, G, B);
			}
}

void DrawBitmap(unsigned int*dest, unsigned int*src,
	int destX, int destY,
	int destWidth, int destHeight,
	int srcWidth, int srcHeight)
{
	for (int j = 0; j<srcHeight; j++)
		for (int i = 0; i<srcWidth; i++)
			if ((destX + i<destWidth) && (destY + j<destHeight) && (destX + i >= 0) && (destY + j >= 0))
				dest[(destY + j)*destWidth + (destX + i)] = src[j*srcWidth + i];
}

void DrawSprite(unsigned int*dest, unsigned int*src,
	int destX, int destY,
	int destWidth, int destHeight,
	int srcWidth, int srcHeight)
{
	for (int j = 0; j<srcHeight; j++)
		for (int i = 0; i<srcWidth; i++)
			if ((destX + i<destWidth) && (destY + j<destHeight) && (destX + i >= 0) && (destY + j >= 0) && src[j*srcWidth + i] != rgbUpperClamped(255, 255, 255))
				dest[(destY + j)*destWidth + (destX + i)] = src[j*srcWidth + i];
}

void Bitmap::Draw(int x, int y, Bitmap&bmp)
{
	DrawTransBitmap(Pixels, bmp.Pixels, x, y, Width, Height, bmp.Width, bmp.Height);
}
void Bitmap::DrawCentered(int x, int y, Bitmap&bmp)
{
	Draw(x - bmp.Width / 2, y - bmp.Height / 2, bmp);
}
void Bitmap::DrawDead(int x, int y, Bitmap&bmp)
{
	DrawTransBitmapEnemyDead(Pixels, bmp.Pixels, x - bmp.Width / 2, y - bmp.Height / 2,
		Width, Height, bmp.Width, bmp.Height);
}

void Bitmap::FastDraw(int x, int y, Bitmap&Bmp)
{
	int target_start_y = y;
	int target_end_y = y + Bmp.Height;
	int target_start_x = x;
	int target_end_x = x + Bmp.Width;
	int source_start_y = 0;
	int source_start_x = 0;
	if (target_start_y<0) { source_start_y -= target_start_y; target_start_y = 0; }
	if (target_end_y>Height) target_end_y = Height;
	if (target_start_x<0) { source_start_x -= target_start_x; target_start_x = 0; }
	if (target_end_x>Width) target_end_x = Width;
	int scanline_len = (target_end_x - target_start_x) * 4;
	if (scanline_len>0)
		for (int j = target_start_y; j<target_end_y; j++)
		{
			memcpy(&Pixels[j*Width + target_start_x],
				&Bmp.Pixels[source_start_y*Bmp.Width + source_start_x], scanline_len);
			source_start_y++;
		}
}