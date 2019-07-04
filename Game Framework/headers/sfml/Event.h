#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace GF {

	class Event : public sf::Event {
	public:
		Event() : type(NoEvent) {};

		void skip() { type = NoEvent; }

		Event(sf::Event event){
			this->type = GF::Event::EventType(event.type);
			this->size = event.size;
			this->key = event.key;
			this->text = event.text;
			this->mouseMove = event.mouseMove;
			this->mouseButton = event.mouseButton;
			this->mouseWheel = event.mouseWheel;
			this->mouseWheelScroll = event.mouseWheelScroll;
			this->joystickMove = event.joystickMove;
			this->joystickButton = event.joystickButton;
			this->joystickConnect = event.joystickConnect;
			this->touch = event.touch;
			this->sensor = event.sensor;
		}

		enum EventType {
			Closed,                 ///< The window requested to be closed (no data)
			Resized,                ///< The window was resized (data in event.size)
			LostFocus,              ///< The window lost the focus (no data)
			GainedFocus,            ///< The window gained the focus (no data)
			TextEntered,            ///< A character was entered (data in event.text)
			KeyPressed,             ///< A key was pressed (data in event.key)
			KeyReleased,            ///< A key was released (data in event.key)
			MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
			MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
			MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
			MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
			MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
			MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
			MouseLeft,              ///< The mouse cursor left the area of the window (no data)
			JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
			JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
			JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
			JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
			JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)
			TouchBegan,             ///< A touch event began (data in event.touch)
			TouchMoved,             ///< A touch moved (data in event.touch)
			TouchEnded,             ///< A touch event ended (data in event.touch)
			SensorChanged,          ///< A sensor value changed (data in event.sensor)

			/// My addicional events
			LeftMouseDoubleClickedEvent,	 ///< left mouse button double clicked (event.mouseButton)
			LeftMouseClickedOnceEvent,		 ///< left mouse button clicked and released (event.mouseButton)
			RightMouseDoubleClickedEvent,	 ///< right mouse button double clicked (event.mouseButton)
			RightMouseClickedOnceEvent,		 ///< right mouse button clicked and released (event.mouseButton)
			NoEvent,
			Count
		};

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
				std::cout << "text entered Key: " << (char)key.code << std::endl;
				break;
			case GF::Event::KeyPressed:
				std::cout << "keypressed Key: " << key.code << std::endl;
				break;
			case GF::Event::KeyReleased:
				std::cout << "key realesed Key: " << key.code <<  std::endl;
				break;
			case GF::Event::MouseWheelMoved:
				std::cout << "mouse wheel moved Position: (" << mouseWheel.x << "," << mouseWheel.y << ")\tDelta: " << mouseWheel.delta << std::endl;
				break;
			case GF::Event::MouseWheelScrolled:
				std::cout << "mouse wheel scrooled Position: (" << mouseWheel.x << "," << mouseWheel.y << ")\tDelta: " << mouseWheel.delta << std::endl;
				break;
			case GF::Event::MouseButtonPressed:
				std::cout << "mouse button pressed Position: (" << mouseButton.x << "," << mouseButton.y << ")\tButton: " << mouseButton.button << std::endl;
				break;
			case GF::Event::MouseButtonReleased:
				std::cout << "mouse button released Position: (" << mouseButton.x << "," << mouseButton.y << ")\tButton" << mouseButton.button << std::endl;
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
				std::cout << "joystick moved ID: " << joystickMove.joystickId << "\tAxis: "<< joystickMove.axis << "\tPosition" << joystickMove.position << std::endl;
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
			case GF::Event::LeftMouseDoubleClickedEvent:
				std::cout << "left double clicked Button: " << mouseButton.button << std::endl;
				break;
			case GF::Event::LeftMouseClickedOnceEvent:
				std::cout << "left clicked once Button: " << mouseButton.button << std::endl;
				break;
			case GF::Event::RightMouseDoubleClickedEvent:
				std::cout << "right double clicked Button: " << mouseButton.button << std::endl;
				break;
			case GF::Event::RightMouseClickedOnceEvent:
				std::cout << "right clicked once Button: " << mouseButton.button << std::endl;
				break;
			default:
				break;
			}
		}

		EventType type;
	};

	static void waitEvent(sf::RenderWindow& window) {
		static sf::Event event;
		while (window.isOpen()) {
			window.pollEvent(event);
			if (event.type == sf::Event::KeyReleased)
				break;
		}
	}
}
