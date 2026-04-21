#include "GameObject.h"
#include <cassert>
#include "GameSprite.h"

void SnakeGame::Models::GameObject::LoadTexture(std::string file)
{
	this->_objectTexture = std::make_unique<sf::Texture>();
	assert(this->_objectTexture->loadFromFile(file));
}

SnakeGame::Models::GameObject::GameObject(std::string file)
{
	LoadTexture(file);
}

SnakeGame::Models::GameObject::GameObject(std::string file, int spriteSize)
	: GameObject(file)
{
	this->_objectSprite.setTexture(*(this->_objectTexture));
	sf::FloatRect spriteRect = this->_objectSprite.getLocalBounds();
	this->_objectSprite.setScale({ spriteSize / spriteRect.width,
						spriteSize / spriteRect.height });
}

SnakeGame::Models::GameObject::GameObject(std::string file, int spriteSize, Vector2f position) 
	: GameObject(file, spriteSize)
{
	this->_objectSprite.setPosition(position);
}

SnakeGame::Models::GameObject::GameObject(std::string file, int spriteSize, Vector2f position, float rotation)
	: GameObject(file, spriteSize, position)
{
	this->_objectSprite.setRotation(rotation);
}

void SnakeGame::Models::GameObject::setPosition(Vector2f newPosition)
{
	this->_objectSprite.setPosition(newPosition);
}

void SnakeGame::Models::GameObject::setRotation(float rotation)
{
	this->_objectSprite.setRotation(rotation);
}

sf::Vector2f SnakeGame::Game::GameObject::GameSprite::GetVectorBetweenSprites(const GameSprite& spriteTo)
{
	return spriteTo.sprite.getPosition() - this->getPosition();
}

float SnakeGame::Game::GameObject::GameSprite::GetManhattanDistanceBetweenSprites(const GameSprite& spriteTo)
{
	const sf::Vector2f result = spriteTo.sprite.getPosition() - this->getPosition();
	return std::fabs(result.x) + std::fabs(result.y);
}

void SnakeGame::Models::GameObject::DrawObject(RenderWindow& win)
{
	win.draw(this->_objectSprite);
}
