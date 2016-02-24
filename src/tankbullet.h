#include <string>
#include <iostream>

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

class TankBullet {

public:

	//boolean for tstate of bullet
	bool active;

	//bullet texture
	SDL_Texture *texture;

	//bullet rectangle for position x,y nand size w,h
	SDL_Rect posRect;

	//movemtn direction vbalues
	float xDir, yDir;

	///bullet speed
	float speed;

	//bullet float position to prevent precision ;pss
	float pos_X, pos_Y;

	float tankangle;

	//bullet creation method, requires the renderer, a path to the needed image, an x positon, a y position
	TankBullet(SDL_Renderer *renderer, string filePath, float x, float y, int dirX, int dirY);

	//bullet update, requires detlaTime be passed
	void Update(float deltaTime);

	//bullet Draw - require rednerer be passed
	void Draw(SDL_Renderer * renderer);

	//bullet destrctuiong method
	void Reset();

	//buyllet start
	void Start(SDL_Rect playerPos, SDL_Rect turretPos);

};
