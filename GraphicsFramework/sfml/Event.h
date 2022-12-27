#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GF {

	class Event : public sf::Event {
	public:
		Event() {};

		void skip() { type = Count; }

		bool isNothing() { return type == Count; }

		void showMessage() {
			switch (type)
			{
			case GF::Event::Closed:
				std::cout << "closed" << std::endl;
				break;
			case GF::Event::Resized:
				std::cout << "rezised" << std::endl;
				break;
			case GF::Event::LostFocus:
				std::cout << "lost focus" << std::endl;
				break;
			case GF::Event::GainedFocus:
				std::cout << "gained focus" << std::endl;
				break;
			case GF::Event::TextEntered:
				std::cout << "text entered Key: " << (char)(key.code) << std::endl;
				break;
			case GF::Event::KeyPressed:
				std::cout << "keypressed Key: " << key.code /*(char)(key.code + 65)*/ << std::endl;
				break;
			case GF::Event::KeyReleased:
				std::cout << "key realesed Key: " << key.code /*(char)(key.code + 65)*/ << std::endl;
				break;
			case GF::Event::MouseWheelMoved:
				std::cout << "mouse wheel moved Position: (" << mouseWheel.x << "," << mouseWheel.y << ")\tDelta: " << mouseWheel.delta << std::endl;
				break;
			/*case GF::Event::MouseWheelScrolled:
				std::cout << "mouse wheel scrooled Position: (" <<mouseWheelScroll.x << "," << mouseWheel.y << ")\tDelta: " << mouseWheel.delta  << "\tWheel: " << mouseWheelScroll.wheel << std::endl;
				break;*/
			case GF::Event::MouseButtonPressed:
				std::cout << "mouse button pressed Position: (" << mouseButton.x << "," << mouseButton.y << ")\tButton: " << (mouseButton.button == 0 ? "Right" : (mouseButton.button == 1 ? "Left" : (mouseButton.button == 3 ? "Middle" : std::to_string(mouseButton.button)))) << std::endl;
				break;
			case GF::Event::MouseButtonReleased:
				std::cout << "mouse button released Position: (" << mouseButton.x << "," << mouseButton.y << ")\tButton: " << (mouseButton.button == 0 ? "Right" : (mouseButton.button == 1 ? "Left" : (mouseButton.button == 3 ? "Middle" : std::to_string(mouseButton.button)))) << std::endl;
				break;
			case GF::Event::MouseMoved:
				std::cout << "mouse moved Position: (" << mouseButton.x << "," << mouseButton.y << ")" << std::endl;
				break;
			case GF::Event::MouseEntered:
				std::cout << "mouse entered screen Position: (" << mouseButton.x << "," << mouseButton.y << ")" << std::endl;
				break;
			case GF::Event::MouseLeft:
				std::cout << "mouse left screen Position: (" << mouseButton.x << "," << mouseButton.y << ")" << std::endl;
				break;
			case GF::Event::JoystickButtonPressed:
				std::cout << "joystick button pressed ID: " << joystickButton.joystickId << "\tButton: " << joystickButton.button << std::endl;
				break;
			case GF::Event::JoystickButtonReleased:
				std::cout << "joystick button released ID: " << joystickButton.joystickId << "\tButton: " << joystickButton.button << std::endl;
				break;
			case GF::Event::JoystickMoved:
				std::cout << "joystick moved ID: " << joystickMove.joystickId << "\tAxis: " << joystickMove.axis << "\tPosition" << joystickMove.position << std::endl;
				break;
			case GF::Event::JoystickConnected:
				std::cout << "joystick connected ID: " << joystickConnect.joystickId << std::endl;
				break;
			case GF::Event::JoystickDisconnected:
				std::cout << "joystick disconnected ID: " << joystickConnect.joystickId << std::endl;
				break;
			case GF::Event::TouchBegan: // unsupported event
				std::cout << "Touch began Finger: " << touch.finger << "\tPosition: (" << touch.x << "," << touch.y << ")" << std::endl;
				break;
			case GF::Event::TouchMoved:
				std::cout << "Touch mouved" << "\tPosition: (" << touch.x << "," << touch.y << ")" << std::endl;
				break;
			case GF::Event::TouchEnded:
				std::cout << "Touch ended Finger: " << touch.finger << "\tPosition: (" << touch.x << "," << touch.y << ")" << std::endl;
				break;
			case GF::Event::SensorChanged:
				std::cout << "sensor changed Type: " << sensor.type << "\tPosition: (" << sensor.x << "," << sensor.y << "," << sensor.z << ")" << std::endl;
				break;
			default:
				break;
			}
		}
	};

	static void waitEvent(sf::RenderWindow& window) {
		static GF::Event event;
		while (window.isOpen()) {
			window.pollEvent(event);
			if (event.type == GF::Event::KeyReleased)
				break;
		}
	}
}