#pragma once
#include "CommonFunction.h"
class highScore
{
private:
	int score;
	string path;
public:
	highScore();
	~highScore();
	int GetScore() { return score; }
	void SetScore(int x) { score = x; }
	bool loadFromFile(string path);
	void saveScore(int x);
};