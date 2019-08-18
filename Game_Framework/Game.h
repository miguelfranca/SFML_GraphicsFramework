#pragma once
#include "holders.h"
#include "FPSCounter.h"
#include "sfml/Event.h"

namespace GF {

	class Game : public NonCopyable, public NonMovable{
	public:

		Game(): showfps(false), should_exit(false) {
			#ifdef TGUI_TGUI_HPP
				gui.setTarget(window);
			#endif
		}

		~Game();

		void setMaxFPS(int frames = 60);
		void showFPS(bool);
		void run();

	private:
		GF::FPSCounter fps;
		sf::Clock begin;
		bool showfps;

		sf::Color clear_color;

	protected:
		std::string title = "Window";
		sf::RenderWindow window;
		std::map<std::string, GF::Widget*> widgets;
		std::vector<std::string> widget_names;

	#ifdef TGUI_TGUI_HPP
		tgui::Gui gui;
	#endif

		void addWidget(GF::Widget* widget, std::string name = "");
		void clearWidgets();
		inline void deleteWidget(const std::string name);
		GF::Widget* getWidget(const std::string name);

		void setClearColor(const sf::Color);

	private:
		GF::Event::EventType pollEvents(GF::Event &event);
		void handleEvent(GF::Event& event);
		void update();

		// for user to create
		virtual bool onCreate() = 0;
		virtual bool onHandleEvent(GF::Event& event) = 0;
		virtual bool onUpdate(const float fElapsedTime, const float fTotalTime) = 0;
		virtual bool onDraw() = 0;
		virtual void onDestroy() = 0;

	private:
		bool should_exit;
	};
}
