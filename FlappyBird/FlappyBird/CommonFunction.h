#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <ctime> 
#include <fstream>
using namespace std;


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;

//screen
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 1200;

//color key
const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

bool CheckCollision(SDL_Rect a, SDL_Rect b);

static int  score = 0;