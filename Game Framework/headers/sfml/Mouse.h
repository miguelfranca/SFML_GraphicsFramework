#include <SFML/Graphics.hpp>
#include "Event.h"

namespace GF {

	class Mouse {
	public:
		Mouse();

		class Button {
		public:
			Button(sf::Mouse::Button);

			bool clicked(const GF::Event& event);
			bool doubleClicked(GF::Event& event);

			bool isPressed();
			bool released(GF::Event& event);

		private:
			sf::Mouse::Button button;
			bool first_click = false;
		};
		
		static sf::Vector2f getPosition(const sf::RenderWindow &window);
		static Button Left;
		static Button Right;
	};
}