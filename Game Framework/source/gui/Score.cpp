#pragma once
#include "../../headers/gui/Score.h"
#include "../../headers/sfml/Text.h"

namespace GF {

	Score::Score(std::string alignment) {
		this->alignment = alignment;
	}

	void Score::draw(sf::RenderTarget& renderer, sf::RenderStates state) const {
		float xx = x, yy = y;
		float* z = &xx; // alignment == HORIZONTAL

		if (alignment == VERTICAL)
			z = &yy;
		
		*z -= size / 2.f;

		float spacing = size / map.size();
		float init = *z + spacing / 2;
		
		*z = init;

		for (auto& kv : map) {
			GF::Text text ((show_names ? kv.first + ": " : "") + std::to_string(kv.second), sf::Vector2f(xx, yy), 40, sf::Color::White, CENTERED);
			text.draw(renderer, state);
			*z += spacing;
		}
	}

	void Score::setPosition(sf::Vector2f pos) { x = pos.x; y = pos.y; }
	void Score::setPosition(float xx, float yy) { x = xx; y = yy; }

	void Score::setSize(float s) { size = s; }

	void Score::inc(std::string name, float add) { map.at(name) += add; }

	void Score::showNames(bool b) { show_names = b; }
}

