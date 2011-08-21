#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "Body.hpp"
#include <map>

#include <Box2D/Box2D.h>

typedef struct
{
	Body* b1;
	Body* b2;
} Edge;

class World
{
public:
    World();

	void render(sf::RenderTarget *target);
	void addBody(Body *b);

	Body* getHighestBodyOnPos(sf::Vector2f pos);

	void selectBody(Body *b);

	void clearSelection();

	std::vector<Body*> getSelection();

	void joinSelection();
	void moveSelection(sf::Vector2f to);

	void makeTriad(Body *b1, Body *b2, Body *b3);

	void step();

	void resetForces();

	void enqueueToDelete(Body *b)
	{
		toDelete.push_back(b);
	}

	void deleteQueue();


	b2World* PWorld(){return p_world;}

	void addEdge();

private:
	std::vector<Body*> bodies;
	std::vector<Body*> toDelete;
	b2World *p_world;

	int getBodyIndex(Body *b);

	std::vector<Edge> edges;

};

#endif // WORLD_HPP
