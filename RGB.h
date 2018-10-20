unsigned int rgb(int r, int g, int b) { return b | (g << 8) | (r << 16); }

unsigned int getA(unsigned int color) { return (color >> 24) & 0xFF; }
unsigned int getR(unsigned int color) { return (color >> 16) & 0xFF; }
unsigned int getG(unsigned int color) { return (color >> 8) & 0xFF; }
unsigned int getB(unsigned int color) { return color & 0xFF; }
unsigned int getL(unsigned int color) { return (getR(color) + getG(color) + getB(color) + 1) / 3; }
unsigned int getRGB(unsigned int color) { return color & 0xFFFFFF; }
unsigned int ARGB(int a, int r, int g, int b) { return (a << 24) | rgb(r, g, b); }
unsigned int ARGB(int rgb, int a) { return rgb | (a << 24); }

unsigned int rgbUpperClamped(int red, int green, int blue)
{
	if (red>255) red = 255;
	if (green>255) green = 255;
	if (blue>255) blue = 255;
	return blue | (green << 8) | (red << 16);
}