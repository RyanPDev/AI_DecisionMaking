#pragma once
#include "Graph.h"

class Blackboard
{
private:

	float seeDistance; // also for cone
	float coneHalfAngle;
	bool playerInSight,playerHasGun;
	const float evasiveDistance = 110;

public:
	Blackboard(Graph);

	Graph graph;

	//SETTERS
	void SetSeeDistance(float _newSeeDistance) { seeDistance = _newSeeDistance; }
	void SetConeHalfAngle(float _newConeAngle) { coneHalfAngle = _newConeAngle; }
	void SetPlayerInSight(bool _isInSight) { playerInSight = _isInSight; }
	void SetPlayerHasGun(bool _hasGun) { playerHasGun = _hasGun; }

	//GETTERS
	float GetSeeDistance() const { return seeDistance; }
	float GetConeHalfAngle() const { return coneHalfAngle; }
	bool GetPlayerInSight() const { return playerInSight; }
	float GetEvasiveDistance() const { return evasiveDistance; }
	bool GetPlayerHasGun() const { return playerHasGun; }
};