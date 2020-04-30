#pragma once
#include <SFML/Graphics.hpp>
#include "Event.h"
#include "../Global.h"
#include "Orientation.h"

namespace GF
{
	class Rectangle : public sf::RectangleShape
	{
	public:
		Rectangle() {}
		Rectangle(sf::Vector2f size, sf::Vector2f pos = TOPLEFT_F, sf::Color fill = sf::Color::White,
		          sf::Color outline = sf::Color::Transparent, float thickness = 0);
		Rectangle(sf::Vector2f size, sf::Vector2f pos = TOPLEFT_F, GF::Alignment origin = GF::CENTERED,
		          sf::Color fill = sf::Color::White, sf::Color outline = sf::Color::Transparent, float thickness = 0);
		Rectangle(sf::FloatRect rect);
		bool isRolledOn(const sf::RenderWindow& window) const;
		bool isClicked(const GF::Event& event, const sf::RenderWindow& window);
		void setup(sf::Vector2f size, sf::Vector2f pos, sf::Vector2f origin, sf::Color fill,
		           sf::Color outline, float thickness);
	private:
	};


	class Circle : public sf::CircleShape
	{
	public:
		Circle() {}
		Circle(float radius, sf::Vector2f pos = TOPLEFT_F, sf::Color fill = sf::Color::White,
		       sf::Color outline = sf::Color::Transparent, float thickness = 1);
		bool isColliding(GF::Circle& other);
		bool contains(sf::Vector2f, float threshold = 0.);
		bool isRolledOn(const sf::RenderWindow& window, float threshold = 0.f) const;
		bool isClicked(const GF::Event& event, const sf::RenderWindow& window, float threshold = 0.f);
		void setup(float radius, sf::Vector2f pos, sf::Color fill, sf::Color outline, float thickness);
	private:
	};

	class Line : public sf::Drawable
	{
	public:
		Line(sf::Vector2f pos1 = sf::Vector2f(0, 0), sf::Vector2f pos2 = sf::Vector2f(0, 0),
		     sf::Color color1 = sf::Color::White, sf::Color color2 = sf::Color::White);

		void draw(sf::RenderTarget& renderer, sf::RenderStates state) const;

		float angleBetween(GF::Line& line);

		void move(const sf::Vector2f);

		sf::VertexArray line;
		GF::Rectangle rect;
	};
}