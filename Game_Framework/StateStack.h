#pragma once

#include "Game_Framework/sfml.h"
#include "Game_Framework/holders.h"

#include <stack>

namespace GF
{
	class StateStack
	{
	public:

		StateStack() { push(new EmptyState()); }

		bool handleEvent(GF::Event& event)
		{
			return top.handleEvent(event);
		}

		bool update(float fElapsedTime, float fTotalTime)
		{
			State top = mStack.top();
			return top.update(fElapsedTime, fTotalTime);
		}

		bool draw()
		{
			State top = mStack.top();
			return top.draw()
		}

		void push(Istate* state)
		{
			mStack.push(state);
		}

		State* pop()
		{
			State* p = nullptr;

			if (!empty()) {
				mStack.top()->onExit();
				State* p = mStack.pop();
				mStack.top()->onCreate();
			}

			return p;
		}

		inline bool empty() const
		{
			return mStack.empty();
		}

	private:
		std::stack<State*> mStack;
	};
}