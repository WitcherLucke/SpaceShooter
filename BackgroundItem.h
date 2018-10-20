class BackgroundItem
{
public:
	Animation image;
	int x, y;
	int height;
	float speed;
	BackgroundItem(Bitmap&image, int x, int y, int height, float speed)
	{
		this->image = image;
		for (int i = 0; i<this->image.frameCount; i++)
			this->image.GetBitmap(i)->FreePixels = 0; //to fix!
		this->x = x;
		this->y = y;
		this->height = height;
		this->speed = speed;
	}
	BackgroundItem(Animation&image, int x, int y, int height, float speed)
	{
		this->image = image;
		for (int i = 0; i<this->image.frameCount; i++)
			this->image.GetBitmap(i)->FreePixels = 0; //to fix!
		this->x = x;
		this->y = y;
		this->height = height;
		this->speed = speed;
	}
	void Draw(Bitmap&target, double time)
	{
		Bitmap&bmp = *image.GetBitmap(time);
		target.Draw(x,
			((int(y + speed * time)) % (height + 2 * bmp.Height)) - bmp.Height, bmp);
		
	}
};