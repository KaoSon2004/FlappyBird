#include "CommonFunction.h"
#include "TextureManager.h"
#include "Player.h"
#include "WaterPile.h"
#include "TextObject.h"
TextureManager gBackGround;
waterPile pile;
TTF_Font* font_time;
bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		success = false;
		cout << "Couldn't initialize SDL" << endl;
	}
	else
	{
		gWindow = SDL_CreateWindow("Flappy bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			success = false;
			cout << "Couldn't create window" << endl;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				cout << "Could create renderer" << endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				int imgFlags = IMG_INIT_PNG;
				if (!imgFlags && IMG_Init(imgFlags))
					success = false;
				if (TTF_Init() == -1)
					success = false;
				font_time = TTF_OpenFont("dlxfont_.ttf", 15);
				if (font_time == NULL)
				{
					cout << "Error" << endl;
					success = false;
				}
			}
		}
	}
		return success;
}
bool LoadBackGround()
{
	bool ret = gBackGround.LoadImg("background.png", gRenderer);
	return ret;
}
bool LoadWaterPile()
{
	bool ret1 = pile.LoadImg("top.png", gRenderer);

	return ret1;
}
void close ()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
}


int main(int argc, char* argv[])
{
	if (Init() == false)
	{
		return -1;
	}

	if (LoadBackGround()==false)
	{
		return -1;
	}

	Bird Player;
	Bird Die;
	
	bool ret = Player.loadImg("bird.png", gRenderer);
	bool ret1 = Die.loadImg("die.png", gRenderer);
	if (ret == false||ret1==false)
	{
		return -1;
	}
	Player.SetRect(100, 100);
	if (!LoadWaterPile())
	{
		return -1;
	}
	pile.Init();

	bool quit = false;

	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	Uint32 mark_value = 0;

	const int FPS = 60;
	const int  frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	while (!quit)
	{
		frameStart = SDL_GetTicks();
		
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			
				Player.HandleInputAction(gEvent, gRenderer);
			

		}

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		gBackGround.Render(gRenderer, NULL);
		Player.DoFalling(gRenderer);
		Player.Show(gRenderer);
		SDL_Rect birdr = Player.GetRect();
		pile.loadWaterPile(gRenderer);
		pile.DoRun(birdr);

		if (pile.GetCollisionState1() == true || pile.GetCollisionState2() == true || pile.GetCollisionState3() == true
		|| pile.GetCollisionState4() == true || pile.GetCollisionState5() == true || pile.GetCollisionState6() == true)
		{
			Player.SetIsDie(true);
		}
		if (Player.GetIsDie())
		{
			pile.SetXVal(0);
			Player.Free();
			Die.SetRect(birdr.x, birdr.y-5);
			Die.Show(gRenderer);
		}
		
		pile.wUpdate(); 
		bool getScore = (pile.GetScore(birdr));


		if (getScore)
			mark_value++;

		string val_str_mark = to_string(mark_value);
		string strMark("Mark: ");
		strMark += val_str_mark;
		mark_game.SetText(strMark);
		mark_game.loadFromtRenderText(font_time, gRenderer);
		mark_game.RenderText(gRenderer, SCREEN_WIDTH - 200, 30);
		SDL_RenderPresent(gRenderer);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		//limit

	}

	close();
	return 0;
}