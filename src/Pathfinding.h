#pragma once
#include "Path.h"
#include "Graph.h"

class Pathfinding
{
protected:
	void GetPath(Path&, Vector2D, Graph::Node*);
	int count;
	//We use Octile diagonal distance
	const float D = 1;
	const float D2 = sqrt(2);
public:
	Pathfinding();
	~Pathfinding();
	virtual void CalculatePath(Graph, Path&, Vector2D, Vector2D) = 0;
	float Heuristic(Vector2D node, Vector2D goal);
};