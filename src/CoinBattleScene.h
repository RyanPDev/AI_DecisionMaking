#pragma once
#include "Grid.h"
#include "Graph.h"
#include "Scene.h"

class CoinBattleScene :
	public Scene
{
public:
	CoinBattleScene();
	~CoinBattleScene();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();

	Grid* maze;
private:
	Graph graph; //--> GOES TO BLACKBOARD
	bool draw_grid;
	int count = 1;

	const int NUM_AGENTS = 2;
	const int MAX_COINS = 5;

	void drawMaze();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
};