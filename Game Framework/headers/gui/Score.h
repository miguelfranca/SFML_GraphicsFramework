#pragma once
#include <SFML/Graphics.hpp>
#include "../holders/Drawable.h"
#include "../holders/ResourceHolder.h"
#include "../sfml/Text.h"
#include "../Global.h"

namespace GF {

	class Score : public sf::Drawable {
	public:
		Score(std::string alignment = HORIZONTAL);

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
		std::string alignment;

		bool show_names = false;
	private:

		virtual void draw(sf::RenderTarget& renderer, sf::RenderStates state) const;
	};
}

