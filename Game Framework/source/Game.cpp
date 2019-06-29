#include "../main.h"
#include "../GUI.h"
#include "../sfml.h"
#include "../holders.h"

namespace GF {

	void Game::showFPS(bool show) {
		showfps = show;
	}


	void Game::setMaxFPS(int frames) {
		//fps.setMaxFPS(frames); // both work
		window.setFramerateLimit(frames); // but this one works better D;
	}

	void Game::run() {

		// initializes the game. Exits if any error occured
		if (should_exit = !onCreate()) return;

		static GF::Event event;

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

	GF::Event::EventType Game::pollEvent(GF::Event & event) {
		static sf::Event v;

		// if no event was triggered return GF::Event::NoEvent
		if (!window.pollEvent(v)) { // window.pollEvent does not change the event type if there is no event on the event buffer, so i change it by hand
			v.type = sf::Event::TouchBegan; event.type = GF::Event::NoEvent;
			return event.type;
		}

		// if any addicional events are detected, the event.type is overridden.

		// for mouse double click event to be triggered, the mouse must be clicked twice in a small period of time ( about 250 ms between clicks)
		if (GF::Mouse::Left.doubleClicked(v))
			event.type = GF::Event::LeftMouseDoubleClickedEvent;
		else if (GF::Mouse::Right.doubleClicked(v))
			event.type = GF::Event::RightMouseDoubleClickedEvent;
		// cliked once means the event is only triggered when the mouse button is released
		else if (GF::Mouse::Left.clickedOnce(v))
			event.type = GF::Event::LeftMouseClickedOnceEvent;
		else if (GF::Mouse::Right.clickedOnce(v))
			event.type = GF::Event::RightMouseClickedOnceEvent;
		else event = GF::Event(v);

		return event.type;
	}

	void Game::handleEvent(GF::Event & event) {
		// closing window events - X button on window or esc on keyboard
		if (event.type == GF::Event::Closed || (event.type == GF::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			should_exit = true;

		// show fps event - F key
		if ((event.type == GF::Event::KeyReleased && event.key.code == sf::Keyboard::F))
			showfps = !showfps;

		// handle game events
		should_exit = !onHandleEvent(event);
	}

	void Game::update() {
		window.clear();

		// shows fps count, if fps is activated
		if (!showfps) fps.update(); // keeps counting fps event it is not being displayed (in case a max fps is set)
		else fps.draw(window, sf::RenderStates::Default); // draw() already calls update()

		float fElapsedTime = fps.getElapsedTime();

		// updates and draws entities of the game
		should_exit = !onUpdate(fElapsedTime) || !onDraw(window, sf::RenderStates::Default);
	}
}
