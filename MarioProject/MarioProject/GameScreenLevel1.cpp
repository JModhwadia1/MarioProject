#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "CharacterKoopa.h"




GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	//m_level_map = nullptr;
	enemyToSpawnCountdown = KOOPA_SPAWN_DELAY;
	
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete luigi;
	delete mario;
	mario = nullptr;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_enemies.clear();

	m_background_texture = nullptr;
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	//do screen shake if required
	
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}

	}
	enemyToSpawnCountdown -= deltaTime;
	if (enemyToSpawnCountdown <= 0)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		enemyToSpawnCountdown = KOOPA_SPAWN_DELAY;
	}

	//update character
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	//collisions
	/*if (Collisions::Instance()->Circle(mario, luigi))
	{
		cout << "Circle hit!" << endl;
	}*/
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		cout << "Box hit" << endl;
	}
	UpdatePOWBLOCK();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);

}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	mario->Render();
	luigi->Render();
	m_pow_block->Render();
	
}
bool GameScreenLevel1::SetUpLevel()
{
	
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	SetLevelMap();

	//set up koopa 
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	//set up coins
	CreateCoins(Vector2D(150, 32), COIN_SPEED);
	CreateCoins(Vector2D(325, 32), COIN_SPEED);

	//set up player character
	mario =  new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64,330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 330), m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

	return true;

	
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	
	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	mapSprites = new Texture2D(m_renderer);
	if (!mapSprites->LoadFromFile("Images/Spritesheet.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

	//set the new one
	m_level_map = new LevelMap(map);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{

			switch (map[i][j])
			{
			case 1:
				//Tile::tex = new Texture2D::LoadFromFile("Images/Spritesheet.png")
				Tile floor;
				floor.tex = mapSprites;
				floor.pos = new Rect2D(i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
				floor.spriteSheetPos = new Rect2D( 16, 296,TILE_WIDTH,TILE_HEIGHT );
				break;
			case 2:
				//Tile::tex = new Texture2D::LoadFromFile("Images/Spritesheet.png")
				Tile powBlock;
				powBlock.tex = mapSprites;
				powBlock.pos = new Rect2D(i * TILE_WIDTH, j * TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT);
				//powBlock.spriteSheetPos = new Rect2D()
				break;
		

		
			default:
				break;
			}
			
		}

	}



}
void GameScreenLevel1::UpdatePOWBLOCK()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}
		}
	}
}
void GameScreenLevel1::DoScreenShake()
{

	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to left / right
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetAlive(false);
				}
					
			}
			//now do the update
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					if (m_enemies[i]->GetIsInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						if (mario->GetAlive())
						{
							mario->SetAlive(false);
						}
					}
				}
			}
			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopa = new CharacterKoopa (m_renderer, "Images/Koopa.png", position, m_level_map,direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoins(Vector2D position, float speed)
{
	CharacterCoin* coins = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map, speed);
	m_coins.push_back(coins);
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	for (unsigned int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Update(deltaTime, e);

		if (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), mario->GetCollisionBox()))
		{
			m_coins[i]->SetAlive(false);
			cout << "coin is dead" << endl;
		}
		if (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), luigi->GetCollisionBox()))
		{
			m_coins[i]->SetAlive(false);
		}
		
	}
}
