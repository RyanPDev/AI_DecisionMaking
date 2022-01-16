#include "Patrol.h"
#include "Agent.h"
#include "Scene.h"
#include "Chase.h"

IFSMState* Patrol::Update(Agent* agent, float dtime)
{
	int i = 0;
	if (agent->sensors->scene->agents[0] == agent) i = 1;

	//Checks distance between agents. If they're close enough, start modifiying weights around them so they AVOID each other
	if (Vector2D::Distance(agent->getPosition(), agent->sensors->scene->agents[i]->getPosition()) < agent->blackBoard->GetEvasiveDistance())
	{		
		agent->blackBoard->graph.ResetAllWeights();
		agent->blackBoard->graph.ChangeWeights(agent->sensors->scene->agents[i]->getPosition(), 100000, 20000, 10000);
		ChooseNewGoal(agent);
	}

	//IF AGENT REACHES GOAL, UPDATE NEW GOAL POSITION
	if (Vector2D::pix2cell(agent->getPosition()) == agent->currentGoal)
	{
		ChooseNewGoal(agent);
		agent->blackBoard->graph.ResetAllWeights();
	}

	//IF AGENT HAS PLAYER IN SIGHT IN ITS BLACKBOARD, CHANGE TO CHASE STATE
	if (agent->blackBoard->GetPlayerInSight())
	{
		delete newState;
		newState = new Chase();
		return newState;
	}

	return nullptr;
}

//CALCULATE NEW GOAL IN A SIMILAR DIRECTION WHERE THE AGENT WAS GOING WITH A DOT PRODUCT
//SO IT MANTAINS CERTAIN REALISM AND DOESNT TURN BACK 180º AS IT WOULD BE AWKWARD
void Patrol::ChooseNewGoal(Agent* agent)
{
	Vector2D a;
	Vector2D b;
	int counter = 0;
	b = Vector2D::Normalize(agent->getVelocity());
	do
	{
		agent->ReplaceWanderPosition();
		a = Vector2D::Normalize(agent->currentGoal - Vector2D::pix2cell(agent->getPosition()));
		counter++;
	} while (Vector2D::Dot(a, b) < 0 && counter < 30);

	agent->RecalculatePath();

	if (counter >= 30)
	{
		agent->ChooseNewGoal(); //--> Chooses random new Goal if within 30 tries cannot find a better one
	}
}

void Patrol::Enter(Agent* agent, float dtime)
{
	agent->blackBoard->graph.ResetAllWeights();
}

void Patrol::Exit(Agent* agent, float dtime)
{
	agent->blackBoard->graph.ResetAllWeights();
}