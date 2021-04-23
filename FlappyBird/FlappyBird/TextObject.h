#pragma once
#include "CommonFunction.h"
class TextObject
{
public:
	TextObject();
	~TextObject();
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT=2,
	};
	bool loadFromFile(string path);
	bool loadFromtRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	void RenderText(SDL_Renderer* screen, int xpos, int ypos, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth() { return tWidth; }
	int GetHeight() { return tHeight; }
	void SetText(string& text) { strVal = text; }
	string GetText() { return strVal; }
private:
	string strVal;
	SDL_Color textCoLor;
	SDL_Texture* tTexture;
	int tWidth;
	int tHeight;

};