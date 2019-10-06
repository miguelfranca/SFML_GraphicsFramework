#pragma once

#include "Game_Framework/sfml.h"

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
	};

	class StateMachine;

	class EmptyState : public State
	{
	public:
		EmptyState() { }
		EmptyState(StateMachine* stateMachine) { sm = stateMachine; }

		~EmptyState() { }

		bool onCreate() { return true; }

		bool onHandleEvent(GF::Event& event) override { return true; }

		bool onUpdate(float fElapsedTime, float fTotalTime) override { return true; }

		bool onDraw() override { return true; }

		void onDestroy() override { }

	protected:
		StateMachine* sm;
	};
}