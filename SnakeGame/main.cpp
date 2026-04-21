#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "SceneManager.h"
#include "GameStateType.h"
#include "MainMenu.h"
#include "MenuLVLSelect.h"
#include "SceneRecordTable.h"
#include "SceneSetting.h"
#include "ScenePlay.h"
#include "SceneGameOver.h"
#include "GameState.h"
#include "Exit.h"
#include "SceneEnterName.h"
#include "QuestionEnterName.h"
#include "RecordTable.h"



using namespace sf;

int main()
{
    unsigned int seed = (unsigned int)time(nullptr);
    srand(seed);
    RenderWindow window(VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEGHT), 
                        L"Новый проект", 
                        Style::Default);
    window.setVerticalSyncEnabled(true);
    sf::Clock game_clock;
    sf::Time lastTime = game_clock.getElapsedTime();
    SnakeGame::Models::RecordTable::Load();
    SnakeGame::Factory::SceneFactory factory = {};
    SnakeGame::Game::GameState::Name = "XYZ";
    factory.registrateScane<SnakeGame::Menu::MainMenu>(SnakeGame::GameSceneType::MainMenu);
    factory.registrateScane<SnakeGame::Menu::MenuLVLSelect>(SnakeGame::GameSceneType::Complexity);
    factory.registrateScane<SnakeGame::Scene::SceneRecordTable>(SnakeGame::GameSceneType::Records);
    factory.registrateScane<SnakeGame::Scene::SceneSetting>(SnakeGame::GameSceneType::Settings);
    factory.registrateScane<SnakeGame::Scene::ScenePlay>(SnakeGame::GameSceneType::Playing);
    factory.registrateScane<SnakeGame::Scene::SceneGameOver>(SnakeGame::GameSceneType::GameOver);
    factory.registrateScane<SnakeGame::Scene::Exit>(SnakeGame::GameSceneType::ExitDialog);
    factory.registrateScane<SnakeGame::Scene::SceneEnterName>(SnakeGame::GameSceneType::EnterName);
    factory.registrateScane<SnakeGame::Scene::QuestionEnterName>(SnakeGame::GameSceneType::QuestionEnterName);
    

    SnakeGame::Scene::SceneManager sceneManager(factory);

    while (window.isOpen())
    {
        float dt = game_clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            sceneManager.handleInput(event, dt);
        }
        sceneManager.update(dt);
        window.clear();
        sceneManager.draw(window);
        window.display();
    }
    return 0;
}

