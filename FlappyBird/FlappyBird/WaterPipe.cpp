#pragma once
#include "WaterPile.h"
static vector <position> posPile;

waterPile::waterPile()
{
	xpos = 0;
	ypos = 0;

	wTexture = NULL;
}
waterPile::~waterPile()
{
	Free();
}
bool waterPile::LoadImg(string path, SDL_Renderer* screen)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
		if (newTexture != NULL)
		{
			wWidth = loadedSurface->w;
			wHeight = loadedSurface->h;
		}
	}
	wTexture = newTexture;
	SDL_FreeSurface(loadedSurface);
	return wTexture != NULL;
}
void waterPile::Init()
{
	srand(time(NULL));
	int ran;
	do
	{
		ran = rand() % 200;
	} while (ran<50);
	for (int i = 0; i < TOTAL_PILE; ++i)
	{
		position k;
		k.GetPos(  i * distance + 450, -200-ran);
		posPile.push_back(k);
	}
	
}
void waterPile::Free()
{
	if (wTexture != NULL)
	{
		SDL_DestroyTexture(wTexture);
		wWidth = 0;
		wHeight = 0;

	}
}
void waterPile::loadWaterPile(SDL_Renderer* screen)
{
	for (int i = 0; i < TOTAL_PILE; ++i)
	{
		if (posPile[i].x <= SCREEN_WIDTH && posPile[i].x > -getWidth())
			wRender(screen,posPile[i].x, posPile[i].y);
		wRender(screen,posPile[i].x, posPile[i].y + getHeight() + space,180);
	}
	
}
void waterPile::wRender(SDL_Renderer* screen,int x, int y, int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
	SDL_Rect Rec_Render = { x, y, wWidth, wHeight };

	if (clip != NULL)
	{
		Rec_Render.w = clip->w;
		Rec_Render.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(screen, wTexture, clip, &Rec_Render, angle, NULL, flip);
}
void waterPile::wUpdate()
{
	srand(time(NULL));
	int ran;
	do
	{
		ran = rand() % 200;
	} while (ran < 50);
		for (int j = 0; j < TOTAL_PILE; ++j)
		{
			if (posPile[j].x < -getWidth())
			{
				posPile[j].y = -200-ran;
				posPile[j].x = posPile[(j + TOTAL_PILE - 1) % TOTAL_PILE].x + distance;
			}

		}
	
}
void waterPile::DoRun(SDL_Renderer* screen)
{
	for (int i = 0; i < TOTAL_PILE; i++)
	{
		posPile[i].x += xval;
	}
	
}