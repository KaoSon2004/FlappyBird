#include "TextureManager.h"
TextureManager::TextureManager()
{
	Mtexture = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}
TextureManager::~TextureManager()
{
	Free();
}
bool TextureManager::LoadImg(string path, SDL_Renderer* screen)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
		if (newTexture != NULL)
		{
			rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}
	}
	Mtexture = newTexture;
	SDL_FreeSurface(loadedSurface);
	return Mtexture != NULL;
}
void TextureManager::Render(SDL_Renderer* des, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { rect_.x,rect_.y,rect_.w,rect_.h };
	SDL_RenderCopy(des, Mtexture, clip, &renderQuad);
}
void TextureManager::Free()
{
	if (Mtexture != NULL)
	{
		SDL_DestroyTexture(Mtexture);
		Mtexture = NULL;
	}
}