#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H
#include "Character.h"
#include "Texture2D.h"
#include "constant.h"



class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, float movementSpeed);
	~CharacterCoin();
	void Render()override;
	void Update(float deltaTime, SDL_Event e)override;
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;
	int m_current_frame;
	float m_movement_speed;

};
#endif

