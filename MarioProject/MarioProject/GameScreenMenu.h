#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include <iostream>
#include <SDL.h>
#include "GameScreen.h"

class Texture2D;

class GameScreenMenu : GameScreen
{
public:
    GameScreenMenu(SDL_Renderer* renderer);
    ~GameScreenMenu();

    void Render()override;


private:
    Texture2D* m_background_texture;



};

#endif