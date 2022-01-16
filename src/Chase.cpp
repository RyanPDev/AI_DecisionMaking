#include "Chase.h"
#include "Patrol.h"
#include "Agent.h"
#include "Evade.h"
#include "Scene.h"

IFSMState* Chase::Update(Agent* agent, float dtime)
{
	timer -= dtime;

	//UPDATE PLAYER POSITION TO CHASE EVERY 0.5s INSTEAD OF EVERY FRAME TO SAVE PERFORMANCE
	if (timer <= 0)
	{
		ChooseNewGoal(agent);
		timer = MAX_TIMER;
	}

	//IF PLAYER NOT IN SIGHT, CHANGE BACK TO PATROL STATE
	if (!agent->blackBoard->GetPlayerInSight())
	{
		delete newState;
		newState = new Patrol();
		return newState;
	}

	//IF WHILE CHASING PLAYER HAS A GUN, CHANGE TO EVADE STATE
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
	ChooseNewGoal(agent);
	timer = MAX_TIMER;
}

void Chase::Exit(Agent* agent, float dtime)
{
	agent->blackBoard->graph.ResetAllWeights();
}

void Chase::ChooseNewGoal(Agent* agent)
{
	agent->ChooseNewGoal(Vector2D::pix2cell(agent->sensors->scene->player->getPosition()));
}