#include "game.h"

int main(int argn, char**argv)
{
	int screenWidth = 1024;
	int screenHeight = 768;
	Bitmap video = Init(screenWidth, screenHeight);
	Background Back0, Back1;
	Player Player;
	Bitmap playerpic("ship2.bmp", "ship2Alpha.bmp");
	Animation fire("fire", "fireAlpha", "bmp", 150);
	Animation germ("germ", "germAlpha", "bmp", 600);
	Animation germB("germB", "germAlpha", "bmp", 600);
	Animation germC("germC", "germAlpha", "bmp", 600);
	Animation disc("disc", "discAlpha", "bmp", 1600);
	Animation discB("discB", "discAlphaB", "bmp", 1600);
	Bitmap back("back.bmp");
	Bitmap arrow("arrow.bmp", "arrowAlpha.bmp");
	Bitmap star0, star1, star2, star3, star4, cloud1, cloud2;
	AddBackgroundElements(video, Back0, Back1, star0, star1, star2, star3, star4, cloud1, cloud2);
	EnemyManager enemyManager;
	MissileManager missileManager;
	enemyManager.AddEnemyType(germ, 1.0f);
	enemyManager.AddEnemyType(germB, 0.5f);
	enemyManager.AddEnemyType(germC, 0.75f);
	enemyManager.AddEnemyType(disc, 3.5f);
	enemyManager.AddEnemyType(discB, 4.0f);


	StartTimer();
	double PlayerTime = CheckTimer();
	double lastFrameTime = 0;
	do {
		float FPS = float((Frames * 1000) / CheckTimer());
		char fpstext[128];
		sprintf_s(fpstext, 128, "FPS:%.2f", FPS);
		double frameTime = CheckTimer();
		double deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		video.FastDraw(0, 0, back);
		Back0.Draw(video, frameTime + 100000);
		int screenPlayerX = int(Player.Pos.x*(video.Height - 1));
		int screenPlayerY = int(Player.Pos.y*(video.Height - 1));
		Player.GetScreenCoordinates(screenPlayerX, screenPlayerY, video.Width, video.Height);

		if (Player.Dir.y<-0.004f)
		{
			if (fire.GetFrame(frameTime))
				video.DrawCentered(screenPlayerX - 3, screenPlayerY + 40, *fire.GetBitmap(frameTime));
			else video.DrawCentered(screenPlayerX - 1, screenPlayerY + 30, *fire.GetBitmap(frameTime));
		}
		enemyManager.Draw(video, frameTime);

		missileManager.Draw(video, frameTime);
		video.DrawCentered(screenPlayerX, screenPlayerY, playerpic);
		Back1.Draw(video, frameTime + 100000);
		if (GetKeyToggle(F)) video.WriteText(fpstext, 0, 0);

		Update();

		if (GetAndStopKey(keySPACE))
			missileManager.AddMissile(Missile(Animation(arrow), Player.Pos, Vector2(0, -1.0f), 10.0f));

		if (GetKey(keyARROWUP)) Player.MoveUp(deltaTime);
		if (GetKey(keyARROWDOWN)) Player.MoveDown(deltaTime);
		if (GetKey(keyARROWLEFT)) Player.MoveLeft(deltaTime);
		if (GetKey(keyARROWRIGHT)) Player.MoveRight(deltaTime);
		Player.Update(deltaTime);
		enemyManager.Update(deltaTime);
		missileManager.Update(deltaTime);
		
		//--enemy hits
		for (int i = 0; i<missileManager.n; i++)
			for (int j = 0; j<enemyManager.n; j++)
			{
				Missile&m = missileManager.Missile[i];
				Enemy&e = enemyManager.enemy[j];
				if (m.Pos.Distance(e.GetPosition())<0.025f)
				{
					e.Kill(frameTime);
				}
			}
	} while (!GetKey(keyESC));

	return 0;

}