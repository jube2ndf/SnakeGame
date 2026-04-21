#include "SceneGameOver.h"
#include "Settings.h"
#include <cassert>
#include "RecordTable.h"
#include <sstream>
#include "GameState.h"
#include "Record.h"


enum class Alignment
{
	Min, // Left or Top
	Middle,
	Max // Right or Bottom
};
enum class Orientation
{
	Horizontal,
	Vertical
};
sf::Vector2f static GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
{
	sf::FloatRect textSize = text.getLocalBounds();
	return {
		(textSize.left + textSize.width) * relativePosition.x,
		(textSize.top + textSize.height) * relativePosition.y,
	};
}
void static DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
{
	sf::FloatRect totalRect;
	// Calculate total height/width of all texts
	for (auto it = items.begin(); it != items.end(); ++it)
	{
		sf::FloatRect itemRect = (*it)->getGlobalBounds();

		if (orientation == Orientation::Horizontal)
		{
			totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
			totalRect.height = std::max(totalRect.height, itemRect.height);
		}
		else
		{
			totalRect.width = std::max(totalRect.width, itemRect.width);
			totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
		}
	}

	totalRect.left = position.x - origin.x * totalRect.width;
	totalRect.top = position.y - origin.y * totalRect.height;
	sf::Vector2f currentPos = { totalRect.left, totalRect.top };

	for (auto it = items.begin(); it != items.end(); ++it)
	{
		sf::FloatRect itemRect = (*it)->getGlobalBounds();
		sf::Vector2f itemOrigin;

		if (orientation == Orientation::Horizontal)
		{
			itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
			itemOrigin.x = 0.f;
			currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
		}
		else
		{
			itemOrigin.y = 0.f;
			itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
			currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
		}

		(*it)->setOrigin(GetTextOrigin(**it, itemOrigin));
		(*it)->setPosition(currentPos);
		window.draw(**it);

		if (orientation == Orientation::Horizontal)
		{
			currentPos.x += itemRect.width + spacing;
		}
		else
		{
			currentPos.y += itemRect.height + spacing;
		}
	}
}



SnakeGame::Scene::SceneGameOver::SceneGameOver()
{
	Models::RecordTable::Add(Models::Record(Game::GameState::Name, Game::GameState::Score));
	assert(this->font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
	for (int i = 0; i < this->menu.size(); i++) {
		sf::Text text;
		text.setFillColor(sf::Color::White);
		text.setString(this->menu[i]);
		text.setCharacterSize(30);
		text.setFont(this->font);
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.0f,
			bounds.top + bounds.height / 2.0f);
		text.setPosition(
			static_cast<float>(SnakeGame::SCREEN_WIDTH) / 2, 
			static_cast<float>(SnakeGame::SCREEN_HEGHT)*3/5 + 40 * (i + 1)
		);
		this->_menuOptions.push_back(std::move(text));
	}

	this->timeSinceGameOver = 0.f;

	sf::Color backgroundColor = sf::Color::Black;
	backgroundColor.a = 200; // a means Alfa, opacity
	this->background.setFillColor(backgroundColor);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(48);
	this->gameOverText.setStyle(sf::Text::Bold);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER");

	this->recordsTableTexts.reserve(SnakeGame::MAX_RECORDS_TABLE_SIZE);

	std::multimap<int, std::string> sortedRecordsTable;

	int snakeScores = Models::RecordTable::getScore(Game::GameState::Name);
	for (const auto& item : Models::RecordTable::GetTop())
	{
		sortedRecordsTable.insert(std::make_pair(item.score, item.Name));
	}

	bool isSnakeInTable = false;
	auto it = sortedRecordsTable.rbegin();
	for (int i = 0; i < 3 && it != sortedRecordsTable.rend(); ++i, ++it) 
	{
		this->recordsTableTexts.emplace_back();
		sf::Text& text = this->recordsTableTexts.back();

		std::stringstream sstream;
		sstream << i + 1 << ". " << it->second << ": " << it->first;
		text.setString(sstream.str());
		text.setFont(this->font);
		text.setCharacterSize(24);
		if (it->second == Game::GameState::Name)
		{
			text.setFillColor(sf::Color::Green);
			isSnakeInTable = true;
		}
		else
		{
			text.setFillColor(sf::Color::White);
		}
	}

	this->hintText.setFont(this->font);
	this->hintText.setCharacterSize(24);
	this->hintText.setFillColor(sf::Color::White);
	this->hintText.setString("Press Space to restart\nEsc to exit to main menu");
}

SnakeGame::SceneCommand SnakeGame::Scene::SceneGameOver::handleInput(sf::Event& event, float dt)
{
	GameOverOptions cmd = this->_menuFunc.Update(event);
	switch (cmd)
	{
	case GameOverOptions::None:
		
		break;
	case GameOverOptions::StartGame:
		return SnakeGame::SceneCommand(GameSceneRequest::Push, GameSceneType::Playing);
		break;
	case GameOverOptions::MainMenu:
		return SnakeGame::SceneCommand(GameSceneRequest::Push, GameSceneType::MainMenu);
		break;
	case GameOverOptions::Back:
		return SnakeGame::SceneCommand(GameSceneRequest::Push, GameSceneType::MainMenu);
		break;
	case GameOverOptions::Count:
		break;
	default:
		break;
	}
	this->update(dt);
    return SnakeGame::SceneCommand(GameSceneRequest::None);
}

SnakeGame::SceneCommand SnakeGame::Scene::SceneGameOver::update(float dt)
{
	for (auto& text : this->_menuOptions)
		text.setFillColor(sf::Color::White);
	int index = this->_menuFunc.GetSelectOptions() - 1;
	if (index >= 0 && index < this->_menuOptions.size())
		this->_menuOptions[index].setFillColor(sf::Color::Green);
	return SnakeGame::SceneCommand(GameSceneRequest::None);
}

void SnakeGame::Scene::SceneGameOver::draw(sf::RenderWindow& window)
{
	sf::Vector2f viewSize = window.getView().getSize();

	this->background.setOrigin(0.f, 0.f);
	this->background.setSize(viewSize);
	window.draw(this->background);

	this->gameOverText.setOrigin(GetTextOrigin(this->gameOverText, { 0.5f, 1.f }));
	this->gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
	window.draw(this->gameOverText);

	// We need to create new vector here as DrawItemsList needs vector of pointers
	std::vector<sf::Text*> textsList;
	textsList.reserve(this->recordsTableTexts.size());
	for (auto& text : this->recordsTableTexts)
	{
		textsList.push_back(&text);
	}

	sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 2.f };
	DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

	this->hintText.setOrigin(GetTextOrigin(this->hintText, { 0.5f, 1.f }));
	this->hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
	window.draw(this->hintText);

	for (auto& text : this->_menuOptions)
		window.draw(text);
}
