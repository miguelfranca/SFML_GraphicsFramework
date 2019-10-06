#pragma once

#include <SFML/Graphics.hpp>
#include "holders/Widget.h"
#include "sfml/Text.h"

#define DISPLAY_FREQ 0.1  // seconds

namespace GF
{

	class FPSCounter : public GF::Widget
	{
	public:
		FPSCounter(sf::RenderTarget* renderer = nullptr);

		// draws a string into the window with the fps counter
		bool draw() override;
		bool handleEvent(GF::Event& event) override;

		// sets the max limit of frames per second
		void setMaxFPS(unsigned frames = 60);

		inline float getMaxFPS() const { return max_frame_count; }

		inline void show(bool s = true) { showfps = s; }

		// returns time between each frame, as seconds
		inline float getElapsedTime() const { return elapsedTime; }

		inline float getFPS() const { return m_fps; }

		void setFillColor(const sf::Color);

	private:
		sf::Clock m_fpsTimer;

		float m_fps = 0.f;
		float elapsedTime = 0.f;

		GF::Text text;

		int max_frame_count = -1;

		unsigned display_counter = 0;

		bool showfps = true;

	private:
		// calculates fps
		void update();
	};
}
