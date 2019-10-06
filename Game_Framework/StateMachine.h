#pragma once

#include "Game_Framework/holders.h"

#include <map>

namespace GF
{
	class StateMachine
	{
	public:

		StateMachine()
		{
			mCurrentState = new EmptyState();
			mStates.insert(std::pair<std::string, State*>("EmptyState", mCurrentState));
		}

		bool onCreate()
		{
			return mCurrentState->onCreate();
		}

		bool onHandleEvent(GF::Event& event)
		{
			return mCurrentState->onHandleEvent(event);
		}

		bool onUpdate(float fElapsedTime, float fTotalTime)
		{
			return mCurrentState->onUpdate(fElapsedTime, fTotalTime);
		}

		bool onDraw()
		{
			return mCurrentState->onDraw();
		}

		void onDestroy()
		{
			mCurrentState->onDestroy();
		}

		bool change(const std::string stateName)
		{
			if (mStates.find(stateName) == mStates.end())
				std::cout << "\n\""  << stateName << "\" State not found" << std::endl;

			mCurrentState->onDestroy();
			mCurrentState = mStates[stateName];
			return mCurrentState->onCreate();
		}

		bool change(const std::string stateName, State* state)
		{
			if (mStates.find(stateName) == mStates.end())
				add(stateName, state);

			mCurrentState->onDestroy();
			mCurrentState = mStates[stateName];
			return mCurrentState->onCreate();
		}

		void add(std::string name, State* state)
		{
			mStates.insert(std::pair<std::string, State*>(name, state));
		}

	private:
		std::map<std::string, State*> mStates;
		State* mCurrentState;
	};
}