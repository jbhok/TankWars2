#include <string>
#include <iostream>
#include <math.h>
using namespace std;

#if defined (__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif

class TurretBullet{

public:
//boolean for state of enemy
bool active;

//enemy texture
SDL_Texture *texture;

//enemy rectanbel for position(x,y) and size(h,w)
SDL_Rect posRect;

//enemy speed
float speed;

//enemy float posiitons to prevent precision loss
float pos_X, pos_Y;

//position for the player
SDL_Point turret, player;

//distance between the 2
float distance;

TurretBullet(SDL_Renderer *renderer, string filePath, float x, float y);

void Start(SDL_Rect playerPos, SDL_Rect turretPos);

void Reset();

void Draw(SDL_Renderer * renderer);

void Update(float deltaTime);
};
