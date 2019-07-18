#include <SFML/Graphics.hpp>

namespace GF {

	class Mouse {
	public:
		Mouse();

		class Button {
		public:
			Button(sf::Mouse::Button);

			bool clicked(const sf::Event& event);
			bool doubleClicked(const sf::Event& event);

			bool isPressed();
			bool released(sf::Event& event);

		private:
			sf::Mouse::Button button;
			bool first_click = false;
			sf::Clock clock;
		};
		
		static sf::Vector2f getPosition(const sf::RenderWindow &window);
		static Button Left;
		static Button Right;
		static Button Middle;
	};
}