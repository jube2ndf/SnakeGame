#include "Snake.h"
#include "Settings.h"
#include <cassert>
#include "GameSprite.h"
#include <iostream>

using namespace SnakeGame;

const std::string HEAD_TEXTURE_ID = "Head.png";
const std::string BODY_TEXTURE_ID = "Body.png";
const std::string BODY_BEND_TEXTURE_ID = "BodyBend.png";
const std::string TAIL_TEXTURE_ID = "Tail.png";

sf::Vector2f SnakeGame::Game::GameObject::Snake::getVectorDirection()
{
	sf::Vector2f result;

	switch (direction)
	{
		case SnakeDirection::Up:
		{
			result = { 0.f, -SNAKE_SIZE };
			break;
		}
		case SnakeDirection::Right:
		{
			result = { SNAKE_SIZE, 0.f };
			break;
		}
		case SnakeDirection::Down:
		{
			result = { 0.f, SNAKE_SIZE };
			break;
		}
		case SnakeDirection::Left:
		{
			result = { -SNAKE_SIZE, 0.f };
			break;
		}
	}
	return result;
}

void SnakeGame::Game::GameObject::Snake::SetHead(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator it)
{
	float angle = -90.f;
	switch (this->direction)
	{
	case GameObject::SnakeDirection::Down:
		angle = 180.f;
		break;
	case GameObject::SnakeDirection::Left:
		angle = -90.f;
		break;
	case GameObject::SnakeDirection::Right:
		angle = 90.f;
		break;
	case GameObject::SnakeDirection::Up:
		angle = 0.f;
		break;
	}


	it->setTexture(this->textures[(size_t)Game::GameObject::SnakePart::Head]);
	it->setRotation(angle);
}

void SnakeGame::Game::GameObject::Snake::GetRotationSprite(std::list<GameObject::GameSprite>::iterator it)
{
	float angle = 0.f;
	if (this->prevDirection == GameObject::SnakeDirection::Right && this->direction == GameObject::SnakeDirection::Up ||
		this->prevDirection == GameObject::SnakeDirection::Down && this->direction == GameObject::SnakeDirection::Left) {
		angle = 0.f;
	}
	else if (this->prevDirection == GameObject::SnakeDirection::Down && this->direction == GameObject::SnakeDirection::Right ||
		this->prevDirection == GameObject::SnakeDirection::Left && this->direction == GameObject::SnakeDirection::Up) {
		angle = 90.f;
	}
	else if (this->prevDirection == GameObject::SnakeDirection::Left && this->direction == GameObject::SnakeDirection::Down ||
		this->prevDirection == GameObject::SnakeDirection::Up && this->direction == GameObject::SnakeDirection::Right) {
		angle = 180;
	}
	else if (this->prevDirection == GameObject::SnakeDirection::Up && this->direction == GameObject::SnakeDirection::Left ||
		this->prevDirection == GameObject::SnakeDirection::Right && this->direction == GameObject::SnakeDirection::Down) {
		angle = -90.f;
	}
	it->setTexture(this->textures[(size_t)GameObject::SnakePart::BodyBend]);
	it->setRotation(angle);
}

void SnakeGame::Game::GameObject::Snake::SetTailSprite(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator it)
{
	

	auto nextIt = std::next(it);
	if (nextIt == this->body.end()) {
		return;
	}

	float angle = 180.f; // Up
	if (nextIt->getPosition().x < it->getPosition().x) { // Left
		angle = 90.f;
	}
	else if (nextIt->getPosition().x > it->getPosition().x) { // Right
		angle = -90.f;
	}
	else if (nextIt->getPosition().y > it->getPosition().y) { // Down
		angle = 0.f;
	}
	it->setTexture(this->textures[(size_t)Game::GameObject::SnakePart::Tail]);
	it->setRotation(angle);
}

Game::GameObject::Snake::Snake(float startSpeed)
{
	assert(this->textures[(size_t)SnakePart::Head].loadFromFile(SnakeGame::TEXTURE_PATH + HEAD_TEXTURE_ID));
	assert(this->textures[(size_t)SnakePart::Body].loadFromFile(SnakeGame::TEXTURE_PATH + BODY_TEXTURE_ID));
	assert(this->textures[(size_t)SnakePart::BodyBend].loadFromFile(SnakeGame::TEXTURE_PATH + BODY_BEND_TEXTURE_ID));
	assert(this->textures[(size_t)SnakePart::Tail].loadFromFile(SnakeGame::TEXTURE_PATH + TAIL_TEXTURE_ID));

	// Init snake state
	for (int i = 0; i < INITIAL_SNAKE_SIZE; ++i) {
		switch (i)
		{
		case 0:
			this->body.push_front(
				GameObject::GameSprite(
					SNAKE_SIZE, 
					SNAKE_SIZE, 
					this->textures[(size_t)SnakePart::Head]
				)
			);
			break;
		case INITIAL_SNAKE_SIZE-1:
			this->body.push_front(
				GameObject::GameSprite(
					SNAKE_SIZE, 
					SNAKE_SIZE, 
					this->textures[(size_t)SnakePart::Tail]
				)
			);
			break;
		default:
			this->body.push_front(
				GameObject::GameSprite(
					SNAKE_SIZE, 
					SNAKE_SIZE, 
					this->textures[(size_t)SnakePart::Body]
				)
			);
			break;
		}
		(*this->body.begin()).SetPosition({(float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f + SNAKE_SIZE * i});
	}
	this->head = --this->body.end();
	this->tail = this->body.begin();

	this->speed = startSpeed;
	this->direction = SnakeDirection::Up;
}

SnakeGame::Game::GameObject::Snake::Snake():
	Snake(INITIAL_SPEED)
{
}

void SnakeGame::Game::GameObject::Snake::GrowSnake()
{
	this->head->SetPosition(this->head->getPosition() + this->getVectorDirection());
}

std::list<Game::GameObject::GameSprite>::iterator SnakeGame::Game::GameObject::Snake::GetNextIterator(std::list<Game::GameObject::GameSprite>::iterator it)
{
	std::list<Game::GameObject::GameSprite>::iterator nextIt = std::next(it);
	if (nextIt == this->body.end()) {
		nextIt = this->body.begin();
	}
	return nextIt;
}

std::list<Game::GameObject::GameSprite>::iterator SnakeGame::Game::GameObject::Snake::GetPrevIterator(std::list<Game::GameObject::GameSprite>::iterator it)
{
	std::list<Game::GameObject::GameSprite>::iterator prevIt = it == this->body.begin()
		? std::prev(this->body.end())
		: std::prev(it);
	return prevIt;
}

bool SnakeGame::Game::GameObject::Snake::CheckHeadIntersection(const SnakeGame::Game::GameObject::GameSprite& sprite)
{
	return this->head->CheckSpriteIntersection(sprite);
}

bool SnakeGame::Game::GameObject::Snake::FullCheckCollisions(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator first, std::list<SnakeGame::Game::GameObject::GameSprite>::iterator last)
{
	return this->head->FullCheckCollisions(first, last);
}

void SnakeGame::Game::GameObject::Snake::SetDirection(SnakeDirection newSnakeDirection)
{
	this->nextDirection = newSnakeDirection;
}

const std::list<SnakeGame::Game::GameObject::GameSprite> SnakeGame::Game::GameObject::Snake::getBody()
{
	return this->body;
}

void SnakeGame::Game::GameObject::Snake::Move(float df, const sf::FloatRect& bounds)
{
	float shift = this->speed * df;
	if (IsHeadInCellCenter(bounds))
	{
		// запрет разворота назад
		if (!(
			(direction == SnakeDirection::Up && nextDirection == SnakeDirection::Down) ||
			(direction == SnakeDirection::Down && nextDirection == SnakeDirection::Up) ||
			(direction == SnakeDirection::Left && nextDirection == SnakeDirection::Right) ||
			(direction == SnakeDirection::Right && nextDirection == SnakeDirection::Left)
			))
		{
			this->direction = nextDirection;
		}
	}
	const sf::Vector2f direction = this->getVectorDirection() * shift / SNAKE_SIZE;
	auto prevHead = this->head;

	// new rotation
	if (this->prevDirection != this->direction) {
		this->head = this->body.insert(++this->head, *prevHead);
		this->SetHead(this->head);

		this->GetRotationSprite(prevHead);
		prevHead->SetPosition(this->head->getPosition());
	}
	this->head->SetPosition(this->head->getPosition() + direction);
	if (IsHeadInCellCenter(bounds))
	{
		SnapToGrid(bounds);
	}

	auto nextTail = std::next(this->tail);
	auto tailDirection = this->tail->GetVectorBetweenSprites(*nextTail);
	auto dist = this->tail->GetManhattanDistanceBetweenSprites(*nextTail);

	if (shift > dist) {
		shift -= dist;
		this->tail = this->body.erase(this->tail);
		this->SetTailSprite(this->tail);
	}
	else {
		this->tail->SetPosition(this->tail->getPosition() + tailDirection * shift / dist);
	}

	this->prevDirection = this->direction;
}

bool SnakeGame::Game::GameObject::Snake::IsHeadInCellCenter(const sf::FloatRect& bounds)
{
	sf::Vector2f pos = this->head->getPosition();

	float localX = pos.x - bounds.left;
	float localY = pos.y - bounds.top;

	float modX = fmod(localX, SNAKE_SIZE);
	float modY = fmod(localY, SNAKE_SIZE);

	const float epsilon = 1.0f; // допуск

	return (std::abs(modX) < epsilon || std::abs(modX - SNAKE_SIZE) < epsilon) &&
		(std::abs(modY) < epsilon || std::abs(modY - SNAKE_SIZE) < epsilon);
}

void SnakeGame::Game::GameObject::Snake::SnapToGrid(const sf::FloatRect& bounds)
{
	sf::Vector2f pos = this->head->getPosition();

	float x = std::round((pos.x - bounds.left) / SNAKE_SIZE) * SNAKE_SIZE + bounds.left;
	float y = std::round((pos.y - bounds.top) / SNAKE_SIZE) * SNAKE_SIZE + bounds.top;

	this->head->SetPosition({ x, y });
}

bool SnakeGame::Game::GameObject::Snake::HasSnakeCollisionWithRect(const sf::FloatRect& rect)
{
	sf::Vector2f forwardPoint = this->head->getPosition();
	if (this->direction == SnakeDirection::Up) {
		forwardPoint.y -= SNAKE_SIZE / 2.f;
	}
	else if (this->direction == SnakeDirection::Right) {
		forwardPoint.x += SNAKE_SIZE / 2.f;
	}
	else if (this->direction == SnakeDirection::Down) {
		forwardPoint.y += SNAKE_SIZE / 2.f;
	}
	else {
		forwardPoint.x -= SNAKE_SIZE / 2.f;
	}
	bool result = rect.contains(forwardPoint);
	return result;
}

bool SnakeGame::Game::GameObject::Snake::CheckSnakeCollisionWithHimself()
{
	auto curIt = this->tail;
	auto nextIt = std::next(this->tail);
	while (nextIt != this->head) {
		auto curRect = curIt->GetSprite().getGlobalBounds();
		auto nextRect = nextIt->GetSprite().getGlobalBounds();

		sf::FloatRect unionRect;
		unionRect.top = std::min(curRect.top, nextRect.top);
		unionRect.left = std::min(curRect.left, nextRect.left);
		unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
		unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

		if (HasSnakeCollisionWithRect(unionRect)) {
			return true;
		}
		curIt = nextIt;
		nextIt = std::next(nextIt);
	}
	return false;
}

void SnakeGame::Game::GameObject::Snake::AddSpead(float value)
{
	this->speed += value;
}

void SnakeGame::Game::GameObject::Snake::Draw(sf::RenderWindow& window) {
	for (auto it = this->body.begin(); it != this->head; ++it) {
		auto nextIt = std::next(it);
		float width = SNAKE_SIZE, height = it->GetManhattanDistanceBetweenSprites(*nextIt) - SNAKE_SIZE;
		float angle = it->getPosition().x != nextIt->getPosition().x ? 90.f : 0.f;

		if (width > 0.f && height > 0.f) {
			GameSprite sprite = GameSprite(
				width, 
				height, 
				this->textures[(size_t)GameObject::SnakePart::Body]
			);
			auto position = (it->getPosition() + nextIt->getPosition()) / 2.f;
			sprite.SetPosition(position);
			sprite.setRotation(angle);
			sprite.Draw(window);
		}
	}
	for (auto first = this->body.begin(); first != this->body.end(); ++first) {
		first->Draw(window);
	}
}


