#pragma once

#include "GraphicsFramework/sfml.h"
#include "GraphicsFramework/holders.h"

#include <stack>

namespace GF
{
	class StateStack
	{
	public:

		StateStack() { push(new EmptyState()); }

		bool handleEvent(GF::Event& event)
		{
			return mStack.top()->onHandleEvent(event);
		}

		bool update(float fElapsedTime, float fTotalTime)
		{
			return mStack.top()->onUpdate(fElapsedTime, fTotalTime);
		}

		bool draw()
		{
			return mStack.top().onDraw()
		}

		bool push(Istate* state)
		{
			mStack.push(state);

			if (activeStates.insert(std::pair<std::string, State*>(stateName, state)).second)
				return mCurrentState->onCreate();
			else
				return true;
		}

		State* pop()
		{
			State* p = nullptr;

			if (!empty())
				p = mStack.pop();

			return p;
		}

		inline bool empty() const
		{
			return mStack.empty();
		}

	private:
		std::stack<State*> mStack;
		std::map<std::string, State*> activeStates;
	};
}