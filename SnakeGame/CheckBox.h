#pragma once
#include <SFML/Graphics.hpp>


namespace SnakeGame {
	namespace UI {
		class CheckBox
		{
		private:
			sf::RectangleShape _box;
			sf::Text _checkMark;
			bool _checked;

		public:
            CheckBox() {
                this->_checked = false;
            }

            CheckBox(sf::Font& font, float x, float y, bool check)
            {
                this->_box.setSize({ 20, 20 });
                this->_box.setFillColor(sf::Color::White);
                this->_box.setOutlineColor(sf::Color::Black);
                this->_box.setOutlineThickness(2);
                this->_box.setPosition(x, y);

                this->_checkMark.setFont(font);
                this->_checkMark.setString("X");
                this->_checkMark.setCharacterSize(18);
                this->_checkMark.setFillColor(sf::Color::Black);
                this->_checkMark.setPosition(x + 3, y - 3);

                this->_checked = check;
            }

            void init(sf::Font& font, float x, float y, bool check)
            {
                this->_box.setSize({ 20, 20 });
                this->_box.setFillColor(sf::Color::White);
                this->_box.setOutlineColor(sf::Color::Black);
                this->_box.setOutlineThickness(2);
                this->_box.setPosition(x, y);

                this->_checkMark.setFont(font);
                this->_checkMark.setString("X");
                this->_checkMark.setCharacterSize(18);
                this->_checkMark.setFillColor(sf::Color::Black);
                this->_checkMark.setPosition(x + 3, y - 3);
                this->_checked = check;
            }

            void draw(sf::RenderWindow& window)
            {
                window.draw(this->_box);
                if (this->_checked)
                    window.draw(this->_checkMark);
            }

            void set(bool f)
            {
                this->_checked = f;
            }

            bool isChecked() const
            {
                return this->_checked;
            }
		};
	}
}

