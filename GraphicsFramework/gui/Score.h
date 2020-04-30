#pragma once
#include <SFML/Graphics.hpp>
#include "../holders/Drawable.h"
#include "../holders/ResourceHolder.h"
#include "../sfml/Text.h"
#include "../Global.h"
#include "../sfml/Orientation.h"

namespace GF {

	class Score : public sf::Drawable {
	public:
		Score(GF::Orientation alignment = GF::HORIZONTAL);

		template<typename T>
		void add(const T name) {
			map.insert(std::make_pair(name, 0));
		}
		template<typename T, typename ...T2>
		void add(const T name, T2...rest) {
			map.insert(std::make_pair(name, 0)); add(rest...);
		}

		void setPosition(sf::Vector2f pos);
		void setPosition(float xx, float yy);
		void setSize(float s);

		void inc(std::string name, float add = 1);
		void showNames(bool b);

	private:

		float x = 0.f, y = 0.f;
		float size = 0.f;

		std::map<std::string, float> map;

		GF::Text text;
		GF::Orientation alignment;

		bool show_names = false;
	private:

		virtual void draw(sf::RenderTarget& renderer, sf::RenderStates state) const;
	};
}

