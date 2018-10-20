#define A 0x41
#define B 0x42
#define C 0x43
#define D 0x44
#define E 0x45
#define F 0x21
#define G 0x47
#define H 0x48
#define I 0x49
#define J 0x4A
#define K 0x4B
#define L 0x4C
#define M 0x4D
#define N 0x4E
#define O 0x4F
#define P 0x50
#define Q 0x51
#define R 0x52
#define S 0x53
#define T 0x54
#define U 0x55
#define V 0x56
#define W 0x57
#define X 0x58
#define Y 0x59
#define Z 0x5A


#define F1  0x70
#define F2  0x71
#define F3  0x72
#define F4  0x73
#define F5  0x74
#define F6  0x75
#define F7  0x76
#define F8  0x77
#define F9  0x78
#define F10 0x79
#define F11 0x7A
#define F12 0x7B

#define CTRL		0x11
#define Shift	0x10
#define Enter	0xD
#define Space	0x20
#define DEL		0x2E
#define Minus	0x189
#define Plus		0x187
#define Tab		0x9
#define PageUp	0x21
#define PageDown 0x22

#define Pause	   0x13
#define Insert	   0x2D

#define LeftArrow  0x25
#define RightArrow 0x27
#define UpArrow	  0x26
#define DownArrow  0x28

#define Esc 27

#define MouseLeft	   1
#define MouseMiddle	   2
#define MouseRight	   3
#define MouseWheelUp	   4
#define MouseWheelDown  5

#define keyESC 1
#define keyENTER 28
#define keySPACE 57
#define keyARROWUP 72
#define keyARROWDOWN 80
#define keyARROWLEFT 75
#define keyARROWRIGHT 77

int keyboard[256], keyboardToggle[256], mouseX, mouseY;

void UpdateKeyboard()
{
	SDL_Event keyEvent;
	while (SDL_PollEvent(&keyEvent))
	{
		if (keyEvent.type == SDL_KEYDOWN)
		{
			int k = keyEvent.key.keysym.scancode;
			keyboard[k] = 1;
			keyboardToggle[k] = !keyboardToggle[k];
		}
		if (keyEvent.type == SDL_KEYUP) keyboard[keyEvent.key.keysym.scancode] = 0;
		if (keyEvent.type == SDL_MOUSEMOTION)
		{
			mouseX = keyEvent.motion.x;
			mouseY = keyEvent.motion.y;
		}
	}
}

int GetKey(int k) { return keyboard[k]; }
int GetKeyToggle(int k) { return keyboardToggle[k]; }
int GetAndStopKey(int k) { int keystate = keyboard[k]; keyboard[k] = 0; return keystate; }

void ExitAtKeyPress() { for (int i = 0; i<256; i++) if (GetKey(i)) exit(i); }