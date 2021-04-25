#pragma once
#include "WaterPile.h"


waterPile::waterPile()
{
	col1 = false;
	col2 = false;
	col3 = false;
	col4 = false;
	col5 = false;
	col6 = false;
	wTexture = NULL;
	xval = -4;
	distance = 400;
	space = 200;
	checkpass = false;
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
	wRect1.x = SCREEN_WIDTH + 0 * distance + 450;
	wRect1.y = -200 - RanDom();
	wRect1.w = wWidth;
	wRect1.h = wHeight;

	wRect2.x = SCREEN_WIDTH + 1 * distance + 450;
	wRect2.y = -200 - RanDom();
	wRect2.w = wWidth;
	wRect2.h = wHeight;

	wRect3.x = SCREEN_WIDTH + 2 * distance + 450;
	wRect3.y = -200 - RanDom();
	wRect3.w = wWidth;
	wRect3.h = wHeight;
	
	wRect11.x = wRect1.x;
	wRect11.y = wRect1.y + wHeight + space;
	wRect11.w = wWidth;
	wRect11.h = wHeight;

	wRect21.x = wRect2.x;
	wRect21.y = wRect2.y + wHeight + space;
	wRect21.w = wWidth;
	wRect21.h = wHeight;
	
	wRect31.x = wRect3.x;
	wRect31.y = wRect3.y+wHeight+space;
	wRect31.w = wWidth;
	wRect31.h = wHeight;
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
	
		if (wRect1.x <= SCREEN_WIDTH && wRect1.x > -getWidth())
		{
			wRender(screen, wRect1.x, wRect1.y);
			wRender(screen, wRect11.x, wRect11.y, 180);
		}


		if (wRect2.x <= SCREEN_WIDTH && wRect2.x > -getWidth())
		{
			wRender(screen, wRect2.x, wRect2.y);
			wRender(screen, wRect21.x, wRect21.y, 180);
		}
		

		if (wRect3.x <= SCREEN_WIDTH && wRect3.x > -getWidth())
		{
			wRender(screen, wRect3.x, wRect3.y);
			wRender(screen, wRect31.x, wRect31.y, 180);
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
	

		if (wRect1.x < -getWidth())
		{
			wRect1.x = wRect3.x + distance;
			wRect1.y = -200 - RanDom();
			
			wRect11.x = wRect1.x;
			wRect11.y = wRect1.y + wHeight + space;
		}
		if (wRect2.x < -getWidth())
		{
			wRect2.x = wRect1.x + distance;
			wRect2.y = -200 - RanDom();
			
			wRect21.x = wRect2.x;
			wRect21.y = wRect2.y + wHeight + space;
		}
		if (wRect3.x < -getWidth())
		{
			wRect3.x = wRect2.x + distance;
			wRect3.y = -200 - RanDom();
			
			wRect31.x = wRect3.x;
			wRect31.y = wRect3.y + wHeight + space;
		}

	
}
void waterPile::DoRun(SDL_Rect player)
{

	wRect1.x += xval;
	wRect2.x += xval;
	wRect3.x += xval;
	wRect11.x += xval;
	wRect21.x += xval;
	wRect31.x += xval;
	col1 = CheckCollision(wRect1, player);
	col2 = CheckCollision(wRect2, player);
	col3 = CheckCollision(wRect3, player);
	col4 = CheckCollision(wRect11, player);
	col5 = CheckCollision(wRect21, player);
	col6 = CheckCollision(wRect31, player);

	
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
bool waterPile::GetScore(SDL_Rect player)
{
	if ((player.x+1 > (wRect1.x + wWidth)&&player.x<(wRect1.x+wWidth+4))
	|| (player.x +1> (wRect2.x + wWidth)&&player.x<(wRect2.x+wWidth+4)) 
	|| (player.x +1> (wRect3.x + wWidth)&&player.x<(wRect3.x+wWidth+4)))
		checkpass = true;
	else
	{
		checkpass = false;
	}
	return checkpass;
}