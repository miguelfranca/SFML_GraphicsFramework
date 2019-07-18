#pragma once

#include <functional>

#include "../holders/Widget.h"
#include "../../sfml.h"

namespace GF {
	template<class T = GF::Rectangle>
	class Button : public Widget, public T{
	public:
		Button(sf::Vector2f size = sf::Vector2f(0, 0), 
			const sf::Color t = sf::Color::White,
			const sf::Color outline = sf::Color::Green, 
			const sf::Color fill = sf::Color::Black);
		Button(float size = 0,
			const sf::Color t = sf::Color::White,
			const sf::Color outline = sf::Color::Green,
			const sf::Color fill = sf::Color::Black);

		void setFunction(void (*func)());
		void setText(const std::string str);
		void setText(const GF::Text &t);
		void setTexture(const sf::Texture& tex);

		void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
		void draw(sf::RenderTarget& renderer, sf::RenderStates state) const;
		void setPos(sf::Vector2f pos);

	private:

		sf::Color outline;
		sf::Color fill;

		Text        m_text;
		void (*m_function)() = NULL;
	};
}
