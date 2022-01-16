#pragma once
#include <vector>
#include "SDL_SimpleApp.h"

class Graph
{
private:
	void AddAllNeighbours();

public:
	Graph();
	Graph(std::vector<std::vector<int>>);
	void ResetAllWeights();
	void ChangeWeights(Vector2D position, float, float,float);

	struct Node {
		Vector2D position;
		float weight, heuristic, priority;
		std::vector<Node*> neighbours;
		Node* cameFrom; //parent node
		int costSoFar; // cost so far for each node
		bool isValid;
		Node(Vector2D cellPos, float _weight) : weight(_weight)
		{
			position = Vector2D::cell2pix(cellPos);
			isValid = weight != 0;
			cameFrom = nullptr;
			costSoFar = 0;
			heuristic = priority = 0;
		}
		void ChangeWeightRecursive(float newWeight, float decreaseStrength, float minimumValue)
		{
			if (newWeight >= minimumValue)
			{
				weight = newWeight;

				for each (Node * neighbour in neighbours)
				{
					if (neighbour->cameFrom != nullptr)
					{
						neighbour->cameFrom = this;
						neighbour->ChangeWeightRecursive(newWeight - decreaseStrength, decreaseStrength, minimumValue);
					}
				}
			}
		}	
	};

	std::vector<std::vector<Node*>> nodes;	
};