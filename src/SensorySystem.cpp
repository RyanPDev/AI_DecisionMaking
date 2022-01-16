#include "SensorySystem.h"
#include "SensorySystemScene.h"
#include <iostream>

using namespace Vector2DUtils;

SensorySystem::SensorySystem(Scene* _scene) : scene(_scene) {}

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
				// When the agent sees the player it checks if it has a gun
				agent->blackBoard->SetPlayerHasGun(scene->player->blackBoard->GetPlayerHasGun()); 
			}
		}
	}
	else
	{
		agent->blackBoard->SetPlayerInSight(false);
	}
}

//LINE TRACE BETWEEN THIS AGENT AND THE PLAYER THAT CHECKS IF THERE ARE WALLS BETWEEN THEM
//IF THERE ARE WALLS, LINE TRACE RETURNS FALSE
bool SensorySystem::LineTrace(Agent* agent) // Checks if can see the player
{
	Vector2D currentNode = Vector2D::pix2cell(agent->getPosition());
	while (Vector2D::pix2cell(scene->player->getPosition()) != currentNode) { // finds a straight "path" until it hits a wall or the player
		if (agent->blackBoard->graph.nodes[currentNode.y][currentNode.x]->isValid)
		{
			float directionX = Vector2D::pix2cell(scene->player->getPosition()).x - currentNode.x;
			float directionY = Vector2D::pix2cell(scene->player->getPosition()).y - currentNode.y;

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