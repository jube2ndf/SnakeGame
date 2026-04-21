#include "SceneRecordTable.h"
#include "Record.h"
#include "RecordTable.h"
#include <iostream>
#include "Settings.h"

using namespace SnakeGame;

SnakeGame::Scene::SceneRecordTable::SceneRecordTable()
{
    
    std::vector<Models::Record> topValue = Models::RecordTable::GetTop();
    if (!this->_font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Black.ttf")) {
        std::cout << "Cannot find arial.ttf! Place font file in project folder." << std::endl;
    }

    const float x_middle = (static_cast<float>(SnakeGame::SCREEN_WIDTH) / 2);
    const float y_start_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 5);

    this->_sceneName.setFillColor(sf::Color::White);
    this->_sceneName.setString("Top");
    this->_sceneName.setCharacterSize(30);
    this->_sceneName.setFont(this->_font);
    sf::FloatRect bounds = this->_sceneName.getLocalBounds();
    this->_sceneName.setOrigin(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);
    this->_sceneName.setPosition(x_middle, y_start_text);

    const float y_step_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 20);
    if (topValue.empty()) {
        sf::Text text;
        text.setFillColor(sf::Color::White);
        text.setString("Empty");
        text.setCharacterSize(20);
        text.setFont(this->_font);
        text.setPosition(x_middle, y_start_text + y_step_text);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width / 2.0f,
            bounds.top + bounds.height / 2.0f);
        this->_top.push_back(text);
    }
    else {
        int index = 1;
        for (Models::Record iter : topValue) {
            sf::Text text;
            text.setFillColor(sf::Color::White);
            text.setString(std::to_string(index) + ") " + iter.Name + ": " + std::to_string(iter.score));
            text.setCharacterSize(20);
            text.setFont(this->_font);
            text.setPosition(x_middle, y_start_text + y_step_text * index);

            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.left + bounds.width / 2.0f,
                bounds.top + bounds.height / 2.0f);
            this->_top.push_back(text);
            ++index;
        }
    }

}

SceneCommand SnakeGame::Scene::SceneRecordTable::handleInput(sf::Event& event, float dt)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::B:
            return SceneCommand(GameSceneRequest::Pop);
            break;
        default:
            break;
        }
    }
    return SceneCommand(GameSceneRequest::None);
}

SceneCommand SnakeGame::Scene::SceneRecordTable::update(float dt)
{
    return SceneCommand(GameSceneRequest::None);
}

void SnakeGame::Scene::SceneRecordTable::draw(sf::RenderWindow& window)
{
    window.draw(this->_sceneName);
    for (auto& iter : this->_top) {
        window.draw(iter);
    }
}
