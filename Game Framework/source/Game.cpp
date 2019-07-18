#include "../main.h"
#include "../GUI.h"
#include "../sfml.h"
#include "../holders.h"

namespace GF {

	void Game::showFPS(bool show) {
		showfps = show;
	}


	void Game::setMaxFPS(int frames) {
		fps.setMaxFPS(frames); // both work
		//window.setFramerateLimit(frames); // but this one only works sometimes? TODO
	}

	void Game::run() {

		// initializes the game. Exits if any error occured
		if (should_exit = !onCreate()) return;

		static sf::Event event;

		window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), title);
		window.setPosition(CENTER_SCREEN);

		//////////// MAIN LOOP /////////////
		while (window.isOpen())
		{
			pollEvent(event); // polls the event from the event queue

			handleEvent(event); // handles the event

			update(); // clears the window and draws the entities
			window.display(); // displays everything into the window
							  
			// exits game if necessary
			if (should_exit)
				break;
		}
		window.close();
	}

	sf::Event::EventType Game::pollEvent(sf::Event & event) {
		// if no event was triggered return sf::Event::NoEvent. window.pollEvent returns false if no event was detected
		if (!window.pollEvent(event)) // window.pollEvent does not change the event type if there is no event on the event buffer, so we change it by hand
			event.type = sf::Event::Count; // unused event. Not best solution...
		return event.type;
	}

	void Game::handleEvent(sf::Event & event) {
		// handle game events
		if (!onHandleEvent(event)) should_exit = true;

		// closing window events - X button on window or esc on keyboard
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			should_exit = true;

		// show fps event - F key
		if ((event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F))
			showfps = !showfps;
	}

	void Game::update() {
		window.clear();

		float fElapsedTime = fps.getElapsedTime(); // time between frames

		// updates and draws entities of the game
		if(!onUpdate(fElapsedTime) || !onDraw(window, sf::RenderStates::Default)) 
			should_exit = true;
		
		// shows fps count, if fps is activated
		if (!showfps) fps.update(); // keeps counting fps event it is not being displayed (in case a max fps is set)
		else fps.draw(window, sf::RenderStates::Default); // draw() already calls update()
	}
}
