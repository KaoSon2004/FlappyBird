#pragma once
#include "HighScore.h"
highScore::highScore()
{
	score = 0;
}
highScore::~highScore()
{

}
bool highScore::loadFromFile(string path)
{
	this->path = path;
	ifstream fileIn;
	fileIn.open(path.c_str(), ios_base::in);
	if (fileIn.fail())
		return false;
	fileIn >> score;
	fileIn.close();
	return true;
	
}
void highScore::saveScore(int x)
{
	ofstream fileOut;
	fileOut.open(path.c_str(),ios_base::out);
	fileOut << x;
	fileOut.close();
}