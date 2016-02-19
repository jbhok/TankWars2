#include "turret.h"

//tank creation
Turret::Turret(SDL_Renderer *renderer, string filePath, string audioPath, float x, float y)
{
	//active the plater
	active = true;

	//tank firing sound
	fire = Mix_LoadWAV((audioPath + "fire.wav").c_str());

	//create the turret base file path
	string basePath = filePath + "turretBase.png";

	//load the surface into the teture
	tBase = IMG_LoadTexture(renderer, basePath.c_str());

	//create the turret base file path
	string barrelPath = filePath + "turretBarrel.png";

	//load the surface into the teture
	tBarrel = IMG_LoadTexture(renderer, barrelPath.c_str());

	//set the SDL_Rext X and Y for the player
	baseRect.x = x;
	baseRect.y = y;

	//use SDL_Querytexture to get the w and h of players texture
	int w, h;
	SDL_QueryTexture(tBase, NULL, NULL, &w, &h);
	baseRect.w = w;
	baseRect.h = h;

	//set the SDL_Rext X and Y for the player
	barrelRect.x = x + 34;
	barrelRect.y = y + 34;

	//use SDL_Querytexture to get the w and h of players texture
	SDL_QueryTexture(tBarrel, NULL, NULL, &w, &h);
	barrelRect.w = w;
	barrelRect.h = h;

	//create the center point
	center.x= 12;
	center.y= 12;

	//string to create the path to the players bullet image
	string bulletPath = filePath + "bullet.png";

	//dcreate player bullets
	for(int i = 0; i <10; i++)
	{
		//creat the bullet and move offscreen out of the game play area
		//TurretBullet tmpBullet(renderer, bulletPath, 500, 500);

		//add to bulletlist
		//bulletList.push_back(tmpBullet);
	}

	//random null init
	srand(time(NULL));
};


//tank draw mtehod
void Turret::Draw(SDL_Renderer *renderer)
{
/*
	//draw the enemies
	for(int i = 0; i <bulletList.size(); i++)
	{
		//check see if bullet acitve
		if(bulletList[i].active){

			//draw bullet
			bulletList[i].Draw(renderer);
		}
	}
*/
	//draw the player texture using the cars texture and posRext
	SDL_RenderCopy(renderer,tBase, NULL, &baseRect);

	//draw the player texture using the cars texture and posRext
	SDL_RenderCopyEx(renderer,tBarrel, NULL, &barrelRect, turretangle, &center, SDL_FLIP_NONE);

}

//bullet update method
void Turret::Update(float deltaTime, SDL_Rect tankRect){

		//adjust position floats based on speed, direction(-1 for up), and deltaTime
		x += (tankRect.x + (tankRect.w/2)) - (baseRect.x + (baseRect.w/2));
		y += (tankRect.y + (tankRect.h/2)) - (baseRect.y + (baseRect.h/2));
		turretangle = atan2(y,x) * 180/3.14;

		if(SDL_GetTicks()> fireTime){

			CreateBullet(tankRect);

			fireTime = SDL_GetTicks() + (rand() % 3 + 1) * 1000;
		}

		/*
		//update the turrests vullets
		for(int i = 0; i <bulletList.size(); i++)
			{
				//check see if bullet acitve
				if(bulletList[i].active){

					//draw bullet
					bulletList[i].Draw(renderer);
				}
			}*/
}


//create a bullet
void Turret::CreateBullet()
{
	/*
	//see if there is a bullet active to fire
	for(int i = 0; i < bulletList.size(); i++)
	{
		//see if the bullet is not active
		if(bulletList[i].active == false){

			bulletList[i].Start(target, baseRect);

			//player over sound
			Mix_PlayChannel(-1, fire, 0);

			//set bullet to active
			bulletList[i].active = true;

			//use some math in the x position to get the bullet close to
			//finish aligning to the player center using the texture width
			bulletList[i].posRect.x = ((baseRect.x + (baseRect.w/2)) -(bulletList[i].posRect.w/2));
			bulletList[i].posRect.y = ((baseRect.y + (baseRect.w/2)) -(bulletList[i].posRect.h/2));

			//set the x and y position of the bullets float positons
			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y ;

			//one hte bullt is found
			break;
		}
	}
	*/
}
