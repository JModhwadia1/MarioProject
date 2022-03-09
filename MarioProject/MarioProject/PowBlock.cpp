#include "PowBlock.h"




PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture." <<imagePath <<std::endl;
		return;
	}
	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3; // there are three images in this sprite sheet in a row
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}
PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = NULL;
	m_level_map = nullptr;
}

void PowBlock::Render()
{
	if (m_num_hits_left < 0) 
	{ 
		return;
	}
	//get the portion of the sheet we want to draw
	int left = m_single_sprite_w * (m_num_hits_left - 1);

	//xPos, yPos, sprite sheet widht, sprite sheet height
	SDL_Rect portionOfSpriteSheet = { left, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where to draw it
	SDL_Rect destRect = {static_cast <int>(m_position.x), static_cast <int>(m_position.y), m_single_sprite_w, m_single_sprite_h };
	//draw the sprite
	m_texture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}	
void PowBlock::TakeHit()
{
	m_num_hits_left--;
	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}
