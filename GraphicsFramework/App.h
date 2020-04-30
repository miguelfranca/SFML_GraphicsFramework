#pragma once
#include <SFML/Window.hpp>

#include "holders.h"
#include "FPSCounter.h"
#include "StateMachine.h"
#include "sfml/Event.h"

namespace GF
{

	class App : public NonCopyable, public NonMovable, protected State
	{
	public:

		App();
		~App();

		void setMaxFPS(int frames = 60);
		void showFPS(bool);
		void run();
		void exitApp();

	protected:
		std::string title = "Window";
		sf::RenderWindow window;
		GF::StateMachine states;

	protected:

		// void addWidget(GF::Widget* widget, std::string name = "");
		// void clearWidgets();
		// inline void deleteWidget(const std::string name);
		// GF::Widget* getWidget(const std::string name);

		void setClearColor(const sf::Color);

		inline float getFPS() const { return fps.getFPS(); }
		inline float getMaxFPS() const { return fps.getMaxFPS(); }
		inline void setStaticScreen(const bool& s) { static_screen = s; }

		void setupWindow(const unsigned sizex, const unsigned sizey, const unsigned x, const unsigned y, const int style = sf::Style::Default);
		void setupWindow(const sf::Vector2u size, const  unsigned x, const unsigned y, const int style = sf::Style::Default);
		void setupWindow(const  unsigned sizex, const  unsigned sizey, const sf::Vector2i position = TOPLEFT_I, const int style = sf::Style::Default);
		void setupWindow(const sf::Vector2u size, const sf::Vector2i position = TOPLEFT_I, const int style = sf::Style::Default);

	private:
		GF::Event::EventType pollEvents(GF::Event& event);
		void handleEvent(GF::Event& event);
		void update();

	private:
		GF::FPSCounter fps;
		sf::Clock begin;

		sf::Color clear_color;

		bool should_exit;

		bool static_screen;

		// std::map<std::string, GF::Widget*> widgets;
		// std::vector<std::string> widget_names;
	};
}
