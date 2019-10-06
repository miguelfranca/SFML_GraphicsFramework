#include "Textbox.h"
#include "Game_Framework/Tools/Random.hpp"

namespace GF {

	TextBox::TextBox(sf::RenderTarget* renderer) : writing(renderer, sf::Vector2f(0, 0)) {
		setup(sf::Vector2f(200, 50), CENTER_WINDOW, "Search");
		if (m_target == nullptr)
			m_target = renderer;
	}

	TextBox::TextBox(sf::Vector2f size, sf::Vector2f pos, std::string _init_text,
		sf::RenderTarget* renderer) : writing(renderer, sf::Vector2f(0, 0)){
		m_target = renderer;
		setup(size, pos, _init_text);
	}

	void TextBox::setup(sf::Vector2f size, sf::Vector2f pos, std::string _init_text) {
		size.x *= SW;
		size.y *= SH;

		init_text = _init_text;
		text = _init_text;

		writing.setTarget(m_target);
		writing.setSize(size);
		writing.setPos(pos);
		writing.setOrigin(size.x / 2, size.y / 2);

		m_text.setCharacterSize((int)(size.y * 0.75));
		m_text.setString(init_text);
		m_text.setCenter(MIDDLELEFT);
		m_text.setPosition(sf::Vector2f(pos.x - size.x / 2 + 10 * SW, pos.y));
		m_text.setFillColor(sf::Color(192, 192, 192));

		while(m_text.getLocalBounds().width + 20 * SW >= writing.getGlobalBounds().width)
			m_text.setCharacterSize(m_text.getCharacterSize() - 1);
		
		writing.setText(m_text);
	}

	bool TextBox::handleEvent(GF::Event & event)
	{
		handleClick(event);
		handleTextInput(event);
		return true;
	}

	bool TextBox::draw()
	{
		writing.draw();

		// Flashing line after text. Only draws for 500ms every 1000ms (1 second)
		static sf::Clock clk;
		if (m_isActive && clk.getElapsedTime().asMilliseconds() > 500 && !textIsSelected)
			m_target->draw(line, sf::RenderStates::Default);
		if (clk.getElapsedTime().asMilliseconds() > 1000) clk.restart();
		return true;
	}

	bool TextBox::update(const float fElapsedTime, const float fTotalTime) {
		// updates the flashing line after the text. Only updates when the text is not selected, because it is only drawn when that happens
		if (!textIsSelected) {
			sf::FloatRect rec = m_text.getLocalBounds();
			line = GF::Line(sf::Vector2f(m_text.getPosition().x + rec.width + 2 * SW, writing.getPosition().y + 5 * SH - writing.getSize().y / 2),
				sf::Vector2f(m_text.getPosition().x + rec.width + 2 * SW, writing.getPosition().y + writing.getSize().y / 2 - 5 * SH));
		}
		return true;
	}

	void TextBox::setPosition(const sf::Vector2f pos)
	{
		writing.setPos(pos);
	}

	void TextBox::handleClick(GF::Event & event)
	{
		static GF::ToggleKey C(sf::Keyboard::C);
		static GF::ToggleKey V(sf::Keyboard::V);
		static GF::ToggleKey X(sf::Keyboard::X);
		static GF::ToggleKey A(sf::Keyboard::A);

		// CTRL + C / X to copy to clipboard (LCONTROL/RCONTROL + C/X)
		if (event.key.control && (C.isKeyReleasedOnce(event) || X.isKeyPressedOnce(event)) && textIsSelected) {
			sf::Clipboard::setString(text.c_str());
			return;
		}

		// CTRL + X to copy to clipboard (LCONTROL/RCONTROL + X)
		if (event.key.control && X.isKeyPressedOnce(event) && textIsSelected) {
			sf::Clipboard::setString(text.c_str());
			return;
		}

		// CTRL + V to paste from clipboard (LCONTROL/RCONTROL + V)
		if (event.key.control &&
			V.isKeyReleasedOnce(event)) {

			// replaces the text if it is being slected (blue color). Otherwise, just add to it
			if (textIsSelected)
				text = sf::Clipboard::getString().toAnsiString();
			else
				text += sf::Clipboard::getString().toAnsiString();

			// update text
			setText(text);
			m_text.setFillColor(sf::Color::White);
			setTextNotSelected();
			return;
		}

		// CTRL + A to select the text (LCONTROL/RCONTROL + A)
		if (event.key.control && A.isKeyReleasedOnce(event) && text != "" && m_isActive) {
			if (!textIsSelected) setTextSelected();
			return;
		}

		// double click on mouse to select the text - makes it blue
		if (GF::Mouse::Left.doubleClicked(event) && writing.isRolledOn((sf::RenderWindow&)*m_target) && text != "") {
			if (!textIsSelected) setTextSelected();
			return;
		}

		// beggin writing by clicking inside the box
		if (GF::Mouse::Left.clicked(event) && writing.isRolledOn((sf::RenderWindow&)*m_target)) {
			if (text == init_text && !m_isActive) {
				text = "";
				setText(text);
			}

			// update text
			m_text.setFillColor(sf::Color::White);
			setTextNotSelected();
			m_isActive = true;
		}

		// stop writing by clicking outside the box
		if (GF::Mouse::Left.clicked(event) && !writing.isRolledOn((sf::RenderWindow&)*m_target)) {
			m_isActive = false;
			m_text.setFillColor(sf::Color(192, 192, 192)); // gray
			if (text == "") {
				text = init_text;
				setText(text);
			}
			setTextNotSelected();
			return;
		}
	}

	void TextBox::setTextSelected() {
		m_text.setFillColor(sf::Color(0, 0, 205));
		textIsSelected = true;
		writing.setText(m_text);
	}

	void TextBox::setTextNotSelected() {
		textIsSelected = false;
		writing.setText(m_text);
	}

	void TextBox::handleTextInput(GF::Event& event)
	{
		if (m_isActive) {
			if (event.type == GF::Event::TextEntered) {
				// Get the key that was entered
				unsigned char keyCode = event.text.unicode;

				// if text is selected ( blue ) then the next letter written will erase the text and start writing from beggining 
				if (textIsSelected) {
					// avoid deleting text (see comment above) while trying to copy or paste text (LCONTROL/RCONTROL + C/V/A)
					// with LCONTROL/RCONTROL + X there is no need for handling. The text is deleted (was copied to clipboard previously on handleEvent)
					if (event.key.control
						&& (sf::Keyboard::isKeyPressed(sf::Keyboard::C) || sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
						return;

					text = "";
					m_text.setString(text);
					m_text.setFillColor(sf::Color::White);
					setTextNotSelected();
				}

				if (isValidCharacter(keyCode)) {
					// if everything is ok, just add the letter to the string
					text.push_back(keyCode);
				}
				else if (isBackspace(keyCode)) {
					// prevents popping back an empty string
					if (text.length() > 0)
						text.pop_back();
				}

				setText(text);
				writing.setText(m_text);
			}
			if ((event.type == GF::Event::KeyReleased && event.key.code == sf::Keyboard::F)) event.skip(); // to prevent the fps to change its state
		}
	}

	/*Recursive function for the displayed text.
	Used to only display the part of the text that is inside the textbox.
	Keeps the "origin" at the last written letter so, the first letters, as soon as the text doesnt fit the textbox, will disapear*/
	void TextBox::setText(const std::string str) {
		m_text.setString(str);
		if (m_text.getLocalBounds().width + 20 * SW >= writing.getGlobalBounds().width) {
			std::string s = m_text.getString().toAnsiString().erase(0, 1);
			setText(s);
		}
	}

	bool TextBox::isValidCharacter(unsigned char keyCode)
	{
		//return  keyCode >= 48 && keyCode <= 57 ||  //Numbers
		//	keyCode >= 65 && keyCode <= 90 ||  //Uppercase
		//	keyCode >= 97 && keyCode <= 122 ||  //Lowercase
		//	keyCode == 32;    //Space
		return keyCode >= 32 && keyCode <= 126; // all normal characters and special characters too
	}

	bool TextBox::isBackspace(unsigned char keycode)
	{
		return keycode == 8;
	}

	GF::TextBox* GF::TextBox::makeRandom(sf::RenderTarget* renderer) {
		return new GF::TextBox(
			sf::Vector2f(Rand.getU(100 * SW, SCREENWIDTH / 2.f), Rand.getU(20 * SH, 70 * SH)),
			sf::Vector2f(Rand.getU(SCREENWIDTH / 4.f, SCREENWIDTH * 3.f / 4.f), Rand.getU(SCREENHEIGHT / 4.f, SCREENHEIGHT * 3.f / 4.f)),
			"Search", renderer);
	}

}