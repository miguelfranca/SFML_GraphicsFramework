#include "VectorOp.h"

float dist(sf::Vector2f pos1, sf::Vector2f pos2) {
	return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +
		(pos1.y - pos2.y) * (pos1.y - pos2.y));
}
std::ostream& operator<<(std::ostream& os, const sf::Vector2f& pos)
{
	// write obj to stream
	os << "(" << pos.x << ", " << pos.y << ")";
	return os;
}