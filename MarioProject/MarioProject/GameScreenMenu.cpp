#include "Texture2D.h"
#include "GameScreenMenu.h"

using namespace std;

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
    m_background_texture = new Texture2D(renderer);
    if (!m_background_texture->LoadFromFile("Images/menu.png"))
    {
        cout << "Failed to load background texture!" << endl;
    }
}

GameScreenMenu::~GameScreenMenu()
{
    delete m_background_texture;
    m_background_texture = nullptr;
}

void GameScreenMenu::Render()
{
    m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
}