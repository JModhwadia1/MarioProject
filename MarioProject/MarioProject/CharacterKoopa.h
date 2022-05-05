#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"
#include "Texture2D.h"
#include "Commons.h"
#include "constant.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Render()override;

	bool GetAlive() { return m_alive; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }

	void Update(float deltaTime, SDL_Event e)override;
	bool GetIsInjured() { return m_injured;};
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	bool m_injured;
	bool m_injured_time;

	float m_movement_speed;
	bool m_alive;

	void FlipRightwayUp();
	void ChangeDirection();
};

#endif // !_CharacterKoopa_H
