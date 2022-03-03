
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
#include <SDL.h>
#include <string>
#include "Commons.h"




class Texture2D
{
	public: 
		Texture2D(SDL_Renderer* renderer);
		~Texture2D();

		bool LoadFromFile(std::string path);
		void Free();
		void Render(Vector2D new_postion, SDL_RendererFlip flip, double angle = 0.0);

		int GetWidth();
		int GetHeight();

	private:
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;


		int m_width;
		int m_height;



};

#endif // _TEXTURE_H

