#pragma once
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Drawable.h"

namespace GF {
	class State : public GF::Drawable {
	public:
		virtual void handleEvent(sf::Event& event) {}
		virtual void update() {}
		bool active = false;
	};
}