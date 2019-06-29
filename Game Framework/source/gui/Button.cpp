#include "../../headers/gui/Button.h"
#include "../../headers/Global.h"
#include "../../sfml.h"

namespace GF {
	Button<GF::Rectangle>::Button(sf::Vector2f size, const sf::Color t, const sf::Color o, const sf::Color f) : outline(o), fill(f)
	{
		m_text.setFillColor(t);
		this->setSize(size);
		this->setFillColor(f);
		this->setOutlineColor(o);
		this->setOutlineThickness(1);
	}

	Button<GF::Circle>::Button(float size, const sf::Color t, const sf::Color o, const sf::Color f) : outline(o), fill(f)
	{
		m_text.setFillColor(t);
		this->setRadius(size);
		this->setFillColor(f);
		this->setOutlineColor(o);
		this->setOutlineThickness(1);
	}

	void Button<GF::Rectangle>::setFunction(void (*func)())
	{
		m_function = func;
	}

	void Button<GF::Rectangle>::setText(const std::string str)
	{
		m_text.setString(str);
		m_text.setCenter(CENTERED);
	}

	void Button<GF::Rectangle>::setText(const GF::Text& t) {
		m_text = t;
	}

	template<class T>
	void Button<T>::setTexture(const sf::Texture& tex)
	{
		this->setTexture(tex);
	}

	template<class T>
	void Button<T>::handleEvent(const GF::Event& event, const sf::RenderWindow& window)
	{
		bool contains = this->isRolledOn(window);  // mouse is inside rectangle boundaries

		if (contains)
			this->setOutlineColor(sf::Color::Blue);
		else
			this->setOutlineColor(outline);

		if(event.type == GF::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && contains) // left mouse button is pressed
			if(m_function != NULL) m_function(); // function is defined
	}

	template<class T>
	void Button<T>::draw(sf::RenderTarget& renderer, const sf::RenderStates state) const
	{
		renderer.draw((T)*this, state);
		renderer.draw(m_text, state);
	}

	void Button<GF::Circle>::setPos(sf::Vector2f pos)
	{
		this->setPosition(pos);
		m_text.setPosition(pos);
	}
	void Button<GF::Rectangle>::setPos(sf::Vector2f pos)
	{
		this->setPosition(pos);
		m_text.setPosition(pos);
	}
}
