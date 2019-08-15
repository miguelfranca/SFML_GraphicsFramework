#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

float dist(sf::Vector2f pos1, sf::Vector2f pos2);
std::ostream& operator<<(std::ostream& os, const sf::Vector2f& pos);