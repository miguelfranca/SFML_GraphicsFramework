#pragma once

#include <SFML/Graphics.hpp>

namespace GF {

	class Widget
	{
	public:
		virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;

		virtual void draw(sf::RenderTarget& renderer, const sf::RenderStates state) const = 0;
	};
}
