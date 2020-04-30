#pragma once

#include "GraphicsFramework/sfml.h"

namespace GF
{
	class State
	{
	public:
		State() { }
		virtual ~State() { }

		virtual bool onCreate() = 0;
		virtual bool onHandleEvent(GF::Event& event) = 0;
		virtual bool onUpdate(float fElapsedTime, float fTotalTime) = 0;
		virtual bool onDraw() = 0;
		virtual void onDestroy() = 0;
		virtual void onSwitch(std::string) = 0;
		
		inline std::vector<std::tuple<GF::Event::EventType, void* (*)(GF::Event&, void*), void*>> getEventListeners() const { return eventListeners; }

	protected:
		void addEventListener(GF::Event::EventType event, void* (*func)(GF::Event&, void*), void* args = NULL)
		{
			eventListeners.push_back(std::make_tuple(event, func, args));
		}
	private:
		std::vector<std::tuple<GF::Event::EventType, void* (*)(GF::Event&, void*), void*>> eventListeners;
	};

	class StateMachine;

	class EmptyState : public State
	{
	public:
		EmptyState() { }
		EmptyState(StateMachine* stateMachine) { states = stateMachine; }

		~EmptyState() { }

		bool onCreate() override { return true; }

		bool onHandleEvent(GF::Event& event) override { return true; }

		bool onUpdate(float fElapsedTime, float fTotalTime) override { return true; }

		bool onDraw() override { return true; }

		void onDestroy() override { }

		void onSwitch(std::string) override { }

	protected:
		StateMachine* states;
	};
}