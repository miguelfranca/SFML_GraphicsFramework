#pragma once

#include <SFML/Graphics.hpp>
#include "Event.h"

namespace GF {

	class ToggleKey
	{
	public:
		ToggleKey(sf::Keyboard::Key key) : m_key(key) { }

		bool isKeyPressed() { return sf::Keyboard::isKeyPressed(m_key); }
		bool isKeyPressedOnce(const GF::Event& event){ return event.type == GF::Event::KeyPressed && event.key.code == m_key; }
		bool isKeyReleasedOnce(const GF::Event& event) { return event.type == GF::Event::KeyReleased && event.key.code == m_key; }

	private:
		sf::Keyboard::Key m_key;
	};
}
