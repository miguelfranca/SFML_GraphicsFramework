#pragma once
#include "holders.h"
#include "FPSCounter.h"
#include "StateMachine.h"
#include "sfml/Event.h"
#include <SFML/Window.hpp>

namespace GF
{

	class Game : public NonCopyable, public NonMovable, protected State
	{
	public:

		Game();
		~Game();

		void setMaxFPS(int frames = 60);
		void showFPS(bool);
		void run();
		void exitApp();

	protected:
		std::string title = "Window";
		sf::RenderWindow window;
		GF::StateMachine states;

	protected:

		void addWidget(GF::Widget* widget, std::string name = "");
		void clearWidgets();
		inline void deleteWidget(const std::string name);
		GF::Widget* getWidget(const std::string name);

		void setClearColor(const sf::Color);

		inline float getFPS() const { return fps.getFPS(); }
		inline float getMaxFPS() const { return fps.getMaxFPS(); }
		inline void setStaticScreen(const bool& s) { static_screen = s; }

		void setupWindow(unsigned sizex, unsigned sizey, unsigned x = 0, unsigned y = 0, int style = 0);
		void setupWindow(sf::Vector2u size, unsigned x = 0, unsigned y = 0, int style = 0);
		void setupWindow(unsigned sizex, unsigned sizey, sf::Vector2i position = TOPLEFT_I, int style = 0);
		void setupWindow(sf::Vector2u size, sf::Vector2i position, int style = 0);

	private:
		GF::Event::EventType pollEvents(GF::Event& event);
		void handleEvent(GF::Event& event);
		void update();

	private:
		GF::FPSCounter fps;
		int max_fps;
		sf::Clock begin;

		sf::Color clear_color;

		bool should_exit;

		bool static_screen;

		std::map<std::string, GF::Widget*> widgets;
		std::vector<std::string> widget_names;
	};
}
