#include "SceneQuestionYesNo.h"
#include "Settings.h"
#include <cassert>

SnakeGame::Scene::SceneQuestionYesNo::SceneQuestionYesNo(std::string question)
{
	assert(this->_font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Black.ttf"));

    float middleX = static_cast<float>(SnakeGame::SCREEN_WIDTH) / 2;
	float y_start_text = static_cast<float>(SnakeGame::SCREEN_WIDTH) * 1 / 5;
	float y_step_text = static_cast<float>(SnakeGame::SCREEN_WIDTH) / 5;

	this->_question.setFillColor(sf::Color::White);
	this->_question.setString(question);
	this->_question.setCharacterSize(30);
	this->_question.setFont(this->_font);
	sf::FloatRect bounds = this->_question.getLocalBounds();
	this->_question.setOrigin(bounds.left + bounds.width / 2.0f,
		bounds.top + bounds.height / 2.0f);
	this->_question.setPosition(middleX, y_start_text);

	for (int i = 0; i < this->_textMenuOptions.size(); i++) {
		sf::Text text;
		text.setFillColor(sf::Color::White);
		text.setString(this->_textMenuOptions[i]);
		text.setCharacterSize(30);
		text.setFont(this->_font);
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.0f,
			bounds.top + bounds.height / 2.0f);
		text.setPosition(middleX, y_start_text + y_step_text * (i + 1));
		this->_menuOptions.push_back(std::move(text));
	}
	this->_menuOptions[0].setFillColor(sf::Color::Green);
}

SnakeGame::SceneCommand SnakeGame::Scene::SceneQuestionYesNo::handleInput(sf::Event& event, float dt)
{
    QuestionYesNo cmd = this->_inputMenu.Update(event);
	this->update(dt);
    return this->handlersQuestionYesNo(cmd);
}

SnakeGame::SceneCommand SnakeGame::Scene::SceneQuestionYesNo::update(float dt)
{
	for (auto& text : this->_menuOptions)
		text.setFillColor(sf::Color::White);
	int index = this->_inputMenu.GetSelectOptions() - 1;
	if (index >= 0 && index < this->_menuOptions.size())
		this->_menuOptions[index].setFillColor(sf::Color::Green);
	return SceneCommand(GameSceneRequest::None);
}

void SnakeGame::Scene::SceneQuestionYesNo::draw(sf::RenderWindow& window)
{
	window.draw(this->_question);
	for (auto& text : this->_menuOptions)
		window.draw(text);
}
