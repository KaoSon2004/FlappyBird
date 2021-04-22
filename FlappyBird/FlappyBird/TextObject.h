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
	void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth() { return width_; }
	int GetHeight() { return height_; }
	void SetText(string& text) { str_val_ = text; }
	string GetText() { return str_val_; }
private:
	string str_val_;
	SDL_Color text_coLor_;
	SDL_Texture* texture_;
	int width_;
	int height_;

};