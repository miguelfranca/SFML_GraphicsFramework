#pragma once
#include "../sfml/Shapes.h"
#include "../holders/Widget.h"
#include "Button.h"

namespace GF {
	template<typename T = GF::Circle>
	class Slider : public Widget {
	public:
	
		Slider(float size, sf::Vector2f pos = CENTER_WINDOW, std::string orientacion = VERTICAL);
		Slider(sf::Vector2f size, sf::Vector2f pos = CENTER_WINDOW, std::string orientacion = VERTICAL);

		void handleEvent(const GF::Event& event, const sf::RenderWindow& window) override {}

		void draw(sf::RenderTarget& renderer, const sf::RenderStates state) const override {}

	private:
		/*GF::Button<> arrow_up;
		GF::Button<> arrow_down;
		GF::Button<T> slider;
		GF::Rectangle box;
		GF::Line line;*/
	};
}