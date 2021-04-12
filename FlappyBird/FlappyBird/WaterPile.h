#pragma once
#include "CommonFunction.h"
class waterPile
{
public:
	waterPile();
	~waterPile();
	void Init();
	void wRender(SDL_Renderer* screen,int x, int y, int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void wUpdate();
	bool LoadImg(string path, SDL_Renderer* screen);
	int getWidth() { return wWidth; }
	int getHeight() { return wHeight; }
	void setRect(int _x, int _y);
	void loadWaterPile(SDL_Renderer* screen);
	void DoRun(SDL_Renderer* screen);
	void Free();
private:
	int xpos, ypos;
	int wWidth;
	int wHeight;
	SDL_Texture* wTexture;
	int distance = 400;
	int space = 200;

	int xval = -4;

};
