//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
//My screen width and height are smaller due to having a smaller screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gXOut = SDL_LoadBMP("x.bmp");
	if (gXOut == NULL)
	{
		printf("x.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

char keystate[10] = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//User presses a key
					else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
					{
						const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

						//Key 0
						if (currentKeyStates[SDL_SCANCODE_0])
						{
							keystate[9] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[9] = '-';

						//Key 1
						if (currentKeyStates[SDL_SCANCODE_1])
						{
							keystate[0] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[0] = '-';

						//Key 2
						if (currentKeyStates[SDL_SCANCODE_2])
						{
							keystate[1] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[1] = '-';

						//Key 3
						if (currentKeyStates[SDL_SCANCODE_3])
						{
							keystate[2] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[2] = '-';

						//Key 4
						if (currentKeyStates[SDL_SCANCODE_4])
						{
							keystate[3] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[3] = '-';

						//Key 5
						if (currentKeyStates[SDL_SCANCODE_5])
						{
							keystate[4] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[4] = '-';

						//Key 6
						if (currentKeyStates[SDL_SCANCODE_6])
						{
							keystate[5] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[5] = '-';

						//Key 7
						if (currentKeyStates[SDL_SCANCODE_7])
						{
							keystate[6] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[6] = '-';

						//Key 8
						if (currentKeyStates[SDL_SCANCODE_8])
						{
							keystate[7] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[7] = '-';

						//Key 9
						if (currentKeyStates[SDL_SCANCODE_9])
						{
							keystate[8] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[8] = '-';

						//Key 9
						if (currentKeyStates[SDL_SCANCODE_9])
						{
							keystate[8] = 'X';
							printf(keystate);
							printf("\n");
						}
						else
							keystate[8] = '-';

						//Key f
						if (currentKeyStates[SDL_SCANCODE_F])
						{
							printf("Alpha key has been pressed");
							printf("\n");
						}
					}
				}

				//Apply the image
				SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}