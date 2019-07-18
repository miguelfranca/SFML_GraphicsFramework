#pragma once
#include "../sfml/Shapes.h"
#include "../holders/Widget.h"
#include "Button.h"

namespace GF {
	template<typename T = GF::Circle>
	class Slider : public Widget {
	public:
	
		Slider(float size, const sf::Vector2f pos = CENTER_WINDOW, const std::string orientacion = VERTICAL, const double max = 0, const double min = 0);
		Slider(sf::Vector2f size, const sf::Vector2f pos = CENTER_WINDOW, const std::string orientacion = VERTICAL, const double max = 0, const double min = 0);

		void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

		void draw(sf::RenderTarget& renderer, const sf::RenderStates state) const override;

		template<typename T2>
		T2 getValue() const {
			// calculates a fraction of the established limits
			if (this->orientacion == VERTICAL)
				return ((1 + ((box.getPosition().y - box.getSize().y / 2) - slider.getPosition().y) / box.getSize().y) * (max - min)) + min;
			if (this->orientacion == HORIZONTAL)
				return ((1 + ((box.getPosition().x - box.getSize().x / 2) - slider.getPosition().x) / box.getSize().x) * (max - min)) + min;

			return 0;
		}

		void setLimits(const double mmax, const double mmin) {
			max = mmax;
			min = mmin;
		}

	private:
		T slider;
		GF::Rectangle box;
		GF::Line line;

		std::string orientacion;
		double max, min;

		void (*m_function) () = nullptr;
	};
}