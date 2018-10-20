void AddBackgroundElements(
	Bitmap&video,
	Background&Back0, Background&Back1,
	Bitmap&star0, Bitmap&star1, Bitmap&star2, Bitmap&star3, Bitmap&star4,
	Bitmap&cloud1, Bitmap&cloud2)
{
	star0.Load("Star0.bmp", "Star0Alpha.bmp");
	star1.Load("Star1.bmp", "Star1Alpha.bmp");
	star2.Load("Star2.bmp", "Star2Alpha.bmp");
	star3.Load("Star3.bmp", "Star3Alpha.bmp");
	star4.Load("Star4.bmp", "Star4Alpha.bmp");
	cloud1.Load("Cloud0.bmp", "CloudAlpha0.bmp");
	cloud2.Load("Cloud0.bmp", "CloudAlpha1.bmp");
	cloud1.AutoCrop();
	cloud2.AutoCrop();
	star0.AutoCrop();
	star1.AutoCrop();
	star2.AutoCrop();
	star3.AutoCrop();
	for (int i = 0; i<45; i++)
	{
		Back0.Add(star4, rand() % video.Width, rand() % video.Height,
			1000 + rand() % 500, 0.0015f + Rand01()*0.0025f);
	}
	for (int i = 0; i<30; i++)
	{
		Back0.Add(star3, rand() % video.Width - star1.Width / 2, rand() % video.Height,
			1000 + rand() % 500, 0.005f + (rand() % 4000) / 65000.0f);
	}
	for (int i = 0; i<30; i++)
	{
		Back0.Add(star2, rand() % video.Width - star1.Width / 2, rand() % video.Height,
			1000 + rand() % 500, 0.005f + (rand() % 4000) / 65000.0f);
	}
	for (int i = 0; i<12; i++)
	{
		Back0.Add(star0, rand() % video.Width - star1.Width / 2, rand() % video.Height,
			1000 + rand() % 500, 0.015f + (rand() % 4000) / 35000.0f);
	}
	for (int i = 0; i<8; i++)
	{
		Back0.Add(star1, rand() % video.Width - star1.Width / 2, rand() % video.Height,
			1000 + rand() % 500, 0.015f + (rand() % 4000) / 35000.0f);
	}
	for (int i = 0; i<15; i++)
	{
		Back0.Add(cloud1, rand() % video.Width - cloud1.Width / 2, rand() % video.Height,
			2000 + rand() % 2000, 0.025f + (rand() % 4000) / 15000.0f);
		Back0.Add(cloud2, rand() % video.Width - cloud2.Width / 2, rand() % video.Height,
			2000 + rand() % 2000, 0.025f + (rand() % 4000) / 15000.0f);
	}
	for (int i = 0; i<10; i++)
	{
		Back1.Add(cloud1, rand() % video.Width - cloud1.Width / 2, rand() % video.Height,
			2000 + rand() % 2000, 0.025f + (rand() % 4000) / 15000.0f);
		Back1.Add(cloud2, rand() % video.Width - cloud2.Width / 2, rand() % video.Height,
			2000 + rand() % 2000, 0.025f + (rand() % 4000) / 15000.0f);
	}
}