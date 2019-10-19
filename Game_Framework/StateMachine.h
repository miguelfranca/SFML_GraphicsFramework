#pragma once

#include "Game_Framework/holders.h"

#include <map>

namespace GF
{
	class StateMachine
	{
	public:

		StateMachine();

		bool onCreate();
		bool onHandleEvent(GF::Event& event);
		bool onUpdate(float fElapsedTime, float fTotalTime);
		bool onDraw();
		void onDestroy();

		bool change(const std::string stateName, State* state = nullptr);
		void add(std::string name, State* state);
		void deleteState(const std::string stateName);

	private:
		std::map<std::string, State*> activeStates;
		std::map<std::string, State*> mStates;
		State* mCurrentState;
	};
}