#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H
#include "Character.h"
#include "Texture2D.h"
#include "Commons.h"
#include "constant.h"

class CharacterMario : public Character 
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	void Update(float deltaTime, SDL_Event e)override;
};

#endif // !_CHARACTERMARIO_

