#include "Global.h"

float SW = sf::VideoMode::getDesktopMode().width / 1920.f; // scale width
float SH = sf::VideoMode::getDesktopMode().height / 1080.f; // scale height

// float SW = sf::VideoMode::getFullscreenModes()[0].width / 1920.f / sf::VideoMode::getFullscreenModes().size();
// float SH = sf::VideoMode::getFullscreenModes()[0].height / 1080.f / sf::VideoMode::getFullscreenModes().size();

unsigned SCREENWIDTH = (int)(1260.f * SW);
unsigned SCREENHEIGHT = (int)(720.f * SH);