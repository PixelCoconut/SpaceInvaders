//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>
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

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
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

	//Load music
	gMusic = Mix_LoadMUS("brainybetty.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gHigh = Mix_LoadWAV("high.wav");
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gMedium = Mix_LoadWAV("medium.wav");
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gLow = Mix_LoadWAV("low.wav");
	if (gLow == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Free the sound effects
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	SDL_Quit();
}

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
					else if (e.type == SDL_KEYDOWN)
					{
						const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
						//Select surfaces based on key press

						if (currentKeyStates[SDL_SCANCODE_1])
						{
							Mix_PlayChannel(-1, gHigh, 0);
							printf("Played High Sound\n");
						}
							

						//Play medium sound effect
						if (currentKeyStates[SDL_SCANCODE_2])
						{
							Mix_PlayChannel(-1, gMedium, 0);
							printf("Played Medium Sound\n");
						}

						//Play low sound effect
						if (currentKeyStates[SDL_SCANCODE_f3])
						{
							Mix_PlayChannel(-1, gLow, 0);
							printf("Played Low Sound\n");
						}

						if (currentKeyStates[SDL_SCANCODE_0])
						{
							//If there is no music playing
							if (Mix_PlayingMusic() == 0)
							{
								//Play the music
								Mix_PlayMusic(gMusic, -1);
								printf("Play Music\n");
							}
							//If music is being played
							else
							{
								//If the music is paused
								if (Mix_PausedMusic() == 1)
								{
									//Resume the music
									Mix_ResumeMusic();
									printf("Resume Music\n");
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
									printf("Pause Music\n");
								}
							}
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