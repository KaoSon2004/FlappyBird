#pragma once
#include "WaterPile.h"


waterPile::waterPile()
{

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
	

	for (int i = 0; i < TOTAL_PILE; ++i)
	{
		SDL_Rect k;
		SetPos( SCREEN_WIDTH+ i * distance + 450, -200-RanDom());
		k = GetPos();
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
	
	for (int i = 0; i < TOTAL_PILE;i++)
	{
		if (posPile[i].x <= SCREEN_WIDTH && posPile[i].x > -getWidth())
		{
			wRender(screen, posPile[i].x, posPile[i].y);
			wRender(screen, posPile[i].x, posPile[i].y + getHeight() + space, 180);
			 
			
		}
		
		
	
		
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
	
		for (int j = 0; j < TOTAL_PILE; ++j)
		{
			if (posPile[j].x < -getWidth())
			{

				posPile[j].y = -200-RanDom(); 
				SetYPos(posPile[j].y);
				posPile[j].x = posPile[(j + TOTAL_PILE - 1) % TOTAL_PILE].x + distance;
			}

		}
	
}
void waterPile::DoRun(SDL_Rect player)
{
	for (int i = 0; i < TOTAL_PILE; i++)
	{
		posPile[i].x += xval;
		SetXPos(posPile[i].x);
		col = CheckCollision(player, wRect);
	}

	
}
int waterPile::RanDom()
{
	
	int res = rand() % (250 - 10 + 1) + 10;
	return res;
}
void waterPile::SetPos(int x, int y)
{
	wRect.x = x;
	wRect.y = y;
}
