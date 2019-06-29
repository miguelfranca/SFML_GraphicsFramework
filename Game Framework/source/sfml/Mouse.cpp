#include "../../headers/sfml/Mouse.h"

namespace GF {
	Mouse::Button Mouse::Left(sf::Mouse::Left);
	Mouse::Button Mouse::Right(sf::Mouse::Right);

	Mouse::Mouse(){
	}

	Mouse::Button::Button(sf::Mouse::Button b) {
		button = b;
	}

	bool Mouse::Button::clickedOnce(sf::Event& event) {
		return event.type == event.MouseButtonReleased && event.mouseButton.button == button;
	}

	bool Mouse::Button::doubleClicked(sf::Event& event) {
		static sf::Clock clock;

		bool button_released = event.type == event.MouseButtonReleased && event.mouseButton.button == button;

		if (button_released && first_click && clock.getElapsedTime().asMilliseconds() < 250) // 250 ms between clicks
			return true;

		if (button_released && !first_click) {
			first_click = true;
			clock.restart();
			return false;
		}

		if (clock.getElapsedTime().asMilliseconds() > 400) // 400 ms to restore after last mouse double-click
			first_click = false;

		return false;
	}
}
