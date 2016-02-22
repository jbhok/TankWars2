#include "tank.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//tank creation
Tank::Tank(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{
	//active the plater
	active = true;

	//set the player number 0 or 1
	playerNum = pNum;

	//set float for player speed
	speed = 200.0f;

	//tank firing sound
	fire = Mix_LoadWAV((audioPath + "fire.wav").c_str());

	//see if this is player 1 or 2
	if(playerNum == 0){
		//create red tank texture
		playerPath = filePath + "tank.png";
	}else{
		//create the blue tank texture
		playerPath = filePath +"tank2.png";
	}

	//load the surface into the teture
	texture = IMG_LoadTexture(renderer, playerPath.c_str());

	//set the SDL_Rext X and Y for the player
	posRect.x = x;
	posRect.y = y;

	//use SDL_Querytexture to get the w and h of players texture
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	//set the movments floats to the players original x and y
	pos_X = x;
	pos_Y = y;

	//set the xdir and ydir
	xDir=0;
	yDir=0;

	//set the initial values so tank cn shoot
	xDirOld=1;
	yDirOld=0;

	//center of inamge rectangel
	center.x= posRect.w/2;
	center.y= posRect.h/2;

	//string to create the path to the players pullet image
	string bulletPath;

	//see if this is player 1 or 2
	if(playerNum == 0){
		//create red tank texture
		playerPath = filePath + "tank.png";
	}else{
		//create the blue tank texture
		playerPath = filePath +"tank2.png";
	}

	//dcreate player bullets
	for(int i = 0; i <10; i++)
	{
		//creat the bullet and move offscreen out of the game play area
		TankBullet tmpBullet(renderer, bulletPath, -1000, -1000, 0,0);

		//add to bulletlist
		bulletList.push_back(tmpBullet);
	}

}

//tank draw mtehod
void Tank::Draw(SDL_Renderer *renderer)
{

	//draw the enemies
	for(int i = 0; i <bulletList.size(); i++)
	{
		//check see if bullet acitve
		if(bulletList[i].active){

			//draw bullet
			bulletList[i].Draw(renderer);
		}
	}


	//draw the player texture using the cars texture and posRext
	SDL_RenderCopy(renderer, texture, NULL, &posRect, tankangle, &center, SDL_FLIP_NONE);
}

//tank update method
void Tank::Update(float deltaTime)
{
	//check for gamepad iput
	if(Xvalue != 0 || Yvalue !=0){
		//get the angle between the tank and the turret
		//x=posRect.x = xDir;
		//y=posRect.y = yDir;
		tankangle = atan2(Yvalue, Xvalue)*180/3.14;
		//ajust position floats based on speed direction of joystick and deltatime
		oldAngle = tankangle;
		//xDirOld= xDir;
		//yDirOld=yDir;

		//gives us radians
		float radians = (tankangle * 3.14) / 180;

		//get x and y
		float move+x = speed * cos (radians);
		float move_y = speed * sin (radians);

		//update flaots for precision loss
		pos_X += (move_x) * deltaTime;
		pos_Y += (move_y) * deltaTime;

		//update [a;lyer [osotion with code to account forp recision loss
		posRect.x = (int)(pos_X + 0.5f);
		posRect.y = (int)(pos_Y + 0.5f);

	} else{
		tankangle = oldAngle;
	}
/*
	//ajust position floats based on speed direction of joystick and deltatime
	pos_X += (speed * xDir) * deltaTime;
	pos_Y += (speed * yDir) * deltaTime;

	//uypdate player positon wuth code to account for precision loss
	posRect.x=(int)(pos_X + 0.5f);
	posRect.y=(int)(pos_Y + 0.5f);
*/
	if(posRect.x < 0){
		posRect.x = 0;
		pos_X = posRect.x;
	}


	if(posRect.x > 1024 - posRect.w){
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}

	if(posRect.y<0){
		posRect.y = 0;
		pos_Y=posRect.y;
	}

	if(posRect.y > 768 - posRect.h){
		posRect.y = 768 - posRect.h;
		pos_Y= posRect.y;
	}


	//Update the players bullets
	for(int i = 0; i < bulletList.size(); i++)
	{
		//check to see if the bullet is active
		if(bulletList[i].active){

			//update bullet
			bulletList[i].Update(deltaTime);
		}
	}


}

//tank joystick axis method
void Tank::OnControllerAxis(Sint16 X, Sint16 Y)
{

	Xvalue =X;
	Yvalue=Y;

	if(!(Xvalue < -JOYSTICK_DEAD_ZONE) && !(Xvalue > JOYSTICK_DEAD_ZONE))
	{
		Xvalue = 0.0f;
	}

	if(!(Yvalue < -JOYSTICK_DEAD_ZONE) && !(Yvalue > JOYSTICK_DEAD_ZONE))
	{
			Yvalue = 0.0f;
		}
}

//tank joystick button method
void Tank::OnControllerButton(const SDL_ControllerButtonEvent event)
{
	//if the players number is 0 and the joystick button is from joystick 0
	if(event.which == 0 && playerNum == 0)
	{
		//if A button
		if(event.button == 0)
		{
			//create bullet
			CreateBullet();
		}
	}

	//if the players number is 1 and the joystick button is from joystick 1
	if(event.which == 1 && playerNum == 1)
	{
		// if A button
		if(event.button == 0)
		{
			//create bullet
			CreateBullet();

		}
	}
}

//create a bullet
void Tank::CreateBullet(){

	//see if there is a bullet active to fire
	for(int i = 0; i < bulletList.size(); i++)
	{
		//see if the bullet is not active
		if(bulletList[i].active == false){

			//player over sound
			Mix_PlayChannel(-1, fire, 0);

			//set bullet to active
			bulletList[i].active = true;

			//use some math in the x position to get the bullet close
			//to the center of the player using player width
			bulletList[i].posRect.x = (posRect.x + (posRect.w/2));
			bulletList[i].posRect.y = (posRect.y + (posRect.h/2));

			//finish aligning to the player center using the texture width
			bulletList[i].posRect.x = bulletList[i].posRect.x -(bulletList[i].posRect.w/2);
			bulletList[i].posRect.y = bulletList[i].posRect.y -(bulletList[i].posRect.h/2);

			//set the x and y position of the bullets float positons
			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y ;

			//if the tank is moving fire in the direction
			if(xDir != 0 || yDir != 0){
				//set the x and y posiiotn
				bulletList[i].tankangle = tankangle;

			}else{
				//if the tank is not moving
				//set the x and y posoitino
				bulletList[i].tankangle = oldAngle;

			}

			//one hte bullt is found
			break;
		}
	}
}
