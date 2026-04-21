#include "GameSettings.h"

unsigned __int8 SnakeGame::GameSettings::lvl = 1;
bool SnakeGame::GameSettings::GAME_MUSIC = false;
bool SnakeGame::GameSettings::GAME_VOLUME = false;

void SnakeGame::GameSettings::setLVL(int s)
{
    if (s >= 0 && s <= 4)
        lvl = s;
}

int SnakeGame::GameSettings::getLVL()
{
    return GameSettings::lvl;
}

void SnakeGame::GameSettings::setGameMusic(bool f)
{
    GAME_MUSIC = f;
}

bool SnakeGame::GameSettings::getGameMusic()
{
    return GAME_MUSIC;
}

void SnakeGame::GameSettings::setGameVolume(bool f)
{
    GAME_VOLUME = f;
}

bool SnakeGame::GameSettings::getGameVolume()
{
    return GAME_VOLUME;
}
