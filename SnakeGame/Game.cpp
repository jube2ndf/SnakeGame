#include "Game.h"


SnakeGame::Game::Game()
{
}

void SnakeGame::Game::pushScene(std::unique_ptr<Interface::Scene> scene)
{
	this->scenes.push_back(std::move(scene));
}

void SnakeGame::Game::popScene()
{
}
