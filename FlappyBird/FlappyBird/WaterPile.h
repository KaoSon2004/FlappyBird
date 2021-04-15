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
	bool GetCollisionState1() { return col1; }
	bool GetCollisionState2() { return col2; }
	bool GetCollisionState3() { return col3; }
	bool GetCollisionState4() { return col4; }
	bool GetCollisionState5() { return col5; }
	bool GetCollisionState6() { return col6; }
	void SetXPos(int x) { wRect.x = x;}
	void SetYPos(int y) { wRect.y = y; }
	
private:
	SDL_Rect wRect;
	SDL_Rect wRect1;
	SDL_Rect wRect2;
	SDL_Rect wRect3;
	SDL_Rect wRect11;
	SDL_Rect wRect21;
	SDL_Rect wRect31;
	int wWidth;
	int wHeight;
	SDL_Texture* wTexture;
	int distance = 400;
	int space = 200;
	bool col1 = false;
	bool col2 = false;
	bool col3 = false;
	bool col4 = false;
	bool col5 = false;
	bool col6 = false;
	int xval = -4;

};
