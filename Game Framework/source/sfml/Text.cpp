#include "../../headers/sfml/Text.h"

#define DEFAULT_FONT "Game Framework/res/fonts/Arial.ttf"

namespace GF {

	sf::Font Text::font;

	std::ostream& operator<<(std::ostream& os, const Text& text)
	{
		os << text.getString().toAnsiString();
		return os;
	}

	Text::Text(sf::Vector2f pos, int charSize, sf::Color color, std::string origin){
		setup(*this, "", pos, charSize, color, origin);
	}

	Text::Text(const char* text, sf::Vector2f pos, int charSize, sf::Color color, std::string origin) {
		setup(*this, text, pos, charSize, color, origin);
	}

	Text::Text(std::string text, sf::Vector2f pos, int charSize, sf::Color color, std::string origin) {
		setup(*this, text, pos, charSize, color, origin);
	}

	template<typename T>
	Text::Text(T text, sf::Vector2f pos, int charSize, sf::Color color, std::string origin) {
		setup(*this, std::to_string(text), pos, charSize, color, origin);
	}

	void Text::setup(GF::Text& t, std::string text, sf::Vector2f pos, int charSize, sf::Color color, std::string origin) {
		loadFont();
		t.setFont(font);
		t.setString(text);
		t.setCharacterSize(charSize);
		t.setFillColor(color);
		t.setCenter(origin);
		t.setPosition(pos);
	}

	template<typename T>
	Text& Text::operator=(T str) {
		setString(std::to_string(str));
		return *this;
	}
	Text& Text::operator=(const char* str) {
		setString(str);
		return *this;
	}

	Text& Text::operator=(const Text& t) {
		this->setFillColor(t.getFillColor());
		this->setCharacterSize(t.getCharacterSize());
		this->setFont(*t.getFont());
		this->setLetterSpacing(t.getLetterSpacing());
		this->setLineSpacing(t.getLineSpacing());
		this->setOrigin(t.getOrigin());
		this->setOutlineColor(t.getOutlineColor());
		this->setOutlineThickness(t.getOutlineThickness());
		this->setPosition(t.getPosition());
		this->setRotation(t.getRotation());
		this->setScale(t.getScale());
		this->setString(t.getString());
		this->setStyle(t.getStyle());
		return *this;
	}

	void Text::setCenter(const std::string origin) {
		sf::FloatRect textRect = getLocalBounds();
		if (origin == CENTERED) 
			setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		if (origin == TOPLEFT)
			setOrigin(textRect.left, textRect.top);
		if (origin == MIDDLELEFT)
			setOrigin(textRect.left, textRect.top + textRect.height / 2.0f);
	}

	void Text::loadFont() {
		if (font.getInfo().family.empty())
			font.loadFromFile(DEFAULT_FONT);
	}

	void Text::draw(sf::RenderTarget& renderer, sf::RenderStates state) {
		renderer.draw(*this, state);
	}
}
