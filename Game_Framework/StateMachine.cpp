#include "Game_Framework/StateMachine.h"

namespace GF
{

	StateMachine::StateMachine()
	{
		mCurrentState = new EmptyState();
		mCurrentState = nullptr;
	}

	bool StateMachine::onCreate()
	{
		return mCurrentState->onCreate();
	}

	bool StateMachine::onHandleEvent(GF::Event& event)
	{
		return mCurrentState->onHandleEvent(event);
	}

	bool StateMachine::onUpdate(float fElapsedTime, float fTotalTime)
	{
		return mCurrentState->onUpdate(fElapsedTime, fTotalTime);
	}

	bool StateMachine::onDraw()
	{
		return mCurrentState->onDraw();
	}

	void StateMachine::onDestroy()
	{
		mCurrentState->onDestroy();
	}

	bool StateMachine::change(const std::string stateName, State* state)
	{
		if (mStates.find(stateName) == mStates.end()) {
			if (state == nullptr)
				std::cout << "\n\""  << stateName << "\" State not found" << std::endl;
			else
				add(stateName, state);
		}

		mCurrentState = mStates[stateName];

		// calls 'onCreate' function if it hasnt already been called.
		// true if state doesnt already exist, false otherwise
		if (activeStates.insert(std::pair<std::string, State*>(stateName, state)).second)
			return mCurrentState->onCreate();
		else
			return true;
	}

	void StateMachine::add(std::string name, State* state)
	{
		mStates.insert(std::pair<std::string, State*>(name, state));

		if (mCurrentState == nullptr && mStates.size() > 0)
			mCurrentState = mStates.begin()->second;
	}

	void StateMachine::deleteState(const std::string stateName)
	{
		auto it = mStates.find(stateName);

		if (it != mStates.end()) {
			delete mStates[stateName];
			mStates.erase(it);
			activeStates.erase(it);
		}
	}
}
