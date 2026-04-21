#include "MenuLVLSelect.h"
#include "SceneCommand.h"
#include <iostream>
#include "Settings.h"
#include "GameSettings.h"

using namespace SnakeGame;

SnakeGame::Menu::MenuLVLSelect::MenuLVLSelect()
{
	if (!this->_font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Black.ttf")) {
		std::cout << "Cannot find arial.ttf! Place font file in project folder." << std::endl;
	}

	const float x_middle = (static_cast<float>(SnakeGame::SCREEN_WIDTH) / 2);
	const float y_start_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 5);

	this->_sceneName.setFillColor(sf::Color::White);
	this->_sceneName.setString("Difficulty level");
	this->_sceneName.setCharacterSize(30);
	this->_sceneName.setFont(this->_font);
	sf::FloatRect bounds = this->_sceneName.getLocalBounds();
	this->_sceneName.setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	this->_sceneName.setPosition(x_middle, y_start_text);

	const float y_step_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 10);

	for (int i = 0; i < this->_textMenuOptions.size(); i++) {
		sf::Text text;
		text.setFillColor(sf::Color::White);
		text.setString(this->_textMenuOptions[i]);
		text.setCharacterSize(30);
		text.setFont(this->_font);
		text.setPosition(x_middle, y_start_text + y_step_text * (i + 1));

		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.0f,
						bounds.top + bounds.height / 2.0f);

		this->_menuOptions.push_back(std::move(text));
	}
	this->_menuOptions[GameSettings::getLVL()].setFillColor(sf::Color::Green);
	this->_inputMenu = { GameSettings::getLVL() };
}

SceneCommand Menu::MenuLVLSelect::handleInput(sf::Event& event, float dt)
{
	SceneLVLComplecityOptions cmd = this->_inputMenu.Update(event);
	switch (cmd)
	{
	case SnakeGame::SceneLVLComplecityOptions::None:
		break;
	case SnakeGame::SceneLVLComplecityOptions::Easy:
		GameSettings::setLVL(1);
		return SceneCommand(GameSceneRequest::Pop);
		break;
	case SnakeGame::SceneLVLComplecityOptions::MoreDifficultThanEasy:
		GameSettings::setLVL(2);
		return SceneCommand(GameSceneRequest::Pop);
		break;
	case SnakeGame::SceneLVLComplecityOptions::Medium:
		GameSettings::setLVL(3);
		return SceneCommand(GameSceneRequest::Pop);
		break;
	case SnakeGame::SceneLVLComplecityOptions::EasierThanDifficult:
		GameSettings::setLVL(4);
		return SceneCommand(GameSceneRequest::Pop);
		break;
	case SnakeGame::SceneLVLComplecityOptions::Difficult:
		GameSettings::setLVL(5);
		return SceneCommand(GameSceneRequest::Pop);
		break;
	case SnakeGame::SceneLVLComplecityOptions::Back:
		return SceneCommand(GameSceneRequest::Pop);
		break;
	case SnakeGame::SceneLVLComplecityOptions::Count:
		break;
	default:
		break;
	}
	this->update(dt);
    return SceneCommand(GameSceneRequest::None);
}

SceneCommand Menu::MenuLVLSelect::update(float dt)
{
	for (auto& text : this->_menuOptions)
		text.setFillColor(sf::Color::White);
	int index = this->_inputMenu.GetSelectOptions() - 1;
	if (index >= 0 && index < this->_menuOptions.size())
		this->_menuOptions[index].setFillColor(sf::Color::Green);
	return SceneCommand(GameSceneRequest::None);
}

void Menu::MenuLVLSelect::draw(sf::RenderWindow& window)
{
	window.draw(this->_sceneName);
	for (auto& text : this->_menuOptions)
		window.draw(text);
}
