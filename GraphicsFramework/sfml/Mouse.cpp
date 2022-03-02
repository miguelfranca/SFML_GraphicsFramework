#include "Mouse.h"
#include "Event.h"
#include <iostream>

namespace GF {
	Mouse::Button Mouse::Left(sf::Mouse::Left);
	Mouse::Button Mouse::Right(sf::Mouse::Right);
	Mouse::Middle Mouse::Wheel;

	Mouse::Mouse(){
	}

	Mouse::Button::Button(sf::Mouse::Button b) {
		button = b;
	}

	bool Mouse::Button::clicked(const GF::Event &event) {
		return event.type == GF::Event::MouseButtonPressed && event.mouseButton.button == button;
	}

	bool Mouse::Button::doubleClicked(const GF::Event& event) {

		bool button_released = event.type == GF::Event::MouseButtonReleased && event.mouseButton.button == button;

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

	bool Mouse::Button::released(const GF::Event& event) {
		return event.type == GF::Event::MouseButtonReleased && event.mouseButton.button == button;
	}
	
	bool Mouse::Button::isPressed() {
		return sf::Mouse::isButtonPressed(button);
	}

	sf::Vector2f Mouse::getPosition(const sf::RenderWindow& window) {
		return sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
	}

	bool Mouse::Middle::moved(GF::Event &event)
	{
		return event.type == sf::Event::MouseWheelMoved;
	}
	int Mouse::Middle::delta(GF::Event &event)
	{
		return event.mouseWheel.delta;
	}
}
