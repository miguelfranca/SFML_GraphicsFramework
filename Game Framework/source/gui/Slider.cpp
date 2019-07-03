#include "../../headers/gui/Slider.h"

namespace GF {
	Slider<GF::Circle>::Slider(float size, const sf::Vector2f pos, const std::string o, const double mmax, const double mmin)
	{
		orientacion = o;
		slider.setup(7*SW, pos, sf::Color(150, 150, 150), sf::Color::White, 1);
		size *= SW;

		if (orientacion == HORIZONTAL) 
		{
			line = GF::Line(sf::Vector2f(pos.x - size / 2, pos.y), sf::Vector2f(pos.x + size / 2, pos.y));
			box = GF::Rectangle(sf::Vector2f(size, 40*SH), pos, CENTERED);
		}
		if (orientacion == VERTICAL)
		{
			line = GF::Line(sf::Vector2f(pos.x, pos.y - size / 2), sf::Vector2f(pos.x, pos.y + size / 2));
			box = GF::Rectangle(sf::Vector2f(40 * SW, size), pos, CENTERED);
		}
		max = mmax;
		min = mmin;
	}

	Slider<GF::Rectangle>::Slider(sf::Vector2f size, const sf::Vector2f pos, const std::string o, const double mmax, const double mmin)
	{
		orientacion = o;
		max = mmax;
		min = mmin;

		size.x *= SW;
		size.y *= SH;

		box = GF::Rectangle(size, pos, CENTERED, sf::Color::Transparent, sf::Color::White, 1);

		static const float side = 10.f * SW;

		if (orientacion == HORIZONTAL)
		{
			slider.setup(sf::Vector2f(side, size.y), pos, sf::Vector2f(side / 2, size.y / 2), sf::Color::White, sf::Color::Transparent, 0);
		}
		if (orientacion == VERTICAL)
		{
			slider.setup(sf::Vector2f(size.x, side), pos, sf::Vector2f(size.x / 2, side / 2), sf::Color::White, sf::Color::Transparent, 0);
		}
	}

	template<class T2>
	void Slider<T2>::handleEvent(const GF::Event& event, const sf::RenderWindow& window)
	{
		static const float factor = -3.f * SW;
		if (orientacion == VERTICAL)
		{
			if (box.isRolledOn(window)) {
				if (GF::Mouse::Left.isPressed()) { // clicking inside the box sets the slider to the mouse position
					slider.setPosition(slider.getPosition().x, GF::Mouse::getPosition(window).y);
					if (m_function != nullptr) m_function();
				}
				if (event.type == GF::Event::MouseWheelMoved) { // scrolling with the mouse wheel moves the slider
					if (box.getGlobalBounds().contains({ slider.getPosition().x, slider.getPosition().y + event.mouseWheel.delta * factor }))
						slider.move(0, event.mouseWheel.delta * factor);
					if (m_function != nullptr) m_function();
				}
			}
		}

		// same for horizontal, but the coordinates are switched
		if (orientacion == HORIZONTAL)
		{
			if (box.isRolledOn(window)) {
				if (GF::Mouse::Left.isPressed()) {
					slider.setPosition(GF::Mouse::getPosition(window).x, slider.getPosition().y);
					if (m_function != nullptr) m_function();
				}
				if (event.type == GF::Event::MouseWheelMoved) {
					if (box.getGlobalBounds().contains({ slider.getPosition().x + event.mouseWheel.delta * factor, slider.getPosition().y }))
						slider.move(event.mouseWheel.delta * factor, 0);
					if (m_function != nullptr) m_function();
				}
			}
		}
	}

	void Slider<GF::Circle>::draw(sf::RenderTarget & renderer, const sf::RenderStates state) const
	{
		renderer.draw(line);
		renderer.draw(slider);
	}
	void Slider<GF::Rectangle>::draw(sf::RenderTarget & renderer, const sf::RenderStates state) const
	{
		renderer.draw(slider);
		renderer.draw(box);
	}
}