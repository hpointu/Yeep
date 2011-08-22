#include "Hud.hpp"
#include <iostream>
#include "ImageManager.cpp"
#include <sstream>
#include <string>

Hud::Hud()
{
	fps.SetColor(sf::Color(0,0,0));
	fps.SetText("fps: ??");
	fps.SetSize(12);
	fps.SetPosition(40, 10);
	if(!font1.LoadFromFile("res/arial.ttf"))
	{
		std::cout << "Cannot load font" << std::endl;
	}

	status = sf::Sprite();
	status.SetPosition(10, 10);
	refresh();
}

void Hud::render(sf::RenderTarget *t)
{
	t->Draw(status);
	t->Draw(fps);
}

void Hud::setFps(int val)
{
	std::stringstream s_fps;
	s_fps << val;
	fps.SetText("fps: "+s_fps.str());
}

void Hud::refresh()
{
	if(Application::getInstance()->physics_enabled)
		status.SetImage(*ImageManager::getInstance()->getImage("play"));
	else
		status.SetImage(*ImageManager::getInstance()->getImage("pause"));
}
