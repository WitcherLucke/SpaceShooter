class Missile
{
public:
	Animation Image;
	Vector2 Pos;
	Vector2 Dir;
	float Speed;
	int Active;
	void Draw(Bitmap&Target, double absTime)
	{
		
		Target.DrawCentered(int(Pos.x*Target.Width), int(Pos.y*Target.Height),
			*Image.GetBitmap(absTime));
	}
	void Update(double deltaTime)
	{
		if (!Active) return;
		Pos = Pos + (float(deltaTime*Speed*0.0001f)*Dir);
		if (Pos.x>2.0f) Active = 0;
		if (Pos.y>2.0f) Active = 0;
		if (Pos.y>2.0f) Active = 0;
		if (Pos.y<-1.0f) Active = 0;
	}

	//--Constructors/Destructors

	void Init() { Active = 1; }

	Missile() { Init(); }

	Missile(Animation&anm, Vector2 pos, Vector2 dir, float speed)
	{
		Init(); Image = anm; Pos = pos; Dir = dir; Speed = speed;
		Dir.y *= 1.333333f;
		Dir.Normalize();
	}
};