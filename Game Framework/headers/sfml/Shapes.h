#pragma once
#include <SFML/Graphics.hpp>
#include "../Global.h"
#include "Event.h"

namespace GF {
	class Rectangle : public sf::RectangleShape {
	public:
		Rectangle(){}
		Rectangle(sf::Vector2f size, sf::Vector2f pos = TOPLEFT_F, sf::Color fill = sf::Color::White, sf::Color outline = sf::Color::Transparent, float thickness = 0);
		Rectangle(sf::Vector2f size, sf::Vector2f pos = TOPLEFT_F, std::string origin = CENTERED, sf::Color fill = sf::Color::White, sf::Color outline = sf::Color::Transparent, float thickness = 0);
		bool isRolledOn(const sf::RenderWindow& window) const;
		bool isClicked(const GF::Event& event, const sf::RenderWindow& window);
		void setup(sf::Vector2f size, sf::Vector2f pos, sf::Vector2f origin, sf::Color fill, sf::Color outline, float thickness);
	private:
	};


	class Circle : public sf::CircleShape {
	public:
		Circle(){}
		Circle(float radius, sf::Vector2f pos = TOPLEFT_F, sf::Color fill = sf::Color::White, sf::Color outline = sf::Color::Transparent, float thickness = 0);
		bool isColliding(GF::Circle& other);
		bool isRolledOn(const sf::RenderWindow& window, float threshold = 0.f) const;
		bool isClicked(const GF::Event& event, const sf::RenderWindow& window, float threshold);
		void setup(float radius, sf::Vector2f pos, sf::Color fill, sf::Color outline, float thickness);
	private:
	};

	class Line : public sf::VertexArray{
	public:
		Line(sf::Vector2f pos1 = sf::Vector2f(0, 0), sf::Vector2f pos2 = sf::Vector2f(0, 0));

		void draw(sf::RenderTarget& renderer, sf::RenderStates state) const;
	private:
		sf::VertexArray line;
	};
}