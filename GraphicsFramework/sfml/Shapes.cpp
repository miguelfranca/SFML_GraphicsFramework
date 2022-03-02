#include "Shapes.h"
#include "Mouse.h"
#include "VectorOp.h"
#include "GraphicsFramework/Util/Maths.h"
#include "Event.h"
#include "Orientation.h"

namespace GF
{

	Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color fill,
	                     sf::Color outline,
	                     float thickness)
	{
		setup(size, pos, { 0, 0 }, fill, outline, thickness);
	}
	Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, GF::Alignment origin,
	                     sf::Color fill,
	                     sf::Color outline, float thickness)
	{
		if (origin == GF::CENTERED)
			setup(size, pos, sf::Vector2f(size.x / 2, size.y / 2), fill, outline, thickness);

		if (origin == GF::TOPLEFT)
			setup(size, pos, { 0, 0 }, fill, outline, thickness);
	}
	Rectangle::Rectangle(sf::FloatRect rect)
	{
		setup(sf::Vector2f(rect.width, rect.height), sf::Vector2f(rect.left, rect.top),
		      sf::Vector2f(0, 0),
		      sf::Color::Transparent, sf::Color::Red, 1);
	}

	void Rectangle::setup(sf::Vector2f size, sf::Vector2f pos, sf::Vector2f origin,
	                      sf::Color fill,
	                      sf::Color outline, float thickness)
	{
		setSize(size);
		setOrigin(origin);
		setPosition(pos);
		setFillColor(fill);
		setOutlineColor(outline);
		setOutlineThickness(thickness);
	}

	bool Rectangle::Rectangle::isRolledOn(const sf::RenderWindow& window) const
	{
		auto pos = sf::Mouse::getPosition(window);
		return getGlobalBounds().contains((float)pos.x, (float)pos.y);
	}

	bool Rectangle::Rectangle::isClicked(const GF::Event& event) const
	{
		return getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
		       && GF::Mouse::Left.clicked(event);
	}

	Circle::Circle(float radius, sf::Vector2f pos, sf::Color fill, sf::Color outline,
	               float thickness)
	{
		setup(radius, pos, fill, outline, thickness);
	}

	void Circle::setup(float radius, sf::Vector2f pos, sf::Color fill, sf::Color outline,
	                   float thickness)
	{
		setRadius(radius);
		setOrigin(radius, radius);
		setPosition(pos);
		setFillColor(fill);
		setOutlineColor(outline);
		setOutlineThickness(thickness);
	}

	bool Circle::contains(sf::Vector2f pos, float threshold) const
	{
		return (getRadius() + threshold) >= dist(getPosition(), pos);
	}

	bool Circle::isColliding(GF::Circle& other) const
	{
		return pow((getPosition().x - other.getPosition().x),
		           2) + pow((getPosition().y - other.getPosition().y), 2)
		       <= (getRadius() + other.getRadius()) * (getRadius() + other.getRadius());
	}

	bool Circle::isRolledOn(const sf::RenderWindow& window, float threshold) const
	{
		auto pos = GF::Mouse::getPosition(window);
		return contains(pos, threshold);
	}

	bool Circle::isClicked(const GF::Event& event, float threshold) const
	{
		return GF::Mouse::Left.clicked(event)
		       && (contains(sf::Vector2f(event.mouseButton.x,
		                                 event.mouseButton.y), threshold));

	}

	Line::Line(sf::Vector2f pos1, sf::Vector2f pos2, sf::Color color1,
	           sf::Color color2) : line(sf::Lines, 2)
	{
		line[0].position = pos1;
		line[0].color = color1;
		line[1].position = pos2;
		line[1].color = color2;
	}

	float Line::angleBetween(GF::Line& snd)
	{
		float m1 = (line[0].position.y - line[1].position.y) / (line[0].position.x -
		           line[1].position.x);
		float m2 = (snd.line[0].position.y - snd.line[1].position.y) / (snd.line[0].position.x -
		           snd.line[1].position.x);
		return abs(toDegrees(atan((m2 - m1) / (1 - m1 * m2))));
	}

	void Line::move(const sf::Vector2f vec)
	{
		line[0].position += vec;
		line[1].position += vec;
	}

	void Line::draw(sf::RenderTarget& renderer, sf::RenderStates state) const
	{
		renderer.draw(line);
	}
}