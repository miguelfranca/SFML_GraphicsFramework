#pragma once
#include "Widget.h"
#include <SFML/Graphics.hpp>
namespace GF
{

	class Drawable
	{
	public:
		virtual void draw(sf::RenderTarget& renderer, sf::RenderStates state) { } ;
	};

	bool draw(sf::RenderTarget& renderer, sf::RenderStates state, sf::Drawable& x);

	bool draw(sf::RenderTarget& renderer, sf::RenderStates state, GF::Drawable& x);

	bool draw(sf::RenderTarget& renderer, sf::RenderStates state, GF::Widget& x);

	/*template<typename T, typename ...T2>
	void draw(sf::RenderTarget& renderer, sf::RenderStates state, const T& x, T2& ...rest) {
		draw(renderer, state, x);
		draw(renderer, state, rest...);
	}*/

	template<typename ...T2>
	void Draw(sf::RenderTarget& renderer, sf::RenderStates state, T2& ...args)
	{
		(void)std::initializer_list< bool > { (draw(renderer, state, args), true) ... };
	}
}