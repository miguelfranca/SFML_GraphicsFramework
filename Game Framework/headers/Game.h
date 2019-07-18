#pragma once
#include "../holders.h"
#include "FPSCounter.h"

namespace GF {

	class Game : public NonCopyable, public NonMovable{
	public:

		void setMaxFPS(int frames = 60);
		void showFPS(bool);

		virtual bool onCreate() = 0;
		virtual bool onHandleEvent(sf::Event& event) = 0;
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
		sf::Event::EventType pollEvent(sf::Event &event);
		void handleEvent(sf::Event& event);
		void update();
	};
}
