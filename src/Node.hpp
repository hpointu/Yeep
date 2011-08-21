#ifndef NODE_HPP
#define NODE_HPP
#include "Body.hpp"

class Node : public Body
{
public:
	Node(b2World *p_world, float x, float y);

	sf::FloatRect getRect();

	void onClick(){
		toggleSelected();
	}
	virtual void update();

	virtual void physicSetup();
private:
	float radius;
};

#endif // NODE_HPP
