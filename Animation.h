class Animation
{
public:
	Bitmap * frame;
	int frameCount;
	float time;
	
	int LoadFromFiles(const char*, const char*, const char*);
	Bitmap*GetBitmap(int i) { return &frame[i]; }
	int GetFrame(double time)
	{
	
		time = fmod(time, double(frameCount*this->time));
		return int(time / this->time);
	}
	Bitmap*GetBitmap(double time)
	{
		time = fmod(time, double(frameCount*this->time));
		return &frame[int(time / this->time)];
	}
	void AutoCrop() { for (int i = 0; i<frameCount; i++) frame[i].AutoCrop(); }
	void Init() { frame = 0; frameCount = 0; }
	Animation() { Init(); }
	Animation(const char*, const char*, const char*, float);
	Animation(Bitmap&bmp)
	{
		Init();
		frame = (Bitmap*)Malloc(sizeof(Bitmap));
		frame[0] = bmp;
		frameCount = 1;
		time = 1000;
	}
};

int Animation::LoadFromFiles(const char*path, const char*alphapath, const char*ext)
{
	char fullPath[512];
	char fullAlphaPath[512];
	fullPath[0] = 0;
	int n = 0;
	while (true)
	{
		sprintf(fullPath, "%s%d.%s", path, n, ext);
		if (FileExists(fullPath)) n++; else break;
	}
	if (!n) return 0; //no file found
	frame = (Bitmap*)Malloc(n * sizeof(Bitmap));
	frameCount = n;
	for (int i = 0; i<n; i++)
	{
		sprintf(fullPath, "%s%d.%s", path, i, ext);
		sprintf(fullAlphaPath, "%s%d.%s", alphapath, i, ext);
		if (alphapath)
		{
			frame[i].Init();
			frame[i].Load(fullPath, fullAlphaPath);
		}
		else
		{
			frame[i].Init();
			frame[i].Load(fullPath);
		}
	}
	return n;
}

Animation::Animation(const char*path, const char*alphapath, const char*ext, float time)
{
	Init(); LoadFromFiles(path, alphapath, ext); this->time = time;
}

