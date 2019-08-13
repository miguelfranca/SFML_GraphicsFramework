#pragma once
#include "../Global.h"
#include "Button.h"
#include "../holders/Widget.h"

namespace GF {
	class TextBox : public Widget {
	public:

		TextBox(sf::RenderTarget* renderer = nullptr);

		TextBox(sf::Vector2f size, sf::Vector2f pos = CENTER_WINDOW, std::string _init_text = "Search",
			sf::RenderTarget* renderer = nullptr);

		// handles text and mouse input events
		bool handleEvent(GF::Event& event) override;

		// updates the flashing line in front of the text
		bool update(const float fElapsedTime, const float fTotalTime) override;

		void setPosition(const sf::Vector2f pos);

		// draws the button and line ( the Button class already has a text member variable, so when drawing the box the text is also drawn) 
		bool draw() override;

		inline std::string getText() const { return text; }

		static GF::TextBox* makeRandom(sf::RenderTarget* renderer);


	private:

		// setup the button and text variables
		void setup(sf::Vector2f size, sf::Vector2f pos, std::string _init_text);

		void handleClick(GF::Event& event);
		void handleTextInput(GF::Event& event);

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
