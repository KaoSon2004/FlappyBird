#include "CommonFunction.h"
#include "TextureManager.h"
#include "Player.h"
#include "WaterPile.h"
#include "TextObject.h"
#include "TextObject.h"
#include "HighScore.h"
TextureManager gBackGround;
waterPile pile;
TTF_Font* font_time;
Mix_Music* theme = NULL;
Mix_Chunk* ting = NULL;
Mix_Chunk* punch = NULL;
Mix_Music* gameover = NULL;
highScore highscore;
bool Init()
{
	bool success = true;

	if ((SDL_Init(SDL_INIT_EVERYTHING)|SDL_INIT_AUDIO) < 0	)
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
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout << "SDL couldn't initialize " << endl;
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
bool LoadMusic()
{
	theme = Mix_LoadMUS("theme.wav");
	if (theme == NULL)
		return false;
	ting = Mix_LoadWAV("ting.wav");
	if (ting == NULL)
		return false;
	punch = Mix_LoadWAV("punch.wav");
	if (punch == NULL)
		return false;
	gameover = Mix_LoadMUS("gameover.wav");
	if (gameover == NULL)
		return false;

	return true;
}

int ShowMeNu(SDL_Renderer* screen, TTF_Font* font, string menu1, string menu2,int score)
{
	Uint32 time = 0;
	int x = 0;
	int y = 0;
	const int numMenu = 2;
	SDL_Texture* menu[numMenu];
	bool selected[numMenu] = { 0,0 };
	SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };
	TextObject textObject[numMenu];
	textObject[0].SetText(menu1);
	textObject[0].SetColor(color[0].r, color[0].g, color[0].b);
	textObject[0].loadFromtRenderText(font, screen);
	textObject[1].SetText(menu2);
	textObject[1].SetColor(color[0].r, color[0].g, color[0].b);
	textObject[1].loadFromtRenderText(font, screen);
	SDL_Rect pos[numMenu];
	pos[0].x = SCREEN_WIDTH/2-50;
	pos[0].y = SCREEN_HEIGHT/2;
	pos[1].x = SCREEN_WIDTH /2-50;
	pos[1].y = SCREEN_HEIGHT /2+50;
	
	TextObject highscore;
	string str = "HiScore: ";
	str = str + to_string(score);
	highscore.SetText(str);
	highscore.SetColor(color[0].r, color[0].g, color[0].b);
	highscore.loadFromtRenderText(font, screen);
	SDL_Rect scorePos;
	scorePos.x = SCREEN_WIDTH / 2 - 60;
	scorePos.y = 10;
	SDL_Event event;
	const int FPS = 60;
	const int  frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	while (1)
	{
		frameStart = SDL_GetTicks();
		while(SDL_PollEvent(&event)!=0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				textObject[0].Free();
				textObject[1].Free();
				highscore.Free();
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < numMenu; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
						y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (selected[i]==false)
						{
							selected[i] = true;
							textObject[i].SetColor(color[1].r, color[1].g, color[1].b);
							textObject[i].loadFromtRenderText(font, screen);

						}
					}
					else
					{
						if (selected[i] == true)
						{
							selected[i] = false;
							textObject[i].SetColor(color[0].r, color[0].g, color[0].b);
							textObject[i].loadFromtRenderText(font, screen);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < numMenu; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
						y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						textObject[0].Free();
						textObject[1].Free();
						highscore.Free();
						return i;
					}
				}
				break;	
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					textObject[0].Free();
					textObject[1].Free();
					highscore.Free();
					return 1;
				}
			}
		}
		for (int i = 0; i < numMenu; ++i)
		{
			textObject[i].RenderText(screen, pos[i].x, pos[i].y);
			pos[i].w = textObject[i].GetWidth();
			pos[i].h = textObject[i].GetHeight();
		}
		highscore.RenderText(screen, scorePos.x, scorePos.y);
		SDL_RenderPresent(screen);
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
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

	bool PlayAgain = false;
	if (Init() == false)
	{
		return -1;
	}

	if (LoadBackGround() == false)
	{
		return -1;
	}
	if (LoadMusic() == false)
		return -1;
	bool limit = true;
	do
	{

		if (highscore.loadFromFile("highscore.txt") == false)
			return -1;
		Bird Player;
		Bird Die;
		bool ret = Player.loadImg("bird.png", gRenderer);
		bool ret1 = Die.loadImg("die.png", gRenderer);
		if (ret == false || ret1 == false)
		{
			return -1;
		}
		if (!LoadWaterPile())
		{
			return -1;
		}
		bool quit = false;
		
		if (PlayAgain == false)
		{
			int retMenu = ShowMeNu(gRenderer, font_time, "Play Game", "Exit",highscore.GetScore());
			if (retMenu == 1)
			{
				quit = true;
				PlayAgain = false;
			}
			else 
			{
				Mix_PlayMusic(theme, -1);
			}
		}


		Player.SetRect(100, 100);

		pile.Init();
		pile.SetXVal(-4);
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
					PlayAgain = false;
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
				Mix_PlayChannel(-1, punch, 0);
				Player.SetIsDie(true);
			}

			if (Player.GetIsDie())
			{
				pile.SetXVal(0);
				Player.Free();
				Die.SetRect(birdr.x, birdr.y - 5);
				Die.Show(gRenderer);
				Mix_PauseMusic();
			}

			pile.wUpdate();
			bool getScore = (pile.GetScore(birdr));


			if (getScore)
			{
				mark_value++;
				Mix_PlayChannel(-1, ting, 0);
			}


			string val_str_mark = to_string(mark_value);
			string strMark("Mark: ");
			strMark += val_str_mark;
			mark_game.SetText(strMark);
			mark_game.loadFromtRenderText(font_time, gRenderer);
			mark_game.RenderText(gRenderer, SCREEN_WIDTH - 200, 30);
			SDL_RenderPresent(gRenderer);
			bool gameOver = false;
			gameOver = Player.GameOver();
			if (gameOver == true)
			{
				
				if (mark_value > highscore.GetScore())
				{
					highscore.saveScore(mark_value);
					highscore.SetScore(mark_value);
				}
					
				Mix_PlayMusic(gameover, -1);
				int retMenu1 = ShowMeNu(gRenderer, font_time, "Play again", "Exit",highscore.GetScore());
				if (retMenu1 == 1)
				{
					quit = true;
					PlayAgain = false;
				}
				else if (retMenu1==0)
				{
					PlayAgain = true;
					limit = false;
					quit = true;
					Mix_PlayMusic(theme, -1);
				}
			}
			if (limit)
			{
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}
			}
			if (PlayAgain == true)
			{
				limit = true;
			}
				
			//limit

		}
		
	}
	while (PlayAgain);
	close();
	return 0;
}