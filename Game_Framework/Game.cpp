#include "Game_Framework/main.h"
#include "Game_Framework/GUI.h"
#include "Game_Framework/sfml.h"
#include "Game_Framework/holders.h"

namespace GF
{

	Game::~Game()
	{
		clearWidgets();

		if (window.isOpen())
			window.close();

		clear_color = sf::Color::Black;
	}

	void Game::showFPS(bool show)
	{
		fps.show(show);
	}


	void Game::setMaxFPS(int frames)
	{
		max_fps = frames;
		//window.setFramerateLimit(frames); // cannot set this before window is created
	}

	void Game::run()
	{
		begin.restart();
		should_exit = false;

		if (!window.isOpen()) {
			window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), title);
			window.setPosition(CENTER_SCREEN);
		}

		fps.setMaxFPS(max_fps); // both work

#ifdef TGUI_TGUI_HPP
		gui.setView(window.getView());
#endif


		// initializes the game. Exits if any error occured
		// if (!onCreate())
		// 	return;
		if (!sm.onCreate())
			return;

		static GF::Event event;

		//////////// MAIN LOOP /////////////
		while (window.isOpen()) {
			pollEvents(event); // polls the event from the event queue

			handleEvent(event); // handles the event

			update(); // clears the window and draws the entities

			window.display(); // displays everything into the window

			// exits game if necessary
			if (should_exit)
				break;
		}

		sm.onDestroy();
		clearWidgets();
	}

	GF::Event::EventType Game::pollEvents(GF::Event& event)
	{
		// window.pollEvent returns false if no event was detected
		if (!window.pollEvent(
		        event)) // window.pollEvent does not change the event type if there is no event on the event buffer, so we change it by hand
			event.type = GF::Event::Count; // unused event. Not best solution...

		return event.type;
	}

	void Game::handleEvent(GF::Event& event)
	{
		// handle game events
		if (!sm.onHandleEvent(event))
			should_exit = true;

		for (auto w : widget_names) {
			GF::Widget* widget = widgets[w];

			if (!widget->handleEvent(event))
				should_exit = true;
		}

#ifdef TGUI_TGUI_HPP

		if (gui.getWidgets().size() != 0)
			gui.handleEvent(event);

#endif

		// closing window events - X button on window or esc on keyboard
		if (event.type == GF::Event::Closed || (event.type == GF::Event::KeyPressed
		                                        && event.key.code == sf::Keyboard::Escape))
			should_exit = true;

		fps.handleEvent(event);
	}

	void Game::update()
	{
		window.clear(clear_color);

		float fElapsedTime = fps.getElapsedTime(); // time between frames
		float fTotalTime = begin.getElapsedTime().asSeconds(); // time between frames

#ifdef TGUI_TGUI_HPP

		if (gui.getWidgets().size() != 0)
			gui.draw();

#endif

		for (auto w : widget_names) {
			GF::Widget* widget = widgets[w];

			if (!widget->update(fElapsedTime, fTotalTime) ||
			    !widget->draw())
				should_exit = true;
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//TODO: change to ERROR and change return of 'update' and 'draw' from 'bool' to 'GAME_STATE'
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		// updates and draws entities of the game
		if (!sm.onUpdate(fElapsedTime, fTotalTime) || !sm.onDraw())
			should_exit = true;

		fps.draw();
	}

	void Game::addWidget(GF::Widget* widget, std::string name)
	{
		if (name == "")
			name = widgets.size();

		widget_names.push_back(name);
		widgets.insert(std::pair<std::string, GF::Widget*>(name, widget));
	}

	void Game::deleteWidget(const std::string name)
	{

		auto end = std::remove_if(widget_names.begin(), widget_names.end(),
		[name](std::string const & n) {
			return n == name; // removes if mouse position is inside circle boundaries
		});

		widget_names.erase(end, widget_names.end());

		if (widgets.find(name) != widgets.end()) {
			delete widgets[name];
			widgets.erase(name);
		}
	}

	void Game::clearWidgets()
	{
		widget_names.clear();

		for (auto& widget : widgets)
			delete widget.second;

		widgets.clear();
	}

	GF::Widget* Game::getWidget(const std::string name)
	{
		if (widgets.find(name) != widgets.end()) {
			return widgets[name];
		}
		else
			return nullptr;
	}

	void Game::setClearColor(const sf::Color color)
	{
		clear_color = color;

		if (clear_color == sf::Color::White)
			fps.setFillColor(sf::Color::Black);

		if (clear_color == sf::Color::Black)
			fps.setFillColor(sf::Color::White);
	}
}
