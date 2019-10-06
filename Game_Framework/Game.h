#pragma once
#include "holders.h"
#include "FPSCounter.h"
#include "StateMachine.h"
#include "sfml/Event.h"

#include <functional>

namespace GF
{

	class Game : public NonCopyable, public NonMovable
	{
	public:

		Game() : fps(&window), max_fps(-1), should_exit(false)
		{
#ifdef TGUI_TGUI_HPP
			gui.setTarget(window);
#endif
		}

		~Game();

		void setMaxFPS(int frames = 60);
		void showFPS(bool);
		void run();

	protected:
		std::string title = "Window";
		sf::RenderWindow window;
		GF::StateMachine sm;

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

		// template<class T, typename Function>
		// void addKeyListener(Function&& fn) const
		// {
		// 	keyListeners.push_back(std::forward<Function>(fn));
		// }
		// std::vector<void(*)()> keyListeners;


	private:
		GF::Event::EventType pollEvents(GF::Event& event);
		void handleEvent(GF::Event& event);
		void update();

		// for user to create
		virtual bool onCreate() = 0;
		virtual bool onHandleEvent(GF::Event& event) = 0;
		virtual bool onUpdate(const float fElapsedTime, const float fTotalTime) = 0;
		virtual bool onDraw() = 0;
		virtual void onDestroy() = 0;


	private:
		GF::FPSCounter fps;
		int max_fps;
		sf::Clock begin;

		sf::Color clear_color;

		bool should_exit;

		std::map<std::string, GF::Widget*> widgets;
		std::vector<std::string> widget_names;

	};
}
