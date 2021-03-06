#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Vector2D.h"

class Grid
{
public:
	Grid(char* filename);

private:
	int num_cell_x;
	int num_cell_y;

public:
	
	std::vector< std::vector<int> > terrain;
	int getNumCellX();
	int getNumCellY();
	bool isValidCell(Vector2D cell);
};