#define ENEMY_STATE_DORMANT 0
#define ENEMY_STATE_ACTIVE 1
#define ENEMY_STATE_DEAD 2
#define ENEMY_STATE_INACTIVE 3
class Enemy
{
public:
	Animation Image;
	Vector2 Pos0, Pos1, Pos2, Pos3;
	float t;
	float Speed;
	int State;
	Vector2 GetPosition();
	Vector2 GeneratePosition();
	Vector2 GenerateStartPosition();
	Vector2 GenerateDeathPosition();
	double TimeOfDeath;
	Vector2 PositionOfDeath;
	void Kill(double absTime)
	{
		if (State != ENEMY_STATE_ACTIVE) return;
		State = ENEMY_STATE_DEAD;
		TimeOfDeath = absTime;
		PositionOfDeath = GetPosition();
	}
	void GenerateAllPos() {
		Pos0 = GenerateStartPosition();
		Pos1 = GenerateStartPosition();
		Pos2 = GeneratePosition();
		Pos3 = GeneratePosition();
	}
	void Init() {
		t = 0;
		State = ENEMY_STATE_ACTIVE;
		GenerateAllPos();
		Speed = 2.0f;
	}
	Enemy() { Init(); }
	Enemy(Animation&image, float speed)
	{
		Init(); Speed = speed; Image = image;
	}
	void Update(double time)
	{
		t += float((time*Speed*0.000025) / max(1.0f / 1000, Pos1.Distance(Pos2)));
		while (t>1.0f)
		{
			t -= 1.0f;
			Pos0 = Pos1; Pos1 = Pos2; Pos2 = Pos3;
			if (State == ENEMY_STATE_ACTIVE) Pos3 = GeneratePosition();
			if (State == ENEMY_STATE_DEAD) Pos3 = GenerateDeathPosition();
		}
		if (State == ENEMY_STATE_DEAD)
		{
			if (Pos1.x<0.0f) State = ENEMY_STATE_INACTIVE;
			if (Pos1.x>1.0f) State = ENEMY_STATE_INACTIVE;
			if (Pos1.y<0.0f) State = ENEMY_STATE_INACTIVE;
			if (Pos1.y>1.0f) State = ENEMY_STATE_INACTIVE;
		}
	}
	void Draw(Bitmap&Target, double time)
	{
		Vector2 enemyPos = GetPosition();
		if (State == ENEMY_STATE_ACTIVE)
			Target.DrawCentered(int(enemyPos.x*Target.Width), int(enemyPos.y*Target.Height),
				*Image.GetBitmap(time));
		if (State == ENEMY_STATE_DEAD)
			Target.DrawDead(int(enemyPos.x*Target.Width), int(enemyPos.y*Target.Height),
				*Image.GetBitmap(time));
	}
};

Vector2 Enemy::GetPosition()
{
	return Cubic(Pos0, Pos1, Pos2, Pos3, t);
}

Vector2 Enemy::GeneratePosition()
{
	return Vector2(Rand01(), Rand01());
}

Vector2 Enemy::GenerateStartPosition()
{
	float xmin = -0.25f;
	float xmax = 1.25f;
	float ymin = -0.25f;
	float ymax = 0.25f;
	Vector2 Pos(0, 0);
	int ok = 0;
	do
	{
		Pos.x = xmin + Rand01()*xmax - xmin;
		Pos.y = ymin + Rand01()*ymax - ymin;
		if ((Pos.x<1.1f) && (Pos.x>-0.1f) && (Pos.y>-0.1f)) ok = 0; else ok = 1;
	} while (!ok);
	return Pos;
}
Vector2 Enemy::GenerateDeathPosition()
{
	float xmin = -0.25f;
	float xmax = 1.25f;
	float ymin = -0.25f;
	float ymax = 1.25f;
	Vector2 Pos(0, 0);
	int ok = 0;
	do
	{
		Pos.x = xmin + Rand01()*xmax - xmin;
		Pos.y = ymin + Rand01()*ymax - ymin;
		if ((Pos.x<1.1f) && (Pos.x>-0.1f) && (Pos.y>-0.1f) && (Pos.y<1.1f)) ok = 0; else ok = 1;
	} while (!ok);
	return Pos;
}