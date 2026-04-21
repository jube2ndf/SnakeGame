#include "SceneSetting.h"
#include "SceneCommand.h"
#include "Settings.h"
#include <iostream>
#include "CheckBox.h"
#include "GameSettings.h"

using namespace SnakeGame;

SnakeGame::Scene::SceneSetting::SceneSetting()
{
    if (!this->_font.loadFromFile(SnakeGame::FONTS_PATH + "Roboto-Black.ttf")) {
        std::cout << "Cannot find arial.ttf! Place font file in project folder." << std::endl;
    }

    const float x_middle = (static_cast<float>(SnakeGame::SCREEN_WIDTH) / 2);
    const float y_start_text = (static_cast<float>(SnakeGame::SCREEN_HEGHT) / 5);

    this->_sceneName.setFillColor(sf::Color::White);
    this->_sceneName.setString("Settings");
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
    this->_Voilume = { this->_font, 
        x_middle + this->_menuOptions[0].getGlobalBounds().width,
        y_start_text + y_step_text, 
        GameSettings::getGameVolume() };
    this->_Music = { this->_font , 
        x_middle + this->_menuOptions[0].getGlobalBounds().width, 
        y_start_text + y_step_text * 2,
        GameSettings::getGameMusic() };

    this->_menuOptions[0].setFillColor(sf::Color::Green);
    this->_inputMenu = {};
}

SceneCommand Scene::SceneSetting::handleInput(sf::Event& event, float dt)
{
    SettingStateType cmd = this->_inputMenu.Update(event);
    switch (cmd)
    {
    case SnakeGame::SettingStateType::None:
        break;
    case SnakeGame::SettingStateType::Voilume:
        GameSettings::setGameVolume(!GameSettings::getGameVolume());
        this->_Voilume.set(GameSettings::getGameVolume());
        break;
    case SnakeGame::SettingStateType::Music:
        GameSettings::setGameMusic(!GameSettings::getGameMusic());
        this->_Music.set(GameSettings::getGameMusic());
        break;
    case SnakeGame::SettingStateType::Back:
        return SceneCommand(GameSceneRequest::Pop);
        break;
    case SnakeGame::SettingStateType::Count:
        break;
    default:
        break;
    }
    this->update(dt);
    return SceneCommand(GameSceneRequest::None);
}

SceneCommand Scene::SceneSetting::update(float dt)
{
    for (auto& text : this->_menuOptions)
        text.setFillColor(sf::Color::White);
    int index = this->_inputMenu.GetSelectOptions() - 1;
    if (index >= 0 && index < this->_menuOptions.size())
        this->_menuOptions[index].setFillColor(sf::Color::Green);
    return SceneCommand(GameSceneRequest::None);
}

void SnakeGame::Scene::SceneSetting::draw(sf::RenderWindow& window)
{
    window.draw(this->_sceneName);
    for (auto& text : this->_menuOptions)
        window.draw(text);
    this->_Music.draw(window);
    this->_Voilume.draw(window);
}
