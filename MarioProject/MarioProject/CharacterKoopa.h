#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"
#include "Texture2D.h"
#include "Commons.h"
#include "constant.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Render()override;

	void Update(float deltaTime, SDL_Event e)override;
	bool GetInjured();
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	bool m_injured;
	bool m_injured_time;

	void FlipRightwayUp();
};

#endif // !_CharacterKoopa_H
