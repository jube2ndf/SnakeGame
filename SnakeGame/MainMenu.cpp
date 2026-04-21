#include "MainMenu.h"
#include "SceneCommand.h"
#include "MainMenuOptions.h"
#include <cassert>

SnakeGame::Menu::MainMenu::MainMenu()
{
	if (!this->_font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Black.ttf")) {
		std::cout << "Cannot find arial.ttf! Place font file in project folder." << std::endl;
	}

	const float x_middle = (static_cast<float>(SnakeGame::SCREEN_WIDTH) / 3);
	const float y_start_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 5);

	this->_gameName.setFillColor(sf::Color::White);
	this->_gameName.setString("SnakeGame");
	this->_gameName.setCharacterSize(30);
	this->_gameName.setFont(this->_font);
	this->_gameName.setPosition(x_middle, y_start_text);

	const float y_step_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 10);

	for (int i = 0; i < this->_textMenuOptions.size(); i++) {
		sf::Text text;
		text.setFillColor(sf::Color::White);
		text.setString(this->_textMenuOptions[i]);
		text.setCharacterSize(30);
		text.setFont(this->_font);
		text.setPosition(x_middle, y_start_text + y_step_text * (i+1));
		this->_menuOptions.push_back(std::move(text));
	}
	this->_menuOptions[0].setFillColor(sf::Color::Green);
}

SnakeGame::SceneCommand SnakeGame::Menu::MainMenu::handleInput(sf::Event& event, float dt)
{
	SnakeGame::MainMenuOptions cmd = this->_inputMenu.Update(event);
	switch (cmd)
	{
	case SnakeGame::MainMenuOptions::None:
		break;
	case SnakeGame::MainMenuOptions::StartGame:
		return SceneCommand(GameSceneRequest::Push, GameSceneType::QuestionEnterName);
		break;
	case SnakeGame::MainMenuOptions::Complexity:
		return SceneCommand(GameSceneRequest::Push, GameSceneType::Complexity);
		break;
	case SnakeGame::MainMenuOptions::Settings:
		return SceneCommand(GameSceneRequest::Push, GameSceneType::Settings);
		break;
	case SnakeGame::MainMenuOptions::Records:
		return SceneCommand(GameSceneRequest::Push, GameSceneType::Records);
		break;
	case SnakeGame::MainMenuOptions::Exit:
		return SceneCommand(GameSceneRequest::Clear);
		break;
	case SnakeGame::MainMenuOptions::Back:
		return SceneCommand(GameSceneRequest::Pop);
		break;
	default:
		break;
	}
	this->update(dt);
	return SnakeGame::SceneCommand{ GameSceneRequest::None };
}

SnakeGame::SceneCommand SnakeGame::Menu::MainMenu::update(float dt)
{
	for (auto& text : this->_menuOptions)
		text.setFillColor(sf::Color::White);
	int index = this->_inputMenu.GetSelectOptions()-1;
	if(index>=0 && index < this->_menuOptions.size())
		this->_menuOptions[index].setFillColor(sf::Color::Green);
	return SnakeGame::SceneCommand{ GameSceneRequest::None };
}

void SnakeGame::Menu::MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(this->_gameName);
	for (auto& text: this->_menuOptions)
		window.draw(text);
}
