#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movementSpeed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_position = start_position;
	m_movement_speed = movementSpeed;

	m_injured = false;
	isAlive = true;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load character texture!" << std::endl;
	}

}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time - INJURED_TIME;
	Jump();

}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = false;
		m_can_jump = false;
	}
}

void CharacterKoopa::Render()
{
	//VARIABLES TO HOLD THE LEFT POSITION OF THE SPRITE WE WANT TO DRAW
	int left = 0.0f;

	//IF INJURED MOVE THE LEFT POSITION TO BE THE LEFT POSITION OF THE SECOND IMAGE OF THE SPRITE SHEET
	if (m_injured)
	{
		left = m_single_sprite_w;
	}
	//GET THE PORTION OF THE SPRITE SHEET YOU WANT TO DRAW
	//				{XPOS, YPOS , WIDTH OF SPRITE, HEIGHT OF SPRITE}
	SDL_Rect portionOfSprite{ left, 0, m_single_sprite_w, m_single_sprite_h };
	
	//DETERMINE WHERE YOU WANT IT DRAWN
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//THEN DRAW IT FACING THE CORRECT DIRECTION
	
		if (m_facing_direction == FACING_RIGHT)
		{
			m_texture->Render(portionOfSprite, destRect, SDL_FLIP_NONE);
		}
		else
		{
			m_texture->Render(portionOfSprite, destRect, SDL_FLIP_HORIZONTAL);
		}

	
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//USE THE CODE WITHIN THE BASE CLASS
	Character::Update(deltaTime, e);
	if (!m_injured)
	{
		//ENEMY IS NOT INJURED SO MOVE
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}

	}
	else
	{
		//WE SHOULD NOT BE MOVING WHEN INJURED
		m_moving_left = false;
		m_moving_right = false;

		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
		{
			FlipRightwayUp();
		}
	}
	if (m_position.x > SCREEN_WIDTH)
	{
		
	}
	
}




void CharacterKoopa::FlipRightwayUp()
{
	m_facing_direction = (m_facing_direction == FACING_RIGHT ? FACING_LEFT : FACING_RIGHT);
	m_injured = false;
	Jump();
}
