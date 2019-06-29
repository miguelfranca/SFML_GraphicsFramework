#pragma once
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../sfml/Event.h"
#include "Drawable.h"

namespace GF {
	class State : public GF::Drawable {
	public:
		virtual void handleEvent(GF::Event& event) {}
		virtual void update() {}
		bool active = false;
	};
}