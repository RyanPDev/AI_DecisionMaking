#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(std::vector<std::vector<int>> terrain)
{
	std::vector<Node*> aux;
	// We traverse the file to get the weights
	for (int i = 0; i < terrain.size(); i++)
	{
		for (int j = 0; j < terrain[i].size(); j++)
		{
			Node* n = new Node({ (float)j, (float)i }, terrain[i][j]);
			aux.push_back(n);
		}
		nodes.push_back(aux);
		aux.clear();
	}
	AddAllNeighbours();
}

void Graph::ResetAllWeights() // Resets weights to their original state
{
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i].size(); j++)
		{
			if (nodes[i][j]->isValid)
				nodes[i][j]->weight = 2;
		}
	}
}

void Graph::ChangeWeights(Vector2D position, float maxValue, float decreaseStrength, float minimumValue)
{
	// Gets the other agent position and then expands recursively changing the vale with a decrease in each iteration untill it reaches a minimum value
	position = Vector2D::pix2cell(position);
	if (nodes[position.y][position.x] != nullptr && nodes[position.y][position.x]->isValid)
	{
		nodes[position.y][position.x]->cameFrom = nodes[position.y][position.x];
		nodes[position.y][position.x]->ChangeWeightRecursive(maxValue, decreaseStrength, minimumValue);
	}
}

void Graph::AddAllNeighbours()
{
	for (int i = 0; i < nodes.size(); i++)
		for (int j = 0; j < nodes[i].size(); j++)
		{
			if (nodes[i][j]->isValid) // the node is not wall
			{
				// 8 directions
				if ((j - 1) >= 0 && nodes[i][j - 1]->isValid) // left neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i][j - 1]);
				}

				if ((j + 1) < nodes[0].size() && nodes[i][j + 1]->isValid) // right neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i][j + 1]);
				}
				if ((i - 1) >= 0 && nodes[i - 1][j]->isValid) // up neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i - 1][j]);
					if ((j - 1) >= 0 && nodes[i - 1][j - 1]->isValid) // up left neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i - 1][j - 1]);
					}

					if ((j + 1) < nodes[0].size() && nodes[i - 1][j + 1]->isValid) // up right neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i - 1][j + 1]);
					}
				}

				if ((i + 1) < nodes.size() && nodes[i + 1][j]->isValid) // down neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i + 1][j]);
					if ((j - 1) >= 0 && nodes[i + 1][j - 1]->isValid) // down left neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i + 1][j - 1]);
					}

					if ((j + 1) < nodes[0].size() && nodes[i + 1][j + 1]->isValid) // down right neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i + 1][j + 1]);
					}
				}

			}
		}
}