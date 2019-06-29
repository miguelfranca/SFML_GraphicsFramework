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
		private:
			sf::Mouse::Button button;
			bool first_click = false;
		};
		
		static Button Left;
		static Button Right;
	};
}