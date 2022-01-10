#pragma once
#include <unordered_map>
#include <string>
#include "Graph.h"

class Blackboard
{
private:
	Graph graph;
	std::unordered_map<std::string, void*> blackboard;

	float seeDistance; // also for cone
	float coneAngle;

public:
	Blackboard(Graph);
	~Blackboard();

	//SETTERS
	void setSeeDistance(float _newSeeDistance) { seeDistance = _newSeeDistance; }
	void setConeAngle(float _newConeAngle) { coneAngle = _newConeAngle; }

	//GETTERS
	float GetSeeDistance() const { return seeDistance; }
	float GetConeAngle() const { return coneAngle; }
};