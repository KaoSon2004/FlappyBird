#include "CommonFunction.h"
#include "TextureManager.h"
#include "Player.h"
TextureManager gBackGround;
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
	bool ret = Player.loadImg("bird.png", gRenderer);

	bool quit = false;
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

		}
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		gBackGround.Render(gRenderer, NULL);
 		Player.HandleInputAction(gEvent, gRenderer);
		Player.Show(gRenderer);
		SDL_RenderPresent(gRenderer);

		//limit
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	close();
	return 0;
}