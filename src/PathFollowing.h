#pragma once
#include "Agent.h"
#include "Path.h"

class PathFollowing :
	public Agent::SteeringBehavior
{
private:
	void applySteeringForce(Agent *agent, float dtime);

public:
	PathFollowing();
	~PathFollowing();
};