#pragma once

#include <SFML/Graphics.hpp>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
#define MIN_PI 3.14f;

// window
extern float SW; // scale width
extern float SH; // scale height

extern unsigned SCREENWIDTH;
extern unsigned SCREENHEIGHT;

// text
#define DEFAULT_CHAR_SIZE 20 * SW
#define DEFAULT_FONT "res/fonts/Arial.ttf"
#define DEFAULT_CHAR_COLOR sf::Color::White

#define CENTER sf::Vector2f(getSize().x / 2.f, getSize().y / 2.f)

// positions and directions
#define TOPLEFT_I sf::Vector2i(0, 0)
#define TOPLEFT_F sf::Vector2f(0.f, 0.f)
#define CENTER_WINDOW sf::Vector2f((float)SCREENWIDTH / 2, (float)SCREENHEIGHT / 2)
const sf::Vector2i CENTER_SCREEN = sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - SCREENWIDTH / 2, sf::VideoMode::getDesktopMode().height / 2 - SCREENHEIGHT / 2);
#define SCALE_2F sf::Vector2f(SW, SH)

#define SFML_VERSION_GT(MAJOR,MINOR,PATCH) (SFML_VERSION_MAJOR>=MAJOR && SFML_VERSION_MINOR>=MINOR && SFML_VERSION_PATCH>=PATCH)

// colors
#define BLACK 	sf::Color(0,0,0)
#define WHITE 	sf::Color(255,255,255)
#define RED		sf::Color(255,0,0)
#define LIME 	sf::Color(0,255,0)
#define BLUE 	sf::Color(0,0,255)
#define YELLOW 	sf::Color(255,255,0)
#define CYAN 	sf::Color(0,255,255)
#define MAGENTA sf::Color(255,0,255)
#define SILVER 	sf::Color(192,192,192)
#define GRAY 	sf::Color(128,128,128)
#define MAROON 	sf::Color(128,0,0)
#define OLIVE 	sf::Color(128,128,0)
#define GREEN 	sf::Color(0,128,0)
#define PURPLE 	sf::Color(128,0,128)
#define TEAL 	sf::Color(0,128,128)
#define NAVY 	sf::Color(0,0,128)
