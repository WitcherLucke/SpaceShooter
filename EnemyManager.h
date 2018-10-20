class EnemyManager
{
public:
	Enemy * enemy;
	int n;
	Enemy*enemyTypes;
	int typesCount;
	void AddEnemy(Animation&Image, float Speed)
	{
		AddObject(Enemy(Image, Speed), enemy, n);
	}
	void AddEnemy(Enemy&e)
	{
		AddObject(e, enemy, n);
	}
	void AddEnemyType(Animation&Image, float Speed)
	{
		AddObject(Enemy(Image, Speed), enemyTypes, typesCount);
	}
	void AddRandomEnemy()
	{
		Enemy e = enemyTypes[rand() % typesCount];
		e.Init();
		AddEnemy(e);
	}
	void RemoveEnemy(int i)
	{
		if (i >= n) return;
		n--; enemy[i] = enemy[n];
	}
	void Update(double deltaTime)
	{
		for (int i = 0; i<n; i++) enemy[i].Update(deltaTime);
		for (int i = 0; i<n; i++)
			if (enemy[i].State == ENEMY_STATE_INACTIVE)
			{
				RemoveEnemy(i); break;
			}
		if (n<60) AddRandomEnemy();
	}
	void Draw(Bitmap&Target, double absTime)
	{
		for (int i = 0; i<n; i++) enemy[i].Draw(Target, absTime);
	}
	EnemyManager() { enemy = 0; n = 0; enemyTypes = 0; typesCount = 0; }
};