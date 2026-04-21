#pragma once
#include "GameStateType.h"
#include "GameSceneRequest.h"
#include <vector>
#include <memory>
#include "Scene.h"
#include "SceneFactory.h"
#include "SceneCommand.h"

namespace SnakeGame {
    namespace Scene {
        class SceneManager
        {
        protected:
            std::vector<std::unique_ptr<Interface::Scene>> _scenes;
            std::vector<SceneCommand> _commands;
            Factory::SceneFactory& _factory;

            void requestPush(GameSceneType id);
            void requesrPop();
            void requesrReplace(GameSceneType id);
            
            void requestClear();
            void processCommands();

        public:
            SceneManager(const SceneManager&) = delete;
            SceneManager& operator=(const SceneManager&) = delete;

            SceneManager(Factory::SceneFactory& factory) :
                _factory(factory)
            {
                this->requesrReplace(GameSceneType::MainMenu);
                processCommands();
            }

            void handleInput(sf::Event& event, float dt);
            void update(float dt);
            void draw(sf::RenderWindow& window);
        };
    }
}

