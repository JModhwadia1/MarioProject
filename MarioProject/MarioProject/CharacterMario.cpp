#include "CharacterMario.h"



CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position):Character(renderer, imagePath, start_position)
{
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load character texture!" << std::endl;
	}
	
	
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	
	switch (e.type)
	{

		//Key pressed
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				Jump();
			}
			break;
		}
		break;
		//key released
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;

		case SDLK_RIGHT:
			m_moving_right = false;
			break;

		/*case SDLK_UP:
			m_can_jump = false;
			break;*/
		}
		break;
	}
	Character::Update(deltaTime, e);

}

