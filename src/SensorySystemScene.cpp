#include "SensorySystemScene.h"
#include "PathFollowing.h"
#include <iostream>
#include <string>

using namespace std;

SensorySystemScene::SensorySystemScene()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	enemyGraph = Graph(maze->terrain);
	playerGraph = Graph(maze->terrain);

	loadTextures("../res/maze.png", "../res/coin.png");
	srand((unsigned int)time(nullptr));

	//CREATES PLAYER
	player = new Agent(playerGraph, this);
	player->loadSpriteTexture("../res/soldier.png", 4);
	player->setBehavior(new PathFollowing);
	player->setTarget(Vector2D(-20, -20));

	//CREATES ENEMIES WITH SENSORY SYSTEMS
	for (int i = 0; i < NUM_AGENTS; i++)
	{
		std::string zombiePath = "../res/zombie" + std::to_string(i + 1) + ".png";

		Agent* agent = new Agent(enemyGraph, this, true);
		agent->loadSpriteTexture((char*)zombiePath.c_str(), 8);
		agent->setBehavior(new PathFollowing);
		agent->setTarget(Vector2D(-20, -20));
		agent->ReplaceWanderPosition();
		agents.push_back(agent);
	}

	Vector2D rand_cell(-1, -1);
	for (Agent* a : agents)
	{
		rand_cell = (-1, -1);
		while (!maze->isValidCell(rand_cell))
			rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

		// set agent position coords to the center of a random cell
		a->setPosition(Vector2D::cell2pix(rand_cell));
		a->ChooseNewGoal();
	}
}

SensorySystemScene::~SensorySystemScene()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	delete maze;
}

void SensorySystemScene::update(float dtime, SDL_Event* event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_G) //-->SHOW GRID
			draw_grid = !draw_grid;
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) //-->SHOW PATHS
			drawPaths = !drawPaths;
		if (event->key.keysym.scancode == SDL_SCANCODE_P)
		{
			player->blackBoard->SetPlayerHasGun(!player->blackBoard->GetPlayerHasGun());
			std::cout << "Player has a weapon = " << player->blackBoard->GetPlayerHasGun() << std::endl;
		}

		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = Vector2D::pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				player->ChooseNewGoal(cell);
			}
		}
		break;
	default:
		break;
	}
	player->update(dtime, event);

	for (Agent* a : agents)
	{
		a->update(dtime, event);
	}
}

void SensorySystemScene::draw()
{
	drawMaze();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}
	player->draw(drawPaths);
	for (Agent* a : agents)
	{
		a->draw(drawPaths);
	}
}

const char* SensorySystemScene::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void SensorySystemScene::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = Vector2D::cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
		}
	}
}

bool SensorySystemScene::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}