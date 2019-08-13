#pragma once

#include <SFML/Graphics.hpp>
#include "holders/Drawable.h"
#include "sfml/Text.h"

namespace GF {

	class FPSCounter : public Drawable
	{
	public:
		FPSCounter();

		// draws a string into the window with the fps counter
		void draw(sf::RenderTarget& renderer, sf::RenderStates state) override;

		// sets the max limit of frames per second (oscilates a little bit around the given number)
		void setMaxFPS(int frames = 60);

		// calculates FPS
		void update();

		// returns time between frames as seconds
		inline float getElapsedTime() const { return elapsedTime; }

	private:
		sf::Clock m_inBetween;
		sf::Clock m_fpsTimer;

		float m_fps = 0.f;
		float elapsedTime = 0.f;

		GF::Text text;

		int m_frameCount = 0;
		int max_frame_count = -1;
	};
}
