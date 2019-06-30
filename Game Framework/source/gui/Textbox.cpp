#include "../../headers/gui/Textbox.h"
#include <windows.h>


namespace GF {
	void CopyToClipboard(const char* str);
	std::string GetClipboardText();

	TextBox::TextBox() : writing(sf::Vector2f(0, 0)) { setup(sf::Vector2f(200, 50), CENTER_WINDOW, "Search"); }
	TextBox::TextBox(sf::Vector2f size, sf::Vector2f pos, std::string _init_text) : writing(sf::Vector2f(0, 0)) {
		setup(size, pos, _init_text);
	}

	void TextBox::setup(sf::Vector2f size, sf::Vector2f pos, std::string _init_text) {
		init_text = _init_text;
		text = _init_text;

		writing.setSize(size);
		writing.setPos(pos);
		writing.setOrigin(size.x / 2, size.y / 2);

		m_text.setString(init_text);
		m_text.setCenter(MIDDLELEFT);
		m_text.setPosition(sf::Vector2f(pos.x - size.x / 2 + 10, pos.y));
		m_text.setFillColor(sf::Color(192, 192, 192));

		writing.setText(m_text);
	}

	void TextBox::handleEvent(const GF::Event & event, const sf::RenderWindow & window)
	{
		handleClick(event, window);
		handleTextInput(event);
	}

	void TextBox::draw(sf::RenderTarget & renderer, const sf::RenderStates state) const
	{
		renderer.draw(writing, state);

		// Flashing line after text. Only draws for 500ms every 1000ms (1 second)
		static sf::Clock clk;
		if (m_isActive && clk.getElapsedTime().asMilliseconds() > 500 && !textIsSelected)
			renderer.draw(line, state);
		if (clk.getElapsedTime().asMilliseconds() > 1000) clk.restart();
	}

	void TextBox::update() {
		// updates the flashing line after the text. Only updates when the text is not selected, because it is only drawn when that happens
		if (!textIsSelected) {
			sf::FloatRect rec = m_text.getLocalBounds();
			line = GF::Line(sf::Vector2f(m_text.getPosition().x + rec.width + 5, writing.getPosition().y + 10 - writing.getSize().y / 2),
				sf::Vector2f(m_text.getPosition().x + rec.width + 5, writing.getPosition().y + writing.getSize().y / 2 - 10));
		}
	}

	void TextBox::setPosition(const sf::Vector2f pos)
	{
		writing.setPos(pos);
	}

	void TextBox::handleClick(const GF::Event & event, const sf::RenderWindow & window)
	{
		static GF::ToggleKey C(sf::Keyboard::C);
		static GF::ToggleKey V(sf::Keyboard::V);
		// CTRL*C to copy to clipboard (LCONTROL/RCONTROL + C)
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			&& C.isKeyReleasedOnce(event) && textIsSelected) {
			CopyToClipboard(text.c_str());
			return;
		}

		// CTRL+V to paste from clipboard (LCONTROL/RCONTROL + V)
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			&& V.isKeyReleasedOnce(event)) {

			// replaces the text if it is being slected (blue color). Otherwise, just add to it
			if (textIsSelected)
				text = GetClipboardText();
			else
				text += GetClipboardText();

			// update text
			setText(text);
			m_text.setFillColor(sf::Color::White);
			setTextNotSelected();
			return;
		}

		// select text by double clicking - makes it blue
		bool isclicked = writing.isClicked(event, window);
		if (event.type == GF::Event::LeftMouseDoubleClickedEvent && writing.isRolledOn(window) && text != "") {
			//text = "";
			if (!textIsSelected) setTextSelected();
			return;
		}

		// beggin writing by clicking inside the box
		if (event.type == GF::Event::LeftMouseClickedOnceEvent && writing.isRolledOn(window)) {
			if (text == init_text && !m_isActive) {
				text = "";
				setText(text);
			}

			// update text
			setTextNotSelected();
			m_text.setFillColor(sf::Color::White);
			writing.setText(m_text);
			m_isActive = true;
		}

		// stop writing by clicking outside the box
		if (event.type == GF::Event::LeftMouseClickedOnceEvent && !writing.isRolledOn(window)) {
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
		m_text.setOutlineColor(sf::Color::Transparent);
		textIsSelected = false;
		writing.setText(m_text);
	}

	void TextBox::handleTextInput(const GF::Event & event)
	{
		if (event.type == GF::Event::TextEntered && m_isActive) {
			// Get the key that was entered
			unsigned char keyCode = event.text.unicode;

			// if text is selected ( blue ) then the next letter written will erase the text and start writing from beggining 
			if (textIsSelected) {
				// avoid deleting text (see comment above) while trying to copy or paste text (LCONTROL/RCONTROL + C/V)
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					&& (sf::Keyboard::isKeyPressed(sf::Keyboard::C) || sf::Keyboard::isKeyPressed(sf::Keyboard::V))) return;

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
	}

	/*Recursive function for the displayed text.
	Used to only display the part of the text that is inside the textbox.
	Keeps the "origin" at the last written letter so, the first letters, as soon as the text doesnt fit the textbox, will disapear*/
	void TextBox::setText(const std::string str) {
		m_text.setString(str);
		if (m_text.getLocalBounds().width + 20 >= writing.getGlobalBounds().width) {
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

	// https://stackoverflow.com/questions/1264137/how-to-copy-string-to-clipboard-in-c
	void CopyToClipboard(const char* str) {
		const size_t len = strlen(str) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), str, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}

	// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
	std::string GetClipboardText()
	{
		// Try opening the clipboard
		if (!OpenClipboard(nullptr)) {
			std::cout << "couldnt open the clipboard" << std::endl;
			exit(0);
		}

		// Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr)
			std::cout << "error getting handle of clipboard object" << std::endl;

		// Lock the handle to get the actual text pointer
		char* pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr)
			std::cout << "error locking the handle" << std::endl;

		// Save text in a string class instance
		std::string text(pszText);

		// Release the lock
		GlobalUnlock(hData);

		// Release the clipboard
		CloseClipboard();

		return text;
	}
}