class MissileManager
{
public:
	Missile * Missile;
	int n;
	void RemoveMissile(int i)
	{
		if (i >= n) return;
		n--; Missile[i] = Missile[n];
	}
	void AddMissile(Missile&missile)
	{
		AddObject(missile, Missile, n);
		for (int i = 0; i<n; i++)
			if (!Missile[i].Active) { RemoveMissile(i); break; }
	}
	void Update(double deltaTime)
	{
		for (int i = 0; i<n; i++) Missile[i].Update(deltaTime);
		for (int i = 0; i<n; i++) if (!Missile[i].Active) { RemoveMissile(i); break; }
	}
	void Draw(Bitmap&Target, double absTime)
	{
		for (int i = 0; i<n; i++) Missile[i].Draw(Target, absTime);
	}
	void Init() { Missile = 0; n = 0; }
	void Release() { Free(Missile); n = 0; }
	MissileManager() { Init(); }
	~MissileManager() { Release(); }
};