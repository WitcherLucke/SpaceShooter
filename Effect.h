void Effect(unsigned int*destination, int&x, int&y, int Height, int Width, int radius, float intensity)
{
	float distance = 0;
	
	float intensityOverRadius = intensity / radius;
	for (int i = max(0, y - radius); i<min(Height, y + radius); i++)
		for (int j = max(0, x - radius); j<min(Width, x + radius); j++)
		{
			
			float distance = sqrt(float((x - j)*(x - j) + (y - i)*(y - i)));
			if (distance<radius)
			{
			
				int light = int((radius - distance)*intensityOverRadius);
				unsigned int&dest = destination[i*Width + j];
				int R = dest >> 16;
				int G = (dest >> 8) & 0xFF;
				int B = dest & 0xFF;
				R = min(255, R + light);
				G = min(255, G + light);
				B = min(255, B + light);
				dest = rgb(R, G, B);
			}
		}
}

void EffectBackground(unsigned int*destination, int Height, int Width)
{
	float distance = 0;
	for (int i = 0; i<Height; i++)
		for (int j = 0; j<Width; j++)
		{
			destination[i*Width + j] = rgbUpperClamped(
				int(i * 255 / Height),
				int(j * 255 / Width),
				int((i*j) / 600));
		}
}
