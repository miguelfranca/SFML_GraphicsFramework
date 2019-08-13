#pragma once
#include "../sfml/Shapes.h"
#include "../holders/Widget.h"
#include "../sfml/Orientation.h"
#include "Button.h"
#include "../Tools/Random.hpp"

namespace GF {
	template<typename T = GF::Circle>
	class Slider : public Widget {
	public:

		template< typename U = T,
			typename = typename std::enable_if< std::is_same<U, GF::Circle>::value >::type >
		Slider(float size, const sf::Vector2f pos = CENTER_WINDOW, const Orientation o = GF::VERTICAL, const double mmax = 0, const double mmin = 0,
			sf::RenderTarget* renderer = nullptr)
		{
			CircleSlider(size, pos, o, mmax, mmin); m_target = renderer;
		}

		template< typename U = T,
			typename = typename std::enable_if< std::is_same<U, GF::Rectangle>::value >::type >
		Slider(sf::Vector2f size, const sf::Vector2f pos = CENTER_WINDOW, const Orientation o = GF::VERTICAL, const double mmax = 0, const double mmin = 0,
			sf::RenderTarget* renderer = nullptr)
		{
			RectSlider(size, pos, o, mmax, mmin); m_target = renderer;
		}

		bool handleEvent(GF::Event& event) override;
		bool draw() override;

		template<typename T2>
		T2 getValue() const {
			// calculates a fraction of the established limits
			if (this->orientation == GF::VERTICAL)
				return ((1 + ((box.getPosition().y - box.getSize().y / 2) - slider.getPosition().y) / box.getSize().y) * (max - min)) + min;
			if (this->orientation == GF::HORIZONTAL)
				return ((1 + ((box.getPosition().x - box.getSize().x / 2) - slider.getPosition().x) / box.getSize().x) * (max - min)) + min;

			return 0;
		}

		void setLimits(const double mmax, const double mmin) {
			max = mmax;
			min = mmin;
		}

		static GF::Slider<T>* makeRandom(sf::RenderTarget* renderer);

	private:
		T slider;
		GF::Rectangle box;
		GF::Line line;
		GF::Orientation orientation;

		double max, min;

	private:
		void CircleSlider(float size, const sf::Vector2f pos, const Orientation o, const double mmax, const double mmin);
		void RectSlider(sf::Vector2f size, const sf::Vector2f pos, const Orientation o, const double mmax, const double mmin);
	};


	template<typename T>
	bool Slider<T>::handleEvent(GF::Event& event) {
		static const float factor = -3.f * SW;
		if (orientation == GF::VERTICAL)
		{
			if (box.isRolledOn((sf::RenderWindow&)*m_target)) {
				if (GF::Mouse::Left.isPressed()) { // clicking inside the box sets the slider to the mouse position
					slider.setPosition(slider.getPosition().x, GF::Mouse::getPosition((sf::RenderWindow&)*m_target).y);
				}
				if (event.type == GF::Event::MouseWheelMoved) { // scrolling with the mouse wheel moves the slider
					if (box.getGlobalBounds().contains({ slider.getPosition().x, slider.getPosition().y + event.mouseWheel.delta * factor }))
						slider.move(0, event.mouseWheel.delta * factor);
				}
			}
		}

		// same for horizontal, but the coordinates are switched
		if (orientation == GF::HORIZONTAL)
		{
			if (box.isRolledOn((sf::RenderWindow&) * m_target)) {
				if (GF::Mouse::Left.isPressed()) {
					slider.setPosition(GF::Mouse::getPosition((sf::RenderWindow&) * m_target).x, slider.getPosition().y);
				}
				if (event.type == GF::Event::MouseWheelMoved) {
					if (box.getGlobalBounds().contains({ slider.getPosition().x + event.mouseWheel.delta * factor, slider.getPosition().y }))
						slider.move(event.mouseWheel.delta * factor, 0);
				}
			}
		}
		return true;
	}
}
