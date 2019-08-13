#pragma once

#include <functional>

#include "Game_Framework/holders/Widget.h"
#include "Game_Framework/sfml.h"

namespace GF {
	template<class T = GF::Rectangle>
	class Button : public Widget, public T{
	public:
		Button(sf::RenderTarget* renderer = nullptr, 
			float size = sf::Vector2f(0, 0), 
			const sf::Color text = sf::Color::White,
			const sf::Color outline = sf::Color::Green,
			const sf::Color fill = sf::Color::Black);

		Button(sf::RenderTarget* renderer = nullptr, 
			sf::Vector2f size = sf::Vector2f(0, 0),
			const sf::Color text = sf::Color::White,
			const sf::Color outline = sf::Color::Green,
			const sf::Color fill = sf::Color::Black);

		Button(sf::RenderTarget* renderer = nullptr,
			const sf::Texture* texture = nullptr,
			sf::Vector2f pos = sf::Vector2f(0, 0),
			sf::Vector2f size = sf::Vector2f(0, 0),
			const sf::Color outline = sf::Color::Green,
			const sf::Color fill = sf::Color::Black);

		void setFunction(void (*func)());
		void setText(const std::string str);
		void setText(const GF::Text &t);

		bool handleEvent(GF::Event& event) override;
		bool draw() override;
		void setPos(sf::Vector2f pos);

		static GF::Button<T>* makeRandom(sf::RenderTarget* renderer);

	private:

		sf::Color outline;
		sf::Color fill;

		Text        m_text;
		void (*m_function)() = NULL;
	};
}
