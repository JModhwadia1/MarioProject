#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "CharacterMario.h"
#include "CharacterLuigi.h"


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete luigi;
	delete mario;
	mario = nullptr;
	luigi = nullptr;
	m_background_texture = nullptr;
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	//update character
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
};
void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	mario->Render();
	luigi->Render();
}
bool GameScreenLevel1::SetUpLevel()
{
	
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//set up player character
	mario =  new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64,330));
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(128, 330));
}
