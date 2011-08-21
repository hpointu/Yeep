#ifndef BODY_HPP
#define BODY_HPP

#include "Const.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Body
{
public:
	Body(b2World *p_world);
	~Body();

	void render(sf::RenderTarget *target);

	inline sf::Shape* getShape(){return &shape;}

	virtual sf::FloatRect getRect() = 0;

	virtual void onClick() = 0;

	virtual void update() = 0;

	virtual void physicSetup() = 0;

	void setPosition(float x, float y);

	inline void toggleSelected(){selected = selected ? false : true ; update();}
	inline bool isSelected(){return selected;}

	void adjust();

	void setStatic(bool q = true);

	void joinWith(Body *b);

	inline b2Body* getBody() {return body;}

	void deleteMe();

protected:
	 sf::Shape shape;
	 bool selected;
	 b2Body *body;
	 b2World *p_world;

};

#endif // BODY_HPP
