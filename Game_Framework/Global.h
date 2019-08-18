#pragma once

#include <SFML/Graphics.hpp>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
#define MIN_PI 3.14f;

#define For0(b) for(unsigned i = 0; i < b; ++i)
#define For1(b, c) for(unsigned b = 0; b < c; ++b)
#define ForFor(b, c) for(unsigned i = 0; i < b; ++i) for(unsigned j = 0; j < c; ++j)
#define ForFor2(i, b, j, c) for(unsigned i = 0; i < b; ++i) for(unsigned j = 0; j < c; ++j)
#define For2(i, b) for(unsigned i = 0; i < b; ++i)
#define For3(i, a, b) for(int i = a; i < b; ++i)
#define For4(i, a, b, c) for(int i = a; i < b; i += c)

// window
const float SW = sf::VideoMode::getDesktopMode().width / 1920.f; // scale width
const float SH = sf::VideoMode::getDesktopMode().height / 1080.f; // scale height
const unsigned SCREENWIDTH = (int)(1280.f * SW);
const unsigned SCREENHEIGHT = (int)(720.f * SH);

// text
#define DEFAULT_CHAR_SIZE 30
#define DEFAULT_FONT "res/fonts/Arial.ttf"
#define DEFAULT_CHAR_COLOR sf::Color::White

#define CENTER sf::Vector2f(getSize().x / 2.f, getSize().y / 2.f)

// positions and directions
#define TOPLEFT_I sf::Vector2i(0, 0)
#define TOPLEFT_F sf::Vector2f(0.f, 0.f)
#define CENTER_WINDOW sf::Vector2f((float)SCREENWIDTH / 2, (float)SCREENHEIGHT / 2)
const sf::Vector2i CENTER_SCREEN = sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - SCREENWIDTH / 2, sf::VideoMode::getDesktopMode().height / 2 - SCREENHEIGHT / 2);

#define SFML_VERSION_GT(MAJOR,MINOR,PATCH) (SFML_VERSION_MAJOR>=MAJOR && SFML_VERSION_MINOR>=MINOR && SFML_VERSION_PATCH>=PATCH)

// colors
#define GRAY sf::Color(128, 128, 128)
