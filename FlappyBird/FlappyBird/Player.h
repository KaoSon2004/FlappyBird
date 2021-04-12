#pragma once
#include "CommonFunction.h"
class Bird
{
public:
	Bird();
	~Bird();
	bool loadImg(string path, SDL_Renderer* des);
	void SetRect(int x, int y) { birdrect.x = x,birdrect.y = y; }
	void HandleInputAction(SDL_Event e, SDL_Renderer* screen);
	void Free();
	void Show(SDL_Renderer* des,SDL_Rect* clip=NULL);


	void DoFalling(SDL_Renderer* des);
	bool GetFalling() const { return isFalling; }
	void SetFalling(bool falling) { isFalling = falling; }
	void DoGround(SDL_Renderer* screen);
	bool GetIsDie() const { return isDie; }
private:
	// bước nhảy

	float xval;
	float yval;
	//vị trí hiện tại
	float xpos;
	float ypos;
	bool isFalling;
	bool isDie;
	SDL_Texture* bird;
	SDL_Rect birdrect;


};
