#include "Player.h"
Bird::Bird()
{

	

}
Bird::~Bird()
{
	Free();
}
void Bird::HandleInputAction(SDL_Event e, SDL_Renderer* screen)
{

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			{
				if ((birdrect.y) <= 0)
					yval = 5;
				else
				{
					yval = -15;
				}
				

			}
			}

		}
		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			{
				yval = 5;
	
			}
			break;
			}
		}
		else 
		{
			yval = 5;

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
void Bird::DoFalling(SDL_Renderer* des)
{
		birdrect.y += yval;
		SetRect(birdrect.x, birdrect.y);
		if (birdrect.y >= (SCREEN_HEIGHT - birdrect.h))
			isDie = true;

}




