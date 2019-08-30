#include "Button.h"
#include "Game_Framework/Global.h"
#include "Game_Framework/sfml.h"
#include "Game_Framework/Tools/Random.hpp"

namespace GF {
	template<>
	Button<GF::Rectangle>::Button(sf::RenderTarget* renderer, sf::Vector2f size,
		const sf::Color t,
		const sf::Color o,
		const sf::Color f,
		const sf::Color o2) 
	: outline(o), fill(f), outline2(o2)
	{
		m_target = renderer;
		m_text.setFillColor(t);
		setup(size, { 0, 0 }, { size.x / 2, size.y / 2 }, f, o, 3);
	}

	template<>
	Button<GF::Circle>::Button(sf::RenderTarget* renderer, float size,
		const sf::Color t,
		const sf::Color o,
		const sf::Color f,
		const sf::Color o2)
	: outline(o), fill(f), outline2(o2)
	{
		m_target = renderer;
		setup(size, { 0, 0 }, f, o, 3);
	}

	template<>
	Button<GF::Rectangle>::Button(sf::RenderTarget* renderer, const sf::Texture* texture, sf::Vector2f pos,
		sf::Vector2f size,
		const sf::Color o,
		const sf::Color f,
		const sf::Color o2)
	: outline(o), fill(f), outline2(o2)
	{
		m_target = renderer;
		this->setTexture(texture);
		setup(size, pos, { size.x / 2, size.y / 2 }, fill, outline, 3);
	}


	template<>
	void Button<GF::Rectangle>::setFunction(void (*func)())
	{
		m_function = func;
	}

	template<>
	void Button<GF::Rectangle>::setText(const std::string str)
	{
		m_text.setString(str);
		m_text.setCenter(CENTERED);
	}

	template<>
	void Button<GF::Rectangle>::setText(const GF::Text& t) {
		m_text = t;
	}

	template<>
	void Button<GF::Rectangle>::setTextSize(unsigned size){
		m_text.setCharacterSize(size);
	}

	template<class T>
	bool Button<T>::handleEvent(GF::Event& event)
	{
		bool contains = this->isRolledOn((sf::RenderWindow&) * m_target);  // mouse is inside object boundaries
		if (contains)
			this->setOutlineColor(outline2);
		else
			this->setOutlineColor(outline);

		// if (GF::Mouse::Left.clicked(event) && contains) // left mouse button is pressed
		// 	if (m_function != nullptr) m_function(); // if function is defined execute it
		return true;
	}

	template<class T>
	bool Button<T>::draw()
	{
		m_target->draw((T)* this, sf::RenderStates::Default);
		m_target->draw(m_text, sf::RenderStates::Default);
		return true;
	}

	template<>
	void Button<GF::Rectangle>::setPos(sf::Vector2f pos)
	{
		this->setPosition(pos);
		m_text.setPosition(pos);
	}

	template<>
	GF::Button<GF::Circle>* GF::Button<GF::Circle>::makeRandom(sf::RenderTarget * renderer) {
		GF::Button<GF::Circle>* temp = new GF::Button<GF::Circle>(
			renderer,
			(float)Rand.getU(70 * SW, 200 * SW),
			sf::Color(Rand.getU(0, 255), Rand.getU(0, 255), Rand.getU(0, 255)), 
			sf::Color(Rand.getU(0, 255), Rand.getU(0, 255), Rand.getU(0, 255)),
			sf::Color(Rand.getU(0, 255), Rand.getU(0, 255), Rand.getU(0, 255)));
		temp->setOrigin(temp->getGlobalBounds().width / 2, temp->getGlobalBounds().height / 2);
		temp->setPosition(sf::Vector2f(Rand.getU(SCREENWIDTH / 4.f, SCREENWIDTH * 3.f / 4.f), Rand.getU(SCREENHEIGHT / 4.f, SCREENHEIGHT * 3.f / 4.f)));
		return temp;
	}
	template<>
	GF::Button<GF::Rectangle>* GF::Button<GF::Rectangle>::makeRandom(sf::RenderTarget* renderer) {
		GF::Button<GF::Rectangle>* temp = new GF::Button<GF::Rectangle>(
			renderer,
			sf::Vector2f((float)Rand.getU(70 * SW, 200 * SW), (float)Rand.getU(50 * SH, 200 * SH)),
			sf::Color(Rand.getU(0, 255), Rand.getU(0, 255), Rand.getU(0, 255)),
			sf::Color(Rand.getU(0, 255), Rand.getU(0, 255), Rand.getU(0, 255)),
			sf::Color(Rand.getU(0, 255), Rand.getU(0, 255), Rand.getU(0, 255)));
		temp->setOrigin(temp->getGlobalBounds().width / 2, temp->getGlobalBounds().height / 2);
		temp->setText(std::string("Button"));
		temp->setPos(sf::Vector2f(Rand.getU(SCREENWIDTH / 4.f, SCREENWIDTH * 3.f / 4.f), Rand.getU(SCREENHEIGHT / 4.f, SCREENHEIGHT * 3.f / 4.f)));
		return temp;
	}
}
