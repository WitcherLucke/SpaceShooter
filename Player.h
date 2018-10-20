class Player
{
public:
	Vector2 Pos;
	Vector2 Dir;
	float Speed;
	float MaxSpeed;
	void Update(double);
	void MoveRight(double);
	void MoveLeft(double);
	void MoveUp(double);
	void MoveDown(double);
	void GetScreenCoordinates(int&, int&, int, int);
	Player()
	{
		Pos = Vector2(0.5f, 0.7f);
		Dir = Vector2(0.0f, 0.0f);
		Speed = 0.000025f;
		MaxSpeed = 0.005f;
	}
};

void Player::GetScreenCoordinates(int&x, int&y, int Width, int Height)
{
	x = int(Width*Pos.x);
	y = int(Height*Pos.y);
	if (x<0) x = 0; if (x >= Width) x = Width - 1;
	if (y<0) y = 0; if (y >= Height) y = Height - 1;
}

void Player::Update(double deltaTime)
{
	if (Pos.x<0) Pos.x = 0;
	if (Pos.y<0) Pos.y = 0;
	if (Pos.x>1) Pos.x = 1;
	if (Pos.y>1) Pos.y = 1;
	if (Dir.Length()>MaxSpeed) Dir.Normalize(MaxSpeed);
	Pos = Pos + Dir * float(deltaTime*0.1f);
	Dir = Dir * float(pow(0.975, deltaTime*0.1));
}

void Player::MoveRight(double deltaTime)
{
	Dir = Dir + (Vector2(1.0f, 0)*(float(deltaTime*Speed)));
}
void Player::MoveLeft(double deltaTime)
{
	Dir = Dir + (Vector2(-1.0f, 0)*(float(deltaTime*Speed)));
}
void Player::MoveUp(double deltaTime)
{
	Dir = Dir + (Vector2(0, -1.33333333f)*(float(deltaTime*Speed)));
}
void Player::MoveDown(double deltaTime)
{
	Dir = Dir + (Vector2(0, 1.33333333f)*(float(deltaTime*Speed)));
}