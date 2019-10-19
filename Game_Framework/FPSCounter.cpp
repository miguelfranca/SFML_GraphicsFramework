#include "FPSCounter.h"
#include "Game_Framework/sfml.h"
#include <iostream>

namespace GF
{

	FPSCounter::FPSCounter(sf::RenderTarget* renderer) : text(sf::Vector2f(0, 0), 15 * SW,
		        sf::Color::White)
	{
		m_target = renderer;
	}

	void FPSCounter::setMaxFPS(unsigned frames)
	{
		max_frame_count = frames;
		// ((sf::RenderWindow*)m_target)->setFramerateLimit(frames);
	}

	bool FPSCounter::handleEvent(GF::Event& event)
	{
		// show fps event - F key
		static GF::ToggleKey F(sf::Keyboard::F);

		if (F.isKeyReleasedOnce(event))
			showfps = !showfps;

		return true;
	}

	//updates the FPS variable
	void FPSCounter::update()
	{
		static sf::Clock m_timer;

		elapsedTime = m_inBetween.restart().asSeconds();

		++m_frameCount;

		// sleep some time if fps is going too fast. The sleep is graduated while the fps is above max limit. This means that the fps flutuates around the limit of fps
		if (max_frame_count != -1 && m_frameCount / m_timer.getElapsedTime().asSeconds() >= max_frame_count)
			sf::sleep(sf::milliseconds((1.f - m_timer.getElapsedTime().asSeconds()) / (float)(
			                               max_frame_count) * 1000.f));

		// update fps text every 'DISPLAY_FREQ' seconds
		if (display_counter % (int)(max_frame_count * DISPLAY_FREQ) == 0) {
			m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
			m_frameCount = 0;
			m_timer.restart();

			text.setString("FPS " + std::to_string((int)m_fps));
			display_counter = 0;
		}

		++display_counter;
	}

	//Draws the FPS to the window
	bool FPSCounter::draw()
	{
		if (!showfps)
			return true;

		update();
		text.draw(*m_target, sf::RenderStates::Default);

		return true;
	}

	void FPSCounter::setFillColor(const sf::Color color)
	{
		text.setFillColor(color);
	}

}
