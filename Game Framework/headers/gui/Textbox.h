#pragma once
#include "../Global.h"
#include "Button.h"
#include "../holders/Widget.h"
#include "../sfml/Event.h"

namespace GF {
	class TextBox : public Widget {
	public:

		TextBox();

		TextBox(sf::Vector2f size, sf::Vector2f pos = CENTER_WINDOW, std::string _init_text = "Search");

		void handleEvent(const GF::Event& event, const sf::RenderWindow& window) override;

		void update(float fElapsedTime);

		void setPosition(const sf::Vector2f pos);

		void draw(sf::RenderTarget& renderer, const sf::RenderStates state) const override;

		inline std::string getText() const { return text; }

	private:

		void setup(sf::Vector2f size, sf::Vector2f pos, std::string _init_text);

		void handleClick(const GF::Event& event, const sf::RenderWindow& window);
		void handleTextInput(const GF::Event& event);

		bool isValidCharacter(unsigned char keyCode);
		bool isBackspace(unsigned char keycode);

	private:

		bool m_isActive = false;

		std::string init_text;
		Button<GF::Rectangle> writing;

		GF::Text m_text;
		std::string text;
		GF::Line line;

		bool textIsSelected = false;

	private:
		void setText(const std::string str);
		void setTextSelected();
		void setTextNotSelected();
	};
}