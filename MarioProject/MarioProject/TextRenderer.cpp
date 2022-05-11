//#include "TextRenderer.h"
//#include <iostream>
//TextRenderer::TextRenderer(SDL_Renderer* renderer)
//{
//	m_renderer = renderer;
//}
//
//TextRenderer::~TextRenderer()
//{
//	m_renderer = nullptr;
//}
//
//void TextRenderer::Render(int xPosition, int yPosition)
//{
//	text_rect.x = xPosition;
//	text_rect.y = yPosition;
//	SDL_RenderCopy(m_renderer, m_texture, nullptr, &text_rect);
//}
//
//bool TextRenderer::LoadFont(const string file_path, const int fontSize, const string message, SDL_Color)
//{
//	font = TTF_OpenFont(file_path.c_str(), fontSize);
//	if (!font)
//	{
//		std::cout << "font is not initialised" << std::endl;
//		
//	}
//	
//	
//
//	
//	return false;
//}
