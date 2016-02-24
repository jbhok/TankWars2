#include "turretbullet.h"

//bnullry creation method
TurretBullet::TurretBullet(SDL_Renderer *renderer, string filePath, float x, float y){

	//set bullet initla state
	active=false;

	//set bullet speed
	speed = 800.0;

	//loat the rexture to a suraface
	texture = IMG_LoadTexture(renderer, filePath.c_str());

	//set the width and height of the bullets rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w=w;
	posRect.h=h;

	//set the x and y positions of the bullet recangle
	//finishing aligning to the player center using texutr width
	posRect.x =x;
	posRect.y=y;

	//set the float posiiotn values of the texurre for precision loss
	pos_X = x;
	pos_Y = y;

}

//resert the bullet method
void TurretBullet::Start(SDL_Rect playerPos, SDL_Rect turretPos){

	player.x = playerPos.x;
	player.y = playerPos.y;

	turret.x = turretPos.x;
	turret.y = turretPos.y;

	distance = sqrt((player.x - turret.x) * (player.x - turret.x) + (player.y - turret.y) * (player.y - turret.y));
}

//Rest the bullet method
void TurretBullet::Reset(){

	//reset the x position off the screen
	posRect.x = -1000;

	//update the pos_x for precision
	pos_X = posRect.x;

	//deactivate the bullet
	active = false;
}

//bykket draw mthod
void TurretBullet::Draw(SDL_Renderer * renderer){
	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

//bullet update method
void TurretBullet::Update(float deltaTime)
{
	//get direction values to move with
	float vX = ((player.x - 32) - turret.x) / distance;
	float vY = ((player.y - 32) - turret.y) / distance;

	//increment the bullet position by vx and vy
	pos_X += (vX * speed *deltaTime);
	pos_Y += (vY * speed *deltaTime);

	//Update bullet posiiton with code to axount for precision loss
	posRect.x = (int) (pos_X + 0.5f);
	posRect.y = (int) (pos_Y + 0.5f);

	//check to see if the bullet is off the top of the screen
	//and deactivate and move off screen
	if((posRect.y < (0-posRect.h)) || (posRect.y >768) || (posRect.x <(0-posRect.w)) || (posRect.x >1024)){
		Reset();
	}

}
