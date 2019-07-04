#include "../../headers/sfml/Shapes.h"
#include "../../headers/sfml/Mouse.h"
#include "../../headers/sfml/VectorOp.h"

namespace GF {
	
	Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, sf::Color fill, sf::Color outline, float thickness) {
		setup(size, pos, { 0, 0 }, fill, outline, thickness);
	}
	Rectangle::Rectangle(sf::Vector2f size, sf::Vector2f pos, std::string origin, sf::Color fill, sf::Color outline, float thickness) {
		if(origin == CENTERED)
			setup(size, pos, sf::Vector2f(size.x / 2, size.y / 2), fill, outline, thickness);
		if (origin == TOPLEFT)
			setup(size, pos, { 0, 0 }, fill, outline, thickness);
	}

	void Rectangle::setup(sf::Vector2f size, sf::Vector2f pos, sf::Vector2f origin, sf::Color fill, sf::Color outline, float thickness) {
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

	bool Rectangle::Rectangle::isClicked(const GF::Event& event, const sf::RenderWindow& window)
	{
		if (isRolledOn(window)) {
			if (event.type == GF::Event::LeftMouseClickedOnceEvent) {
				return true;
			}
		}
		return false;
	}

	Circle::Circle(float radius, sf::Vector2f pos, sf::Color fill, sf::Color outline, float thickness){
		setup(radius, pos, fill, outline, thickness);
	}

	void Circle::setup(float radius, sf::Vector2f pos, sf::Color fill, sf::Color outline, float thickness){
		setRadius(radius);
		setOrigin(radius, radius);
		setPosition(pos);
		setFillColor(fill);
		setOutlineColor(outline);
		setOutlineThickness(thickness);
	}

	bool Circle::isColliding(GF::Circle& other) {
		return pow((getPosition().x - other.getPosition().x), 2) + pow((getPosition().y - other.getPosition().y), 2)
				<= (getRadius() + other.getRadius())* (getRadius() + other.getRadius());
	}

	bool Circle::isRolledOn(const sf::RenderWindow& window, float threshold) const
	{
		auto pos = GF::Mouse::getPosition(window);
		return (getRadius() + threshold)*(getRadius() + threshold) >= dist(getPosition(), pos) * dist(getPosition(), pos);
	}

	bool Circle::isClicked(const GF::Event& event, const sf::RenderWindow& window, float threshold)
	{
		if (isRolledOn(window, threshold)) {
			if (GF::Mouse::Left.clicked(event)) {
				return true;
			}
		}
		return false;
	}

	Line::Line(sf::Vector2f pos1, sf::Vector2f pos2) : line(sf::Lines, 2) {
		line[0].position = pos1;
		line[1].position = pos2;
	}

	void Line::draw(sf::RenderTarget& renderer, sf::RenderStates state) const {
		renderer.draw(line);
	}
}