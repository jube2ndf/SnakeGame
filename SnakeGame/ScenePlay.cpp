#include "ScenePlay.h"
#include "GameSceneRequest.h"
#include <cassert>
#include "Settings.h"
#include "GameState.h"
#include "RecordTable.h"
#include "GameSettings.h"


SnakeGame::Scene::ScenePlay::ScenePlay()
{
	this->snake = Game::GameObject::Snake(static_cast<float>(SNAKE_SIZE * INITIAL_SPEED));
	assert(this->appleTexture.loadFromFile(SnakeGame::TEXTURE_PATH + "Apple.png"));
	assert(this->rockTexture.loadFromFile(SnakeGame::TEXTURE_PATH + "Rock.png"));
	assert(this->font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Regular.ttf"));

	// Init background
	this->background.setSize(sf::Vector2f(SCREEN_WIDTH - 20, SCREEN_HEGHT - 60));
	this->background.setPosition(10.f, 50.f);
	this->background.setFillColor(sf::Color(0, 200, 0));
	this->background.setOutlineThickness(10);
	this->background.setOutlineColor(sf::Color::Red);

	this->bounds = this->background.getGlobalBounds();
	this->cols = bounds.width / SnakeGame::SNAKE_SIZE;
	this->rows = bounds.height / SnakeGame::SNAKE_SIZE;

	// Init apple
	this->apple = Game::GameObject::GameSprite(APPLE_SIZE, APPLE_SIZE, this->appleTexture);
	this->apple.SetRandomPosition(this->background.getGlobalBounds(), this->snake.getBody());

	// Init rocks
	this->rocks.resize(ROCKS_COUNT);
	for (SnakeGame::Game::GameObject::GameSprite& rock : this->rocks) {
		rock = SnakeGame::Game::GameObject::GameSprite( ROCK_SIZE, ROCK_SIZE, this->rockTexture);
		rock.SetRandomPosition(this->background.getGlobalBounds(), this->snake.getBody());
	}

	this->numEatenApples = 0;
	this->elapsedTime = 0;

	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(24);
	this->scoreText.setFillColor(sf::Color::Yellow);

	this->inputHintText.setFont(this->font);
	this->inputHintText.setPosition(100.0f, 10.0f);
	this->inputHintText.setCharacterSize(24);
	this->inputHintText.setFillColor(sf::Color::White);
	this->inputHintText.setString("Use WASD keys to move, P to pause");
	this->inputHintText.setOrigin({ 1.f, 0.f });

	// Init sounds
	this->eat = Sound::SoundObject(SnakeGame::SOUNDS_PATH + "AppleEat.wav");
	this->death = Sound::SoundObject(SnakeGame::SOUNDS_PATH + "Death.wav");
}

SnakeGame::SceneCommand SnakeGame::Scene::ScenePlay::handleInput(sf::Event& event, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->snake.SetDirection(Game::GameObject::SnakeDirection::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->snake.SetDirection(Game::GameObject::SnakeDirection::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->snake.SetDirection(Game::GameObject::SnakeDirection::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->snake.SetDirection(Game::GameObject::SnakeDirection::Left);
	}

    return SnakeGame::SceneCommand(GameSceneRequest::None);
}

SnakeGame::SceneCommand SnakeGame::Scene::ScenePlay::update(float dt)
{
	// Update snake
	this->snake.Move(dt);
	if (!this->snake.HasSnakeCollisionWithRect(this->background.getGlobalBounds())
		|| this->snake.CheckSnakeCollisionWithHimself()
		|| this->snake.FullCheckCollisions(this->rocks.begin(), this->rocks.end()))
	{
		if (GameSettings::getGameVolume()) {
			this->death.Play();
		}
		Game::GameState::Score = this->numEatenApples;
		return SnakeGame::SceneCommand(GameSceneRequest::Push, GameSceneType::GameOver);
	}

	if (this->snake.CheckHeadIntersection(this->apple)) {
		if (GameSettings::getGameVolume()) {
			this->eat.Play();
		}
		this->snake.GrowSnake();

		this->snake.AddSpead(SnakeGame::GameSettings::getLVL() * SNAKE_SIZE);

		this->numEatenApples += SnakeGame::GameSettings::getLVL() * 2;

		this->apple.SetRandomPosition(this->background.getGlobalBounds(), this->snake.getBody());
	}

	this->scoreText.setString("Apples eaten: " + std::to_string(this->numEatenApples));
	return SnakeGame::SceneCommand(GameSceneRequest::None);
}

void SnakeGame::Scene::ScenePlay::draw(sf::RenderWindow& window)
{

	window.draw(this->background);

	this->snake.Draw(window);

	this->apple.Draw(window);

	for (SnakeGame::Game::GameObject::GameSprite& rock : this->rocks) {
		rock.Draw(window);
	}
	
	this->scoreText.setOrigin({ 0.f, 0.f });
	this->scoreText.setPosition(10.f, 10.f);
	window.draw(this->scoreText);

	sf::Vector2f viewSize = window.getView().getSize();
	this->inputHintText.setPosition(viewSize.x - 400.f, 10.f);
	window.draw(this->inputHintText);
}
