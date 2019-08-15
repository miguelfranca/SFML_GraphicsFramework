#include "FPSCounter.h"
#include "Game_Framework/sfml/Text.h"

namespace GF {

	FPSCounter::FPSCounter() : text(sf::Vector2f(0, 0), 15, sf::Color::White)
	{
	}

	void FPSCounter::setMaxFPS(int frames) {
		max_frame_count = frames;
	}

	//updates the FPS variable
	void FPSCounter::update()
	{
		static sf::Clock m_timer;

		elapsedTime = m_inBetween.restart().asSeconds();

		++m_frameCount;

		// sleep some time if fps is going too fast. The sleep is graduated while the fps is above max limit. This means that the fps flutuates around the limit of fps
		if (max_frame_count != -1 && m_frameCount / m_timer.getElapsedTime().asSeconds() >= max_frame_count)
			sf::sleep(sf::milliseconds((1.f - m_timer.getElapsedTime().asSeconds()) / (float)(max_frame_count) * 1000.f));

		if (m_timer.getElapsedTime().asSeconds() >= 0.2f) {
			m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
			m_frameCount = 0;
			m_timer.restart();
		}
	}

	//Draws the FPS display to the window
	void FPSCounter::draw(sf::RenderTarget& renderer, sf::RenderStates state)
	{
		update();
		text.setString("FPS " + std::to_string((int)m_fps));
		text.draw(renderer, state);
	}

	void FPSCounter::setFillColor(const sf::Color color){
		text.setFillColor(color);
	}

}
