#pragma once
#include "Scene.h"
#include "MenuFunctionality.h"
#include "SceneSettingStateType.h"
#include "CheckBox.h"


namespace SnakeGame {
    namespace Scene {
        class SceneSetting :
            public Interface::Scene
        {
        private:
            sf::Font _font;
            sf::Text _sceneName;

            const std::vector<std::string> _textMenuOptions = {
                "Voilume",
                "Music"
            };

            UI::CheckBox _Voilume, _Music;


            std::vector<sf::Text> _menuOptions;

            MenuFunctionality<SettingStateType> _inputMenu;
        public:
            SceneSetting();
            // Унаследовано через Scene
            SceneCommand handleInput(sf::Event& event, float dt) override;
            SceneCommand update(float dt) override;
            void draw(sf::RenderWindow& window) override;
        };
    }
}

