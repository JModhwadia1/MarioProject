#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h" 
#include "Texture2D.h"
#include "LevelMap.h"
#include <vector>

using namespace std;



class Texture2D;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	CharacterMario* mario;
	CharacterLuigi* luigi;


	Texture2D* m_background_texture;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool SetUpLevel();
	void SetLevelMap();

	//Screen shake variables
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();

	//Enemy
	vector<CharacterKoopa*> m_enemies;
	float enemyToSpawnCountdown = 0;
	
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	
		
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBLOCK();
};
#endif

