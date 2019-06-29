#include "../../headers/sfml/ToggleKey.h"

namespace GF {

	ToggleKey::ToggleKey(sf::Keyboard::Key key)
		: m_key(key)
	{ }

	bool ToggleKey::isKeyPressed()
	{
		if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
			if (sf::Keyboard::isKeyPressed(m_key)) {
				m_delayTimer.restart();
				return true;
			}
		}
		return false;
	}

	bool ToggleKey::isKeyPressedOnce() {
		static bool keyWasPressed = false;

		if (keyWasPressed) {
			if (!sf::Keyboard::isKeyPressed(m_key))
				keyWasPressed = false;
			return false;
		}
		else {
			if (sf::Keyboard::isKeyPressed(m_key)) {
				keyWasPressed = true;
				return true;
			}
			return false;
		}
	}
}
