#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace SnakeGame {
	template <typename T>
	class MenuFunctionality
	{
	private:
		int _menuSelectedOptions = 1;
	public:

		MenuFunctionality() {

		}

		MenuFunctionality(int index) {
			if (index > 1 && index < static_cast<int>(T::Count) - 2)
				this->_menuSelectedOptions = index;
		}

		int GetSelectOptions()
		{
			return this->_menuSelectedOptions;
		}

		T Update(sf::Event& event)
		{
			if (event.type == sf::Event::Closed) {
				return static_cast<T>(T::Count);
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{
				case sf::Keyboard::S:
					if (this->_menuSelectedOptions < static_cast<int>(T::Count) - 2) {
						this->_menuSelectedOptions++;
					}
					break;
				case sf::Keyboard::W:
					if (this->_menuSelectedOptions > 1) {
						this->_menuSelectedOptions--;
					}
					break;
				case sf::Keyboard::Enter:
					return static_cast<T>(this->_menuSelectedOptions);
					break;
				case sf::Keyboard::B:
					return static_cast<T>(static_cast<int>(T::Count) - 1);
				default:
					break;
				}
			}

			return static_cast<T>(0);
		}
	};
}

