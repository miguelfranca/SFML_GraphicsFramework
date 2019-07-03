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
