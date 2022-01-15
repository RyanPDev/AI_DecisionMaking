#include "Chase.h"
#include "Patrol.h"
#include "Agent.h"
#include "utils.h"
#include "Evade.h"
#include "Scene.h"

IFSMState* Chase::Update(Agent* agent, float dtime)
{
	timer -= dtime;
	if (timer <= 0)
	{
		agent->ChooseNewGoal(pix2cell(agent->sensors->scene->player->getPosition()));
		timer = MAX_TIMER;

	}
	if (!agent->blackBoard->GetPlayerInSight())
	{
		delete newState;
		newState = new Patrol();
		return newState;
	}
	else if (agent->blackBoard->GetPlayerHasGun())
	{
		delete newState;
		newState = new Evade();
		return newState;
	}

	return nullptr;
}

void Chase::Enter(Agent* agent, float dtime)
{
	agent->ChooseNewGoal(pix2cell(agent->sensors->scene->player->getPosition()));
	timer = MAX_TIMER;
}

void Chase::Exit(Agent* agent, float dtime)
{
	agent->blackBoard->graph.ResetAllWeights();
}