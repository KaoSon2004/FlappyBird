#include "TextObject.h"
TextObject::TextObject()
{
	textCoLor.r = 255;
	textCoLor.g = 255;
	textCoLor.b = 255;
	tTexture = NULL;
}
TextObject::~TextObject()
{

}
bool TextObject::loadFromtRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, strVal.c_str(), textCoLor);
	if (text_surface)
	{
		tTexture = SDL_CreateTextureFromSurface(screen, text_surface);
		tWidth = text_surface->w;
		tHeight = text_surface->h;
		SDL_FreeSurface(text_surface);

	}
	return tTexture != NULL;
}
void TextObject::Free()
{
	if (tTexture != NULL)
	{
		SDL_DestroyTexture(tTexture);
		tTexture = NULL;
	}
}
void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	textCoLor.r = red;
	textCoLor.g = green;
	textCoLor.b = blue;

}
void TextObject::SetColor(int type)
{
	if (type==RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };
		textCoLor = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255,255,255 };
		textCoLor = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0,0,0 };
		textCoLor = color;
	}
}
void TextObject::RenderText(SDL_Renderer* screen, int xpos, int ypos, SDL_Rect* clip , double angle , SDL_Point* center , SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { xpos,ypos,tWidth,tHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, tTexture,clip, &renderQuad, angle, center, flip);
}