#include "Player.h"
Bird::Bird()
{
	isDie = false;
	yval = 5;
	bird = NULL;
}
Bird::~Bird()
{
	Free();
}
void Bird::HandleInputAction(SDL_Event e, SDL_Renderer* screen)
{
	if (isDie == false)
		if (e.type == SDL_KEYDOWN)
			if (e.key.keysym.sym == SDLK_SPACE)
				yval = -15;



}

bool Bird::loadImg(string path, SDL_Renderer* des)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xff,0xff, 0xff));
		newTexture = SDL_CreateTextureFromSurface(des, loadedSurface);
		if (newTexture != NULL)
		{
			birdrect.w = loadedSurface->w;
			birdrect.h = loadedSurface->h;
		}
	}
	bird = newTexture;
	SDL_FreeSurface(loadedSurface);
	return bird != NULL;
}
void Bird::Show(SDL_Renderer* des,SDL_Rect* clip)
{
	SDL_Rect renderQuad = { birdrect.x,birdrect.y,birdrect.w,birdrect.h };
	SDL_RenderCopy(des, bird, clip, &renderQuad);
}
void Bird::Free()
{
	if (bird != NULL)
	{
		SDL_DestroyTexture(bird);
		bird = NULL;
	}
}

void Bird::DoFalling(SDL_Renderer* des)
{
	if (isDie == false)
	{
		birdrect.y += yval;
		SetRect(birdrect.x, birdrect.y);
		if (birdrect.y >= (SCREEN_HEIGHT - birdrect.h))
		{
			isDie = true;
			yval = 0;
		}
	}
	else if (isDie==true)
	{
		
		if (birdrect.y >=0)
		{
			birdrect.y += 5;
		} 
	}
}
bool Bird::GameOver()
{
	if (birdrect.y + birdrect.h >= SCREEN_HEIGHT)
	{

		isDie = true;
		return true;
	}
	
}



