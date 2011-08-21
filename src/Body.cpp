#include "Body.hpp"

Body::Body(b2World *p_world)
	: p_world(p_world)
{

}

void Body::render(sf::RenderTarget *target)
{
	target->Draw(*this->getShape());
}

void Body::adjust()
{
	if(body && getShape())
	{
		b2Vec2 position = body->GetPosition();
		getShape()->SetPosition(position.x, -position.y);
	}
}

void Body::setPosition(float x, float y)
{
	setStatic(true);
	body->SetTransform(b2Vec2(x, -y), body->GetAngle());
	getShape()->SetPosition(x, y);
	setStatic(false);
}

void Body::setStatic(bool q)
{
	if(q)
		body->SetType(b2_staticBody);
	else
		body->SetType(b2_dynamicBody);
}

void Body::joinWith(Body *b)
{
	b2DistanceJointDef jointDef;
	b2Body *_b1 = getBody();
	b2Body *_b2 = b->getBody();

	b->setStatic();
	jointDef.Initialize(_b1,
						_b2,
						_b1->GetWorldCenter(),
						_b2->GetWorldCenter());
	jointDef.frequencyHz = 2.0f;
	jointDef.dampingRatio = 0.1f;
	jointDef.collideConnected = true;

	jointDef.length = 10;

	p_world->CreateJoint(&jointDef);
	b->setStatic(false);
}

void Body::deleteMe()
{
	if(body)
		p_world->DestroyBody(body);
	body = NULL;
}

Body::~Body()
{

}
