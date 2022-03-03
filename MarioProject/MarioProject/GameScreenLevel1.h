#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Texture2D.h"


class Texture2D;
class CharacterMario;
class CharacterLuigi;

class GameScreenLevel1 : GameScreen
{
private:
	CharacterMario* mario;
	CharacterLuigi* luigi;
	Texture2D* m_background_texture;
	bool SetUpLevel();
	
		
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
};
#endif

