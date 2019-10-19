#include "Game_Framework/main.h"
#include "Game_Framework/GUI.h"
#include "Game_Framework/sfml.h"
#include "Game_Framework/holders.h"

namespace GF
{
	Game::Game() : fps(&window), max_fps(-1), should_exit(false)
	{
#ifdef TGUI_TGUI_HPP
		gui.setTarget(window);
#endif
		states.add("home", this);
	}

	Game::~Game()
	{
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
		//fps.setMaxFPS(max_fps); // cannot set this before sfml window is created
	}

	void Game::run()
	{
		begin.restart();
		should_exit = false;

		if (!window.isOpen()) {
			window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), title);
			window.setPosition(CENTER_SCREEN);
		}

		fps.setMaxFPS(max_fps);

#ifdef TGUI_TGUI_HPP
		gui.setView(window.getView());
#endif

		// initializes the game. 'onCreate' gets called automatically when a new state is added. Exits if any error occured
		if (!states.onCreate())
			return;

		static GF::Event event;

		//////////// MAIN LOOP /////////////
		while (window.isOpen()) {
			pollEvents(event); // polls the event from the event queue

			handleEvent(event); // handles the event

			update(); // clears the window, updates and draws the entities

			window.display(); // displays everything into the window

			// exits game if necessary
			if (should_exit)
				break;
		}

		states.onDestroy();
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
		if (!states.onHandleEvent(event))
			should_exit = true;

		for (auto& widget : widget_names) {
			if (!widgets[widget]->handleEvent(event))
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

		for (unsigned i = 0; i < eventListeners.size(); ++i) {
			if (event.type == std::get<0>(eventListeners[i]))
				std::get<1>(eventListeners[i])(std::get<2>(eventListeners[i]));
		}
	}

	void Game::update()
	{
		window.clear(clear_color);

		float fElapsedTime = fps.getElapsedTime(); // time between frames
		float fTotalTime = begin.getElapsedTime().asSeconds(); // time since start

#ifdef TGUI_TGUI_HPP

		if (gui.getWidgets().size() != 0)
			gui.draw();

#endif

		for (auto& widget : widget_names) {

			if (!widgets[widget]->update(fElapsedTime, fTotalTime) ||
			    !widgets[widget]->draw())
				should_exit = true;
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//TODO: change to ERROR and change return of 'update' and 'draw' from 'bool' to 'GAME_STATE'
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		// updates and draws entities of the game
		if (!states.onUpdate(fElapsedTime, fTotalTime) || !states.onDraw())
			should_exit = true;

		fps.draw();
	}

	void Game::addWidget(GF::Widget* widget, std::string name)
	{
		if (name == "")
			name = widgets.size();

		widgets.insert(std::pair<std::string, GF::Widget*>(name, widget));
		widget_names.push_back(name);
	}

	void Game::deleteWidget(const std::string name)
	{
		if (widgets.find(name) != widgets.end()) {
			delete widgets[name];
			widgets.erase(name);

			auto it = std::find_if(widget_names.begin(), widget_names.end(),
			[&name](std::string element) { return element == name;});
			widget_names.erase(it);
		}
	}

	void Game::clearWidgets()
	{
		for (auto& widget : widgets)
			delete widget.second;

		widgets.clear();
		widget_names.clear();
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
