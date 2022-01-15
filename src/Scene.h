#pragma once
#include <vector>
#include "Agent.h"

class Scene
{
public:
	virtual ~Scene()
	{
		for (auto ptr : agents)
		{
			delete ptr;
		}
		agents.clear();

		delete player;
	}

	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };
	std::vector<Agent*> agents;
	Agent* player;

protected:
	bool drawPaths = false;
};