#include "Blackboard.h"

Blackboard::Blackboard(Graph _graph) : graph(_graph)
{
	seeDistance = 200; // also for cone
	coneHalfAngle = 45;
	playerInSight = false;
	playerHasGun = false;
}