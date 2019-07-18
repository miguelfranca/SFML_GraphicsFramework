#pragma once

#include <SFML/Graphics.hpp>

namespace GF {

	class ToggleKey
	{
	public:
		ToggleKey(sf::Keyboard::Key key) : m_key(key) { }

		bool isKeyPressed() { return sf::Keyboard::isKeyPressed(m_key); }
		bool isKeyPressedOnce(const sf::Event& event){ return event.type == sf::Event::KeyPressed && event.key.code == m_key; }
		bool isKeyReleasedOnce(const sf::Event& event) { return event.type == sf::Event::KeyReleased && event.key.code == m_key; }

	private:
		sf::Keyboard::Key m_key;
	};
}
