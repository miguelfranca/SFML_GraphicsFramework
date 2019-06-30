#include <SFML/Graphics.hpp>

namespace GF {

	class Mouse {
	public:
		Mouse();

		class Button {
		public:
			Button(sf::Mouse::Button);

			bool clickedOnce(sf::Event& event);
			bool doubleClicked(sf::Event& event);

			bool isPressed();

		private:
			sf::Mouse::Button button;
			bool first_click = false;
		};
		
		static sf::Vector2f getPosition(const sf::RenderWindow &window);
		static Button Left;
		static Button Right;
	};
}