#include "GameSprite.h"

SnakeGame::Game::GameObject::GameSprite::GameSprite()
{
}

SnakeGame::Game::GameObject::GameSprite::GameSprite(float desiredWidth, float desiredHeight, const sf::Texture& texture)
{
	this->sprite = sf::Sprite(texture);
	this->SetOrigin(0.5f, 0.5f);
	this->SetSize(desiredWidth, desiredHeight);
}

void SnakeGame::Game::GameObject::GameSprite::Draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void SnakeGame::Game::GameObject::GameSprite::SetOrigin(float originX, float originY)
{
	sf::FloatRect bouns = sprite.getLocalBounds();
	sprite.setOrigin(originX * bouns.width, originY * bouns.height);
}

void SnakeGame::Game::GameObject::GameSprite::SetSize(float newWidth, float newHeight)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	this->sprite.scale(newWidth / bounds.width, newHeight / bounds.height);
}

void SnakeGame::Game::GameObject::GameSprite::SetRandomPosition(const sf::FloatRect& rect, const std::list<GameObject::GameSprite>& collection)
{
	do {
		this->SetRandomSpritePositionInRectangle(rect);
	} while (this->FullCheckCollisions(collection.begin(), collection.end()));
}

bool SnakeGame::Game::GameObject::GameSprite::CheckSpriteIntersection(const GameSprite& sprite2)
{
	sf::FloatRect bounds1 = this->sprite.getGlobalBounds();
	sf::FloatRect bounds2 = sprite2.sprite.getGlobalBounds();

	if (!bounds1.intersects(bounds2)) {
		return false;
	}

	return true;
}

void SnakeGame::Game::GameObject::GameSprite::SetRandomSpritePositionInRectangle(const sf::FloatRect& rect)
{
	const float Width = this->sprite.getGlobalBounds().width;
	const float Height = this->sprite.getGlobalBounds().height;
	this->sprite.setPosition(
		rand() / (float)RAND_MAX * (rect.width - 2 * Width) + rect.left + Width,
		rand() / (float)RAND_MAX * (rect.height - 2 * Height) + rect.top + Height
	);
}

void SnakeGame::Game::GameObject::GameSprite::SetPosition(sf::Vector2f v)
{
	this->sprite.setPosition(v);
}

sf::Vector2f SnakeGame::Game::GameObject::GameSprite::getPosition()
{
	return this->sprite.getPosition();
}

void SnakeGame::Game::GameObject::GameSprite::setTexture(const sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void SnakeGame::Game::GameObject::GameSprite::setRotation(float rotation)
{
	this->sprite.setRotation(rotation);
}

const sf::Sprite& SnakeGame::Game::GameObject::GameSprite::GetSprite()
{
	return this->sprite;
}

