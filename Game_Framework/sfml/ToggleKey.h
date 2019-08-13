#pragma once

#include <SFML/Graphics.hpp>

namespace GF {

	class ToggleKey
	{
	public:
		ToggleKey(sf::Keyboard::Key key) : m_key(key) { }

		inline bool isKeyPressed() { return sf::Keyboard::isKeyPressed(m_key); }
		inline bool isKeyPressedOnce(const GF::Event& event){ return event.type == GF::Event::KeyPressed && event.key.code == m_key; }
		inline bool isKeyReleasedOnce(const GF::Event& event) { return event.type == GF::Event::KeyReleased && event.key.code == m_key; }

	private:
		sf::Keyboard::Key m_key;
	};
}
