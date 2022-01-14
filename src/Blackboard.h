#pragma once
#include <unordered_map>
#include <string>
#include "Graph.h"

class Blackboard
{
private:

	float seeDistance; // also for cone
	float coneAngle;
	bool playerInSight,playerHasGun;


public:
	Blackboard(Graph);
	~Blackboard();
	Graph graph;

	//SETTERS
	void SetSeeDistance(float _newSeeDistance) { seeDistance = _newSeeDistance; }
	void SetConeAngle(float _newConeAngle) { coneAngle = _newConeAngle; }
	void SetPlayerInSight(bool _isInSight) { playerInSight = _isInSight; }
	void SetPlayerHasGun(bool _hasGun) { playerHasGun = _hasGun; }

	//GETTERS
	float GetSeeDistance() const { return seeDistance; }
	float GetConeAngle() const { return coneAngle; }
	float GetPlayerInSight() const { return playerInSight; }
	float GetPlayerHasGun() const { return playerHasGun; }
};