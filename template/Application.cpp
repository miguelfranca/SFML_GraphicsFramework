#include "Application.h"


Application::Application(std::string t)
{
	title = t;
}

// called once before the loop starts
bool Application::onCreate()
{
	return true;
}

// first thing to be called every frame
bool Application::onHandleEvent(GF::Event& event)
{
	// skip if no events have happened and this function was just called 
	// because of the function calls order logic (handle events -> update -> draw) 
	if (event.isNothing()) return true;

	// handle waiting events, because events can stay in queue for a long time and that
	// is worse for user interaction. e.g maximum of 5 events per frame 
	int c = 0;
	while (window.pollEvent(event) && c++ < 5)
		onHandleEvent(event);
}

// called every frame before draw
bool Application::onUpdate(const float fElapsedTime, const float fTotalTime)
{
	return true;
}

// last thing to be called every frame
bool Application::onDraw()
{
	return true;
}

// called before exiting the app
void Application::onDestroy()
{

}

void Application::onSwitch(std::string other)
{

}
