#pragma once

#include <SFML/Graphics.hpp>
#include "../sfml/Event.h"

namespace GF {

	class Widget
	{
	public:
		Widget(sf::RenderTarget* renderer = nullptr) { m_target = renderer; }
		virtual ~Widget() {}
		
		virtual bool handleEvent(GF::Event& event) = 0;
		virtual bool update(const float fElapsedTime, const float fTotalTime) {return true;};
		virtual bool draw() = 0;
		virtual void setTarget(sf::RenderTarget* renderer) { m_target = renderer; }
	protected:
		sf::RenderTarget* m_target = nullptr;
	};
}
