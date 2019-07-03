#pragma once
#include "../holders.h"
#include "FPSCounter.h"
#include "sfml/Event.h"

namespace GF {

	class Game : public NonCopyable, public NonMovable{
	public:

		void setMaxFPS(int frames = 60);
		void showFPS(bool);

		virtual bool onCreate() = 0;
		virtual bool onHandleEvent(GF::Event& event) = 0;
		virtual bool onUpdate(float fElapsedTime) = 0;
		virtual bool onDraw(sf::RenderTarget& renderer, sf::RenderStates state) = 0;

		void run();


	private:
		GF::FPSCounter fps;
		bool showfps = false;
		bool should_exit = false;

	protected:
		std::string title = "Window";
		sf::RenderWindow window;

	private:
		GF::Event::EventType pollEvent(GF::Event &event);
		void handleEvent(GF::Event& event);
		void update();
	};
}
