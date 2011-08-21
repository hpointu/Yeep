#include "Node.hpp"

Node::Node(b2World *p_world, float x, float y) :
	Body(p_world),
	radius(10.f)
{

	getShape()->SetPosition(x/SCALE, y/SCALE);
	update();
	this->physicSetup();
}

sf::FloatRect Node::getRect()
{
	sf::Vector2f pos = this->getShape()->GetPosition();
	return sf::FloatRect(pos.x - radius/SCALE, pos.y -radius/SCALE, pos.x + radius/SCALE, pos.y + radius/SCALE);
}

void Node::update()
{
	sf::Vector2f pos = getShape()->GetPosition();

	sf::Color color(0, 180, 0);

	if(isSelected())
		color = sf::Color(0, 0, 200);

	this->shape = sf::Shape::Circle(0,
									0,
									radius/SCALE,
									sf::Color(0, 180, 0, 90),
									-2.f/SCALE,
									color
									);
	this->shape.SetPosition(pos);
}

void Node::physicSetup()
{
	b2BodyDef bodyDef;
	b2CircleShape p_shape;
	p_shape.m_p.Set(0,0);
	p_shape.m_radius = radius/SCALE;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &p_shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.userData = this;

	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.position.Set(getShape()->GetPosition().x, -getShape()->GetPosition().y);

	body = p_world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);


}
