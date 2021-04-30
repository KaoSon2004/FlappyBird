#pragma once
#include "CommonFunction.h"
class TextureManager
{
private:
	SDL_Texture* Mtexture;
	SDL_Rect rect_;
public:
	TextureManager();
	~TextureManager();
	void SetRect(int x, int y) { rect_.x = x, rect_.y = y; }
	//SDL_Rect GetRect() { return rect_; }
	bool LoadImg(string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, SDL_Rect* clip=NULL);
	void Free();
};