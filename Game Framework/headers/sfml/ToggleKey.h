#pragma once

#include <SFML/Graphics.hpp>
#include "Event.h"

namespace GF {

	class ToggleKey
	{
	public:
		ToggleKey(sf::Keyboard::Key);

		bool isKeyPressed();
		bool isKeyPressedOnce();
		bool isKeyReleasedOnce(const GF::Event& event) { return event.type == GF::Event::KeyReleased && event.key.code == m_key; }

	private:
		sf::Keyboard::Key m_key;
		sf::Clock m_delayTimer;
	};
}
