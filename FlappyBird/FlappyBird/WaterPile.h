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
	void DoRun(SDL_Rect player);
	int RanDom();
	void Free();
	SDL_Rect GetPos() {return wRect; }
	void SetPos(int x, int y);
	bool GetCollisionState() { return col; }
	void SetXPos(int x) { wRect.x = x;}
	void SetYPos(int y) { wRect.y = y; }
	
private:
	SDL_Rect wRect;
	int wWidth;
	int wHeight;
	SDL_Texture* wTexture;
	int distance = 400;
	int space = 200;
	bool col = false;
	int xval = -4;

};
