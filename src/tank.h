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

#include "tankbullet.h"

class Tank{

public:

	//is the player actice- still?
	bool active;

	//variable to hold the list of bullets
	vector<TankBullet> bulletList;

	//string to thold the path to the platyers texture
	string playerPath;

	//integer for the platers nunbemer
	int playerNum;

	//players texture to hold img
	SDL_Texture *texture;

	//players SDL_Rect for the X, Y, W, and H of texture
	SDL_Rect posRect;

	//floats to hold the joystick axis(-1 or 0 or 1)
	float xDir, xDirOld;
	float yDir, yDirOld;

	//float for player speed
	float speed;

	//float for the players position to avoid precision
	float pos_X, pos_Y;

	//vars used to get the angel betwene the tanks position and the joystick position
	float x, y, tankangle;

	//point that will be used to rotate the turret, relative to the turrets barrels rext
	SDL_Point center;

	//keep the last angle to hte player can fire in the correct firaction
	float oldAngle;

	//audio sound effect - CHUNK
	Mix_Chunk *fire;

	//add x and y
	Sint16 Xvalue, Yvalue;

	//players creatoin method using passed in balues for renderer player number path to the texture
	//starting posinot x starting positno y
	Tank(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y);

	//mathod to allow the player the move bia joystick axis
	void OnControllerAxis(Sint16 X, Sint16 Y);

	//method to allow the players interect with the joystick buttons
	void OnControllerButton(const SDL_ControllerButtonEvent event);

	//update th e playre using the passed in DeltaTime
	void Update(float deltaTime);

	//draw the player main passed in renderer
	void Draw(SDL_Renderer * renderer);

	//reset the player
	void Reset();

private:

	void CreateBullet();
};
