#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "constant.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function prototypes
bool InitSDL();
bool CLoseSDL();


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		SDL_Delay(5000);
	}
	CLoseSDL();
	return 0;
	
	
		


}
bool InitSDL()
{
	//setup sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not intialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
}
bool CLoseSDL()
{
	//release the window 
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return true;
}
	






