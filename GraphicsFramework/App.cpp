#include "GraphicsFramework/main.h"
#include "GraphicsFramework/GUI.h"
#include "GraphicsFramework/sfml.h"
#include "GraphicsFramework/holders.h"

namespace GF
{
	App::App() : fps(&window), should_exit(false), static_screen(false)
	{
		states.add("home", this);
	}

	App::~App()
	{
		if (window.isOpen())
			window.close();

		clear_color = sf::Color::Black;
	}

	void App::showFPS(bool show)
	{
		fps.show(show);
	}


	void App::setMaxFPS(int frames)
	{
		fps.setMaxFPS(frames);
	}

	void App::setupWindow(const unsigned sizex, const unsigned sizey, const unsigned x,
	                      const unsigned y, const int style)
	{
		SCREENWIDTH = sizex;
		SCREENHEIGHT = sizey;

		if ((window.getSize() != sf::Vector2u(sizex, sizey))
		    || (window.getPosition() != sf::Vector2i(x, y))) {

			if (window.isOpen()) window.close();

			window.create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), title, style);
			window.setPosition(sf::Vector2i(x, y));
		}
	}

	void App::setupWindow(const sf::Vector2u size, const unsigned x, const unsigned y, const int style)
	{
		setupWindow(size.x, size.y, x, y, style);
	}

	void App::setupWindow(const unsigned sizex, const unsigned sizey, const sf::Vector2i position,
	                      const int style)
	{
		setupWindow(sizex, sizey, position.x, position.y, style);
	}

	void App::setupWindow(const sf::Vector2u size, const sf::Vector2i position, const int style)
	{
		setupWindow(size.x, size.y, position.x, position.y, style);
	}

	void App::run()
	{
		begin.restart();
		should_exit = false;

		// creates a new window if it hasnt been created yet
		// setupWindow(sizeX, sizeY, posX, posY, style)
		if (!window.isOpen())
			setupWindow(CENTER_SCREEN.x, CENTER_SCREEN.y, CENTER_SCREEN.x / 2, CENTER_SCREEN.y / 2,
			            sf::Style::Default);

		// initializes the app. 'onCreate' gets called automatically when a new state is added. Exits if any error occured
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

			// exits app if necessary
			if (should_exit)
				break;
		}

		states.onDestroy();
		// clearWidgets();
	}

	GF::Event::EventType App::pollEvents(GF::Event& event)
	{
		// window.pollEvent returns false if no event was detected
		if (!window.pollEvent(
		        event)) // window.pollEvent does not change the event type if there is no event on the event buffer and returns false, so we change it by hand
			event.type = GF::Event::Count; // unused event. Not the best solution...

		return event.type;
	}

	void App::handleEvent(GF::Event& event)
	{
		static GF::ToggleKey ESC(sf::Keyboard::Escape);

		// handle app events
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

	void App::update()
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

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//TODO: change to ERROR enum and change return of 'update' and 'draw' from 'bool' to 'GAME_STATE'!
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		// updates and draws entities of the app
		if (!states.onUpdate(fElapsedTime, fTotalTime) || !states.onDraw()) {
			should_exit = true;
			return;
		}

		fps.draw();
	}

	void App::exitApp()
	{
		should_exit = true;
	}

	void App::setClearColor(const sf::Color color)
	{
		clear_color = color;

		if (clear_color == sf::Color::White)
			fps.setFillColor(sf::Color::Black);

		if (clear_color == sf::Color::Black)
			fps.setFillColor(sf::Color::White);
	}

	void App::addWidget(GF::Widget* widget, std::string name)
	{
		if (name == "")
			name = widgets.size();

		widgets.insert(std::pair<std::string, GF::Widget*>(name, widget));
		widget_names.push_back(name);
	}

	void App::deleteWidget(const std::string name)
	{
		if (widgets.find(name) != widgets.end()) {
			delete widgets[name];
			widgets.erase(name);

			auto it = std::find_if(widget_names.begin(), widget_names.end(),
			[&name](std::string element) { return element == name;});
			widget_names.erase(it);
		}
	}

	void App::clearWidgets()
	{
		for (auto& widget : widgets)
			delete widget.second;

		widgets.clear();
		widget_names.clear();
	}

	GF::Widget* App::getWidget(const std::string name)
	{
		if (widgets.find(name) != widgets.end()) {
			return widgets[name];
		}
		else {
			std::cout << name << " not found." << std::endl;
			return nullptr;
		}
	}
}
