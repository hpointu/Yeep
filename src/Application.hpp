#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <SFML/Graphics.hpp>
#include "PausableClock.cpp"
#include "World.hpp"

#include "Singleton.h"

class Hud;

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;

	//allez : caca :)
	friend class Hud;

	enum MouseMode
	{
		Normal,
		Move,
		Add
	};

public:
	void init();
	void run();

	inline float getZoomFactor(){ return currentZoom; }



private:
	Application();
	sf::RenderWindow window;
	sf::View *view;

	void _processEvents();

	float currentZoom;

	World *world;

	MouseMode mouseMode;
	sf::Vector2f clickPos;

	bool physics_enabled;

	Hud *hud;

};

#endif // APPLICATION_HPP
