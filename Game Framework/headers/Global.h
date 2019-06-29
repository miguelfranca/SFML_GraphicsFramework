#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.14159265358979f
#define MIN_PI 3.14f;

#define For(b) for(int i = 0; i < b; ++i)
#define For2(i, b) for(int i = 0; i < b; ++i)
#define For3(i, a, b) for(int i = a; i < b; ++i)
#define For4(i, a, b, c) for(int i = a; abs(i) < abs(b); i += c)

// window
const float SW = sf::VideoMode::getDesktopMode().width / 1920.f; // scale width
const float SH = sf::VideoMode::getDesktopMode().height / 1080.f; // scale height
const unsigned SCREENWIDTH = (int)(1280.f * SW);
const unsigned SCREENHEIGHT = (int)(720.f * SH);

// text
#define DEFAULT_CHAR_SIZE 40
#define DEFAULT_CHAR_COLOR sf::Color::White

#define CENTER sf::Vector2f(getSize().x / 2.f, getSize().y / 2.f)

// positions and directions
#define HORIZONTAL "HORIZONTAL"
#define VERTICAL "VERTICAL"
#define TOPLEFT "TOPLEFT"
#define MIDDLELEFT "TOPLEFT"
#define CENTERED "CENTERED"
#define TOPLEFT_I sf::Vector2i(0, 0)
#define TOPLEFT_F sf::Vector2f(0.f, 0.f)
#define CENTER_WINDOW sf::Vector2f((float)SCREENWIDTH / 2, (float)SCREENHEIGHT / 2)
const sf::Vector2i CENTER_SCREEN = sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - SCREENWIDTH / 2, sf::VideoMode::getDesktopMode().height / 2 - SCREENHEIGHT / 2);
