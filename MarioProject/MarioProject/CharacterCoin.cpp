#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, float movementSpeed) : Character (renderer, imagePath, start_position, map)
{
	m_movement_speed = movementSpeed;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	std::cout << "X: " << m_position.x << " " << "Y: " << m_position.y << std::endl;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);
	if(!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load character texture!" << std::endl;
	}
	std::cout << "coin constructor ran" << std::endl;
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Render()
{

	
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	//Character::Update(deltaTime, e);
	//m_position.x += MOVEMENTSPEED * deltaTime;
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//reset frame delay count
		m_frame_delay = ANIMATION_DELAY;

		//move the frame over
		m_current_frame++;

		//loop frame around if it goes beyond the number of frames
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}

	}
}
