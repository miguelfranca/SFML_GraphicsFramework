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
	return true;
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
