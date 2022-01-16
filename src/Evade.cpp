#include "Evade.h"
#include "Chase.h"
#include "Patrol.h"
#include "Agent.h"
#include "utils.h"
#include "Scene.h"

IFSMState* Evade::Update(Agent* agent, float dtime)
{
	timer -= dtime;
	if (Vector2D::Distance(cell2pix(agent->currentGoal), agent->getPosition()) < 150 ||
		Vector2D::Distance(agent->sensors->scene->player->getPosition(), agent->getPosition()) < agent->blackBoard->GetSeeDistance() * 0.6)
	{
		ChooseEscapeGoal(agent);
	}

	if (timer <= 0)
	{
		timer = MAX_TIMER;

		if (!agent->blackBoard->GetPlayerInSight())
		{
			delete newState;
			newState = new Patrol();
			return newState;
		}

		if (!agent->blackBoard->GetPlayerHasGun())
		{
			delete newState;
			newState = new Chase();
			return newState;
		}
	}
	return nullptr;
}

void Evade::Enter(Agent* agent, float dtime)
{
	timer = 0;
	agent->setMaxVelocity(280); //Increments movement speed while evading

	ChooseEscapeGoal(agent);
}

void Evade::ChooseEscapeGoal(Agent* agent)
{
	Vector2D a;
	Vector2D b;

	agent->blackBoard->graph.ChangeWeights(agent->sensors->scene->player->getPosition(), 100000, 20000, 10000);
	int counter = 0;
	do
	{
		agent->ReplaceWanderPosition();
		counter++;
		a = Vector2D::Normalize(cell2pix(agent->currentGoal) - agent->getPosition());
		b = Vector2D::Normalize(agent->sensors->scene->player->getPosition() - agent->getPosition());
	} while (Vector2D::Dot(a, b) > 0.5 && counter < 30);

	agent->RecalculatePath();

	if (counter >= 30)
		agent->ChooseNewGoal();
}

void Evade::Exit(Agent* agent, float dtime)
{
	agent->setMaxVelocity(180); //Reset to default speed after evading successfully
}