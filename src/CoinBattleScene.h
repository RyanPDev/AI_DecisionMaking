#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
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

private:
	Grid* maze;
	Graph graph; //--> GOES TO BLACKBOARD
	bool draw_grid;
	int count = 1;
	//Agent player;
	const int NUM_AGENTS = 2;
	const int MAX_COINS = 5;
	const float evasiveDistance = 64;


	void drawMaze();
	void drawCoin();
	void ReplaceCoinPosition(Vector2D&);
	std::vector<Vector2D*> coinsPosition;
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
};