#pragma once
#include <SFML/Graphics.hpp>
#include "../Global.h"
#include "../holders/Drawable.h"
#include "Orientation.h"

namespace GF {

	class Text : public GF::Drawable, public sf::Text {
	public:
		template<typename T>
		Text(T text, sf::Vector2f pos = TOPLEFT_F, int charSize = DEFAULT_CHAR_SIZE, sf::Color color = DEFAULT_CHAR_COLOR, GF::Alignment origin = GF::CENTERED);
		Text(const char* text, sf::Vector2f pos = TOPLEFT_F, int charSize = DEFAULT_CHAR_SIZE, sf::Color color = DEFAULT_CHAR_COLOR, GF::Alignment origin = GF::CENTERED);
		Text(std::string text, sf::Vector2f pos = TOPLEFT_F, int charSize = DEFAULT_CHAR_SIZE, sf::Color color = DEFAULT_CHAR_COLOR, GF::Alignment origin = GF::CENTERED);
		Text(sf::Vector2f pos = TOPLEFT_F, int charSize = DEFAULT_CHAR_SIZE, sf::Color color = DEFAULT_CHAR_COLOR, GF::Alignment origin = GF::CENTERED);

		template<typename T>
		Text& operator=(T str);
		Text& operator=(const char* str);
		Text& operator=(const Text& t);
		friend std::ostream& operator<<(std::ostream& os, const Text& dt);

		void setCenter(const GF::Alignment origin);

		void draw(sf::RenderTarget& renderer, sf::RenderStates state) override;

	private:
		static sf::Font font;
		static void loadFont();
		static void setup(GF::Text&, std::string text, sf::Vector2f pos, int charSize, sf::Color color, GF::Alignment origin);
	};
}

