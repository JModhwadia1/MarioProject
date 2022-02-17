#include "Texture2D.h"
#include <iostream>
#include <SDL_Image.h>
using namespace std;
Texture2D::Texture2D(SDL_Renderer* renderer)
{

	 m_renderer = renderer;

}
Texture2D::~Texture2D()
{
	Free();
	m_renderer = nullptr;
}
void Texture2D::Free()
{
	
	
	//free up memory
	if (m_texture != nullptr)
	{
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
	
}
void Texture2D::Render(Vector2D new_postion, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture
	SDL_Rect renderLocation = { new_postion.x,new_postion.y, m_width, m_height };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, angle, NULL, flip);
}


bool Texture2D::LoadFromFile(std::string path)
{
	Free();
	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
		
		
		//return the texture
		return m_texture != nullptr;
		
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
}
int Texture2D::GetWidth()
{
	return m_width;

}
int Texture2D::GetHeight()
{
	return m_height;
}



