#include <string>
#include <iostream>

using namespace std;
#include <vector>

#if defined (__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif

//#include "turretbullet.h"
class Turret{

public:
	//is the player actice- still?
	bool active;

	//variable to hold the list of bullets
	//vector<TurretBullet> bulletList;

	//string to thold the path to the platyers texture
	string playerPath;

	//turret texture to hold img
	SDL_Texture *tBase;
	SDL_Texture *tBarrel;

	//players SDL_Rect for the X, Y, W, and H of texture
	SDL_Rect BaseRect;

	//players SDL_Rect for the X, Y, W, and H of texture
	SDL_Rect BarrelRect;

	//vars used to get the angelbetwen the turrests position and the tanks position
	float x, y, turretangle;

	//point center
	SDL_Point center;

	//flots for firetime and firereate
	float fireTime = 0.0f;
	float fireRate = 1000.0f; //one second

	//audio sound effect -chunk
	Mix_Chunk *fire;

	//turrets creation method
	//enemy creation method, requires the renderer, a path to the needed image
	Turret(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y);

	//update th e playre using the passed in DeltaTime
	void Update(float deltaTime, SDL_Rect tankRect);

	//draw the player main passed in renderer
	void Draw(SDL_Renderer * renderer);

	//reset the player
	void Reset();

	//create a bullet
	void CreateBullet(SDL_Rect target);

};
