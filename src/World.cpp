#include "World.hpp"
#include "Node.hpp"
#include <iostream>

World::World()
{
	p_world = new b2World(b2Vec2(0.0f, -0.f), true);


	this->addBody(new Node(p_world, 22,0));
	this->addBody(new Node(p_world, 120,100));
	this->addBody(new Node(p_world, 100,0));
}

void World::render(sf::RenderTarget *target)
{
	for (unsigned int i=0; i<edges.size(); i++)
	{
		sf::Shape l = sf::Shape::Line(edges.at(i).b1->getShape()->GetPosition(),
									  edges.at(i).b2->getShape()->GetPosition(),
									  2.f/SCALE,
									  sf::Color(100,100,100));
		target->Draw(l);
	}

	for (unsigned int i=0; i<bodies.size(); i++)
		bodies.at(i)->render(target);

}

void World::addBody(Body *b)
{
	bodies.push_back(b);
}

void World::step()
{
	float32 tstep = 1.0f/20.0f;
	p_world->Step(tstep, 20, 20);

	//synchronize bodies
	for (unsigned int i=0; i<bodies.size(); i++)
		bodies.at(i)->adjust();

	p_world->ClearForces();

	deleteQueue();
}

void World::selectBody(Body *b)
{
	if(b)
		b->toggleSelected();
}

void World::clearSelection()
{
	for(unsigned int i=0; i<bodies.size(); i++)
	{
		if(bodies[i]->isSelected())
			bodies[i]->toggleSelected();
	}
}

void World::joinSelection()
{
	std::vector<Body*> selection = getSelection();
	if(selection.size() == 2)
	{
		selection[0]->joinWith(selection[1]);
		Edge e;
		e.b1 = selection[0];
		e.b2 = selection[1];
		edges.push_back(e);
	}
	else
	{
		std::cout << "Non." << std::endl;
	}
}

void World::makeTriad(Body *b1, Body *b2, Body *b3)
{

}

void World::resetForces()
{
	for(unsigned int i=0; i<bodies.size(); i++)
	{
		bodies.at(i)->setStatic(true);
		bodies.at(i)->setStatic(false);
	}
}

void World::moveSelection(sf::Vector2f to)
{
	std::vector<Body*> selection = getSelection();
	if(selection.size() == 1)
	{
		for(unsigned int i=0; i<selection.size(); i++)
		{
			selection.at(i)->setPosition(to.x, to.y);
		}
	}
}

std::vector<Body*> World::getSelection()
{
	std::vector<Body*> result;
	for(unsigned int i=0; i<bodies.size(); i++)
	{
		if(bodies[i]->isSelected())
			result.push_back(bodies[i]);
	}
	return result;
}

Body* World::getHighestBodyOnPos(sf::Vector2f pos)
{
	// dans ce sens, car... la flemme d'expliquer
	unsigned int i = bodies.size();
	while(i!=0)
	{
		Body *b = bodies.at(i-1);
		sf::FloatRect r = b->getRect();
		if(r.Contains(pos.x, pos.y))
			return b;
		i--;
	}

	return NULL;
}

void World::deleteQueue()
{
	if(toDelete.size()>0)
	{
		std::vector<Body *> _delList(toDelete);
		while(_delList.size() > 0)
		{
			Body *b = _delList.back();
			_delList.pop_back();
			b->deleteMe();
			int i = getBodyIndex(b);
			if(i>=0)
				bodies.erase(bodies.begin()+i);
		}


		// on recrée la liste de edges sans les sommets virés
		std::vector<Edge> _new_edges;
		for(unsigned int i=0; i<edges.size(); i++)
		{
			if(getBodyIndex(edges[i].b1) >- 1 && getBodyIndex(edges[i].b2) > -1)
				_new_edges.push_back(edges[i]);
		}
		edges = _new_edges;
	}
}

int World::getBodyIndex(Body *b)
{
	for(unsigned int i=0; i<bodies.size(); i++)
	{
		if(bodies.at(i) == b)
			return i;
	}
	return -1;
}
