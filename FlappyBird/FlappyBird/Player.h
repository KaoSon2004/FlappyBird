#pragma once
#include "CommonFunction.h"
class Bird
{
public:
	Bird();
	~Bird();
	bool loadImg(string path, SDL_Renderer* des);
	void SetRect(int x, int y) { birdrect.x = x,birdrect.y = y; }
	SDL_Rect GetRect() { return birdrect; }
	void HandleInputAction(SDL_Event e, SDL_Renderer* screen);
	void Free();
	void Show(SDL_Renderer* des,SDL_Rect* clip=NULL);
	bool CheckCollision(const SDL_Rect& object2);


	void DoFalling(SDL_Renderer* des);
	void Move();
	

	
	bool GetIsDie() { return isDie; }
	void SetIsDie(bool die) { isDie = die;}
	void SetYVal(int y) { yval = y; }

	bool GameOver();
private:
	// bước nhảy

	float yval;
	//vị trí hiện tại
	bool isDie;
	SDL_Texture* bird;
	SDL_Rect birdrect;


};
