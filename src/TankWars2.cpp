#include <iostream>
#include <stdio.h>
#include <string>
#include <stdint.h>

using namespace std;

//screen dimension onstants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

//deltaTime car initialization - for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

#include "tank.h"
#include "turret.h"

#if defined (__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

string currentWorkingDirectory (getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";
#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <direct.h>
#define get cwd _getcwd

string currentWorkingDirectory (getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "\\src\\";
string audio_dir = currentWorkingDirectory + "\\src\\";
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#include <unistd.h>

string currentWorkingDirectory (getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";
#endif

//main start *********************************************************************
int main(){

	// *****CREAT ETHE SDL WINDOW - START &&&&&&
	//start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);

	//create a SDL Window reference - pointer
	SDL_Window *window = NULL;

	//create a SDL renderTarget - pointer
	SDL_Renderer *renderer = NULL;

	//create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("Tank Wars!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);





	//create an SDL RenderTaret
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// *********CREATE THE SDL WINDOW - END **********

	// *********caraubke creatuib - start**********
	//main loop flag
	bool quit =false;

	//event handler
	SDL_Event e;
	//*************baraibel creation - end**********

	//***Turn on Game controller Eventws *****
	SDL_GameControllerEventState(SDL_ENABLE);

	//****set up a Game Controller vaiable for player 1 *****
	SDL_GameController* gGameController0 = NULL;

	// ***Open Game Controller for player 1 ****
	gGameController0 = SDL_GameControllerOpen(0);

	//open audio channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//load a music file
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "BenJamin_Banger_-_03_-_Delfino_Plaza_httpsbenjaminbangerbandcampcomalbumse7en.mp3").c_str());

	//if music file isnt' playing, play it
	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	//cREATE PLAYERS START*******************************************
	Tank tank1 = Tank(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 50.0f,50.0f);

	//cREATE TURRET START*******************************************
	Turret turret1 = Turret(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 800.0f, 800.0f);

	// MAIN GAME LOOP START ************

	while(!quit)
	{
		//create deltaTime - for grame reate independence
		thisTime= SDL_GetTicks();
		deltaTime=(float)(thisTime-lastTime)/1000;
		lastTime=thisTime;

		//handle events on queue -Keypresses and such START ********
		while(SDL_PollEvent(&e)!= 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit=true;
			}

			switch (e.type){
			case SDL_CONTROLLERBUTTONDOWN:

				if(e.cdevice.which == 0){

					if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A){

						tank1.OnControllerButton(e.cbutton);
						break;
					}
				}

				break;

			case SDL_CONTROLLERAXISMOTION:

				tank1.OnControllerAxis(e.caxis);

				break;

			}

		}//POLL EVENT

		//update player 1 tank************************************
		tank1.Update(deltaTime);

		turret1.Update(deltaTime, tank1.posRect);


		//draw player 1 tank************************************
		//claer the SDL RenderTarget
		SDL_RenderClear(renderer);
		//draw the tank
		tank1.Draw(renderer);
		//draw the tuuret
		turret1.Draw(renderer);
		//present new buffer to screen
		SDL_RenderPresent(renderer);


	}// end main loop

	//close and destroy the window
	SDL_DestroyWindow(window);

	//clean up
	SDL_Quit();

	return 0;

}
