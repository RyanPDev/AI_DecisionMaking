#include "SensorySystem.h"
#include "CoinBattleScene.h"
#include <iostream>
#include "utils.h"

using namespace Vector2DUtils;


SensorySystem::SensorySystem(Scene* _scene) : scene(_scene)
{
}

SensorySystem::~SensorySystem()
{
}

void SensorySystem::Update(Agent* agent, float dTime)
{
	// Calculate Distance between scene player and agent
	if (Vector2D::Distance(scene->player->getPosition(), agent->getPosition()) < agent->blackBoard->GetSeeDistance()) 
	{
		if (Vector2DUtils::IsInsideCone(scene->player->getPosition(),
			agent->getPosition(),
			agent->getPosition() + (Vector2D::Normalize(agent->getVelocity())) * agent->blackBoard->GetSeeDistance(),
			agent->blackBoard->GetConeHalfAngle())) // Calculate if scene player inside cone
		{
			if (LineTrace(agent)) // Calculate if there is no wall between the scene player and agent
			{
				agent->blackBoard->SetPlayerInSight(true);
				agent->blackBoard->SetPlayerHasGun(scene->player->blackBoard->GetPlayerHasGun());
				return;
			}
		}
	}
	// If there is no line trace conection, enemies don't see the player
	agent->blackBoard->SetPlayerInSight(false);
}
bool SensorySystem::LineTrace(Agent* agent) // Checks if can see the player
{
	Vector2D currentNode = pix2cell(agent->getPosition());
	while (pix2cell(scene->player->getPosition()) != currentNode) {
		if (agent->blackBoard->graph.nodes[currentNode.y][currentNode.x]->isValid)
		{
			float directionX = pix2cell(scene->player->getPosition()).x - currentNode.x;
			float directionY = pix2cell(scene->player->getPosition()).y - currentNode.y;

			if (directionX != 0)
				directionX > 0 ? currentNode.x++ : currentNode.x--;
			if (directionY != 0)
				directionY > 0 ? currentNode.y++ : currentNode.y--;
		}
		else
			return false; // There is a wall
	}
	return true;
}
