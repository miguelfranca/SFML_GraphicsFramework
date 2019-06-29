#include "../../headers/holders/Drawable.h"

namespace GF {
	bool draw(sf::RenderTarget& renderer, sf::RenderStates state, sf::Drawable& x) {
		renderer.draw(x, state);
		return true;
	}

	bool draw(sf::RenderTarget& renderer, sf::RenderStates state, GF::Drawable& x) {
		x.draw(renderer, state);
		return true;
	}
}