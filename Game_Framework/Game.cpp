#include "Game_Framework/main.h"
#include "Game_Framework/GUI.h"
#include "Game_Framework/sfml.h"
#include "Game_Framework/holders.h"

namespace GF
{
	Game::Game() : fps(&window), should_exit(false), static_screen(false)
	{
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
		fps.setMaxFPS(frames); 
	}

	void Game::setupWindow(unsigned sizex, unsigned sizey, unsigned x, unsigned y, int style)
	{
		SCREENWIDTH = sizex;
		SCREENHEIGHT = sizey;

		if ((window.getSize() != sf::Vector2u(sizex, sizey))
		    && (window.getPosition() != sf::Vector2i(x, y))) {

			if (window.isOpen()) window.close();

			window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), title, style);
			window.setPosition(sf::Vector2i(x, y));
		}
	}

	void Game::setupWindow(sf::Vector2u size, unsigned x, unsigned y, int style)
	{
		setupWindow(size.x, size.y, x, y, style);
	}

	void Game::setupWindow(unsigned sizex, unsigned sizey, sf::Vector2i position, int style)
	{
		setupWindow(sizex, sizey, position.x, position.y, style);
	}

	void Game::setupWindow(sf::Vector2u size, sf::Vector2i position, int style)
	{
		setupWindow(size.x, size.y, position.x, position.y, style);
	}

	void Game::run()
	{
		begin.restart();
		should_exit = false;

		if (!window.isOpen())
			setupWindow(CENTER_SCREEN.x, CENTER_SCREEN.y, CENTER_SCREEN.x / 2, CENTER_SCREEN.y / 2,
			            sf::Style::Default);

		// fps.setMaxFPS(max_fps);


		// initializes the game. 'onCreate' gets called automatically when a new state is added. Exits if any error occured
		if (!states.onCreate())
			return;

		static GF::Event event;

		//////////// MAIN LOOP /////////////
		while (window.isOpen()) {
			if (!static_screen) window.clear(clear_color);

			if (!should_exit) pollEvents(event); // polls the event from the event queue

			if (!should_exit) handleEvent(event); // handles the event

			if (!should_exit) update(); // clears the window, updates and draws the entities

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
		static GF::ToggleKey ESC(sf::Keyboard::Escape);
		
		// handle game events
		if (!states.onHandleEvent(event)) {
			should_exit = true;
			return;
		}

		for (auto& widget : widget_names) {
			if (!widgets[widget]->handleEvent(event)) {
				should_exit = true;
				return;
			}
		}

		// closing window events - X button on window or esc on keyboard
		if (event.type == GF::Event::Closed || ESC.isKeyPressed()) {
			should_exit = true;
			return;
		}
	}

	void Game::update()
	{
		float fElapsedTime = fps.getElapsedTime(); // time between frames
		float fTotalTime = begin.getElapsedTime().asSeconds(); // time since start

		for (auto& widget : widget_names) {

			if (!widgets[widget]->update(fElapsedTime, fTotalTime) ||
			    !widgets[widget]->draw()) {
				should_exit = true;
				return;
			}
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//TODO: change to ERROR and change return of 'update' and 'draw' from 'bool' to 'GAME_STATE'
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		// updates and draws entities of the game
		if (!states.onUpdate(fElapsedTime, fTotalTime) || !states.onDraw()) {
			should_exit = true;
			return;
		}

		fps.draw();
	}

	void Game::exitApp()
	{
		should_exit = true;
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
		else {
			std::cout << name << " not found." << std::endl;
			return nullptr;
		}
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
