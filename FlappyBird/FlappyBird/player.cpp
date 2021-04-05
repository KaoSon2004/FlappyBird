#include "Player.h"
Bird::Bird()
{
	isFalling = false;
	isDie = false;
	yval = 1;
	accelerate = 0;
	gravity = 0.02;
}
Bird::~Bird()
{
	Free();
}
void Bird::HandleInputAction(SDL_Event e, SDL_Renderer* screen)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (isFalling == false)
		{
			yval = -20;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		yval = 5;

	}
	else
	{
		Gravity();
	}
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
void Bird::Gravity()
{
	accelerate = accelerate + 0.035;
	
	birdrect.y = birdrect.y + gravity + accelerate ;
	SetRect(birdrect.x, birdrect.y);
}