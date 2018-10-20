class Background
{
	BackgroundItem*items;
	int n;
public:
	void Add(Bitmap&bmp, int x, int y, int height, float speed)
	{
		AddObject(BackgroundItem(bmp, x, y, height, speed), items, n);
	}
	void Add(Animation&anm, int x, int y, int height, float speed)
	{
		AddObject(BackgroundItem(anm, x, y, height, speed), items, n);
	}
	void Draw(Bitmap&target, double time)
	{
		for (int i = 0; i<n; i++) items[i].Draw(target, time);
	}
	Background() { items = 0; n = 0; }
	~Background() { Free(items); }
};