#include "SceneManager.h"
#include "Scene.h"

void SnakeGame::Scene::SceneManager::requestPush(GameSceneType id)
{
	this->_commands.emplace_back(GameSceneRequest::Push, id);
}

void SnakeGame::Scene::SceneManager::requesrPop()
{
	this->_commands.emplace_back(GameSceneRequest::Pop);
}

void SnakeGame::Scene::SceneManager::requesrReplace(GameSceneType id)
{
	this->_commands.emplace_back(GameSceneRequest::Switch, id);
}

void SnakeGame::Scene::SceneManager::update(float dt) {
	if (_scenes.empty())
		return;

    SceneCommand cmd = _scenes.back()->update(dt);
    if (cmd.action != GameSceneRequest::None)
        _commands.push_back(std::move(cmd));
    processCommands();
}

void SnakeGame::Scene::SceneManager::handleInput(sf::Event& event, float dt) {
	if (_scenes.empty())
		return;

	SceneCommand cmd = _scenes.back()->handleInput(event, dt);
	if (cmd.action != GameSceneRequest::None)
		_commands.push_back(std::move(cmd));
}

void SnakeGame::Scene::SceneManager::draw(sf::RenderWindow& window)
{
    if (!this->_scenes.empty())
        this->_scenes.back()->draw(window);
    else
        window.close();
}

void SnakeGame::Scene::SceneManager::requestClear()
{
	this->_commands.emplace_back(GameSceneRequest::Clear, GameSceneType::None);
}

void SnakeGame::Scene::SceneManager::processCommands()
{
    for (auto& cmd : this->_commands)
    {
        switch (cmd.action)
        {
        case GameSceneRequest::Push:
            _scenes.push_back(_factory.create(cmd.id));
            break;

        case GameSceneRequest::Pop:
            if(_scenes.size() != 0)
                _scenes.pop_back();
            break;

        case GameSceneRequest::Switch:
            if (!_scenes.empty())
                _scenes.pop_back();
            _scenes.push_back(_factory.create(cmd.id));
            break;

        case GameSceneRequest::Clear:
            _scenes.clear();
            break;

        default:
            break;
        }
    }
    this->_commands.clear();
}
