#pragma once
#include <SFML/Graphics.hpp>

static sf::Vector2f& operator+(sf::Vector2f & vec, sf::Vector2f add)
{
	vec.x += add.x;
	vec.y += add.y;
	return vec;
}
static sf::Vector2f& operator-(sf::Vector2f& vec, sf::Vector2f sub)
{
	vec.x -= sub.x;
	vec.y -= sub.y;
	return vec;
}
static sf::Vector2f& operator+(sf::Vector2f& vec, float add)
{
	vec.x += add;
	vec.y += add;
	return vec;
}
static sf::Vector2f& operator-(sf::Vector2f& vec, float sub)
{
	vec.x -= sub;
	vec.y -= sub;
	return vec;
}
static sf::Vector2f& operator*(sf::Vector2f& vec, float mult)
{
	vec.x *= mult;
	vec.y *= mult;
	return vec;
}
static sf::Vector2f& operator/(sf::Vector2f& vec, float div)
{
	vec.x /= div;
	vec.y /= div;
	return vec;
}
static float dist(sf::Vector2f pos1, sf::Vector2f pos2) {
	return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +
		(pos1.y - pos2.y) * (pos1.y - pos2.y));
}