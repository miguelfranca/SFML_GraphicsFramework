#pragma once
#include "holders.h"
#include "FPSCounter.h"
#include "StateMachine.h"
#include "sfml/Event.h"

#include <functional>

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

	protected:
		std::string title = "Window";
		sf::RenderWindow window;
		GF::StateMachine states;

#ifdef TGUI_TGUI_HPP
		tgui::Gui gui;
#endif

	protected:
		void addWidget(GF::Widget* widget, std::string name = "");
		void clearWidgets();
		inline void deleteWidget(const std::string name);
		GF::Widget* getWidget(const std::string name);

		void setClearColor(const sf::Color);

		inline float getFPS() const { return fps.getFPS(); }
		inline float getMaxFPS() const { return fps.getMaxFPS(); }

		void addEventListener(GF::Event::EventType event, void *(*func) (void*), void* args)
		{
			eventListeners.push_back(std::make_tuple(event, func, args));
		}

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

		std::map<std::string, GF::Widget*> widgets;
		std::vector<std::string> widget_names;

		std::vector<std::tuple<GF::Event::EventType, void *(*) (void*), void*>> eventListeners;
	};
}
