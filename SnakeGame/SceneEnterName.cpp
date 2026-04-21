#include "SceneEnterName.h"
#include "Settings.h"
#include <cassert>
#include "GameState.h"

SnakeGame::Scene::SceneEnterName::SceneEnterName()
{
	assert(this->_font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Black.ttf"));
	float middleX = static_cast<float>(SnakeGame::SCREEN_WIDTH) / 2;
	float y_start_text = static_cast<float>(SnakeGame::SCREEN_WIDTH) * 1 / 4;
	float y_step_text = static_cast<float>(SnakeGame::SCREEN_WIDTH) / 5;

	this->_enterName.setFillColor(sf::Color::White);
	this->_enterName.setString("Enter name");
	this->_enterName.setCharacterSize(30);
	this->_enterName.setFont(this->_font);
	sf::FloatRect bounds = this->_enterName.getLocalBounds();
	this->_enterName.setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	this->_enterName.setPosition(middleX, y_start_text);

	this->_text.setFillColor(sf::Color::White);
	this->_text.setString("Enter name");
	this->_text.setCharacterSize(30);
	this->_text.setFont(this->_font);
	bounds = this->_text.getLocalBounds();
	this->_text.setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	this->_text.setPosition(middleX, y_start_text + y_step_text);
}

SnakeGame::SceneCommand SnakeGame::Scene::SceneEnterName::handleInput(sf::Event& event, float dt)
{
	if (event.type == sf::Event::TextEntered) // Если вводится текст
	{
		if (event.text.unicode < 128)  // отсекаем не ASCII символы
		{
			this->_drawingString += static_cast<char>(event.text.unicode); // добавляем в строку вводимый символ
			this->_text.setString(this->_drawingString); // обновляем выводимый текст
		}
	}
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code)
		{
		case sf::Keyboard::Enter:
			Game::GameState::Name = this->_drawingString;
			return SceneCommand(GameSceneRequest::Push, GameSceneType::Playing);
		case sf::Keyboard::BackSpace:
			this->_drawingString.erase(this->_drawingString.getSize() - 1);
			break;
		}
	}
	this->update(dt);
	return SceneCommand(GameSceneRequest::None);
}

SnakeGame::SceneCommand SnakeGame::Scene::SceneEnterName::update(float dt)
{
	return SceneCommand(GameSceneRequest::None);
}

void SnakeGame::Scene::SceneEnterName::draw(sf::RenderWindow& window)
{
    window.draw(this->_text);
    window.draw(this->_enterName);
}
