#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "constant.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//Function prototypes
bool InitSDL();
bool CLoseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextFromFile(string path);
void FreeTexture();


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//flag to check if we wish to quit
		bool quit = false;
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CLoseSDL();
	Update();
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
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imageFlags)& imageFlags))
			{
				cout << "SDL Image could not initialise. Error:" << IMG_GetError();
				return false;
			}
			//Load the background texture
			g_texture = LoadTextFromFile("Images/test.bmp");
			if (g_texture == nullptr)
			{
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
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
bool Update()
{
	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click the 'x' to quit
	case SDL_QUIT:
			return true;
			break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		}
			
	}
	return false;
}
void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//set where to render the texture
	SDL_Rect renderLocation = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);
}
SDL_Texture* LoadTextFromFile(string path)
{
	//remove memory used for a previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
		
		
		//return the texture
		return p_texture;
		
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
}
void FreeTexture()
{
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;

		//clear the texture
		FreeTexture();
		//release the renderer
		SDL_DestroyRenderer(g_renderer);
		g_renderer = nullptr;
	}
}





