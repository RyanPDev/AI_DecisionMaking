#pragma once
#include "Grid.h"
#include "Graph.h"
#include "Scene.h"

class SensorySystemScene :
	public Scene
{
public:
	SensorySystemScene();
	~SensorySystemScene();
	Grid* maze;

	void ReplaceGunPosition();
	void update(float dtime, SDL_Event* event);
	void draw();
	void DrawGun(bool playerHasIt);
	const char* getTitle();
	
private:
	const int NUM_AGENTS = 2;
	bool draw_grid;
	Graph enemyGraph;
	Graph playerGraph;
	Vector2D gunPosition;
	SDL_Texture* background_texture;
	SDL_Texture* gun_texture;

	void drawMaze();
	bool loadTextures(char* filename_bg, char* filename_gun);
};