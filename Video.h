SDL_Surface*Screen;
unsigned int*oldInit(int Width, int Height)
{
	static int called = 0;
	if (!called)
	{
		_putenv_s("SDL_VIDEODRIVER", "windib");
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_ShowCursor(SDL_DISABLE);
		atexit(SDL_Quit);
		called = 1;
	}
	else SDL_FreeSurface(Screen);
	memset(keyboard, 0, sizeof(int) * 256);
	Screen = SDL_SetVideoMode(Width, Height, 32, SDL_SWSURFACE | SDL_FULLSCREEN);
	//Screen=SDL_SetVideoMode(Width,Height,32,0);
	if (!Screen) return 0;
	return (unsigned int*)Screen->pixels;
}

Bitmap Init(int screenWidth, int screenHeight)
{
	Bitmap video;
	unsigned int*screenBuffer;
	screenBuffer = oldInit(screenWidth, screenHeight);
	video.Load(screenBuffer, screenWidth, screenHeight);
	alnLoadFonts();
	return video;
}

long long Frames = 0;
int Update()
{
	if (!Screen) return 1;
	SDL_Flip(Screen);
	UpdateKeyboard();
	Frames++;
	return 0;
}