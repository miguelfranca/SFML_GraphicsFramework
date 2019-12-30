#include "Game_Framework/StateMachine.h"

namespace GF
{

	StateMachine::StateMachine() : readyToSwitch(false)
	{
		mCurrentState = new EmptyState();
		// mCurrentState = nullptr;
	}

	bool StateMachine::onCreate()
	{
		checkSwitchState();
		return mCurrentState->onCreate();
	}

	bool StateMachine::onHandleEvent(GF::Event& event)
	{
		checkSwitchState();
		auto eventListeners = mCurrentState->getEventListeners();

		for (unsigned i = 0; i < eventListeners.size(); ++i) {
			if (event.type == std::get<0>(eventListeners[i]))
				std::get<1>(eventListeners[i])(event, std::get<2>(eventListeners[i]));
		}

		return mCurrentState->onHandleEvent(event);
	}

	bool StateMachine::onUpdate(float fElapsedTime, float fTotalTime)
	{
		checkSwitchState();
		return mCurrentState->onUpdate(fElapsedTime, fTotalTime);
	}

	bool StateMachine::onDraw()
	{
		checkSwitchState();
		return mCurrentState->onDraw();
	}

	void StateMachine::onDestroy()
	{
		checkSwitchState();
		mCurrentState->onDestroy();
	}

	bool StateMachine::change(const std::string stateName, State* state)
	{
		if (mStates.find(stateName) == mStates.end()) {
			if (state == nullptr)
				std::cout << "\n\""  << stateName << "\": State not found" << std::endl;
			else
				add(stateName, state);
		}

		lastState = mCurrentStateName;
		mCurrentState = mStates[stateName];
		mCurrentStateName = stateName;

		// calls 'onCreate' function if it hasnt already been called.
		// true if state doesnt already exist, false otherwise
		if (activeStates.insert(std::pair<std::string, State*>(stateName, state)).second)
			return mCurrentState->onCreate();
		else {
			readyToSwitch = true;
			return true;
		}
	}

	void StateMachine::add(std::string name, State* state)
	{
		mStates.insert(std::pair<std::string, State*>(name, state));

		if (mCurrentState == nullptr && mStates.size() > 0) {
			mCurrentState = mStates.begin()->second;
			mCurrentStateName = mStates.begin()->first;
		}
	}

	void StateMachine::deleteState(const std::string stateName)
	{
		auto it = mStates.find(stateName);

		if (it != mStates.end()) {
			delete mStates[stateName];
			mStates.erase(it);
			activeStates.erase(activeStates.find(stateName));
		}
	}

	void StateMachine::checkSwitchState(){
		if(readyToSwitch){
			mCurrentState->onSwitch(lastState);
			readyToSwitch = false;
		}
	}
}
