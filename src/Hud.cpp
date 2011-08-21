#include "Hud.hpp"
#include <iostream>
#include "ImageManager.cpp"

Hud::Hud()
{
	status = sf::Sprite();
	status.SetPosition(10, 10);
	refresh();
}


void Hud::refresh()
{
	if(Application::getInstance()->physics_enabled)
		status.SetImage(*ImageManager::getInstance()->getImage("play"));
	else
		status.SetImage(*ImageManager::getInstance()->getImage("pause"));
}
