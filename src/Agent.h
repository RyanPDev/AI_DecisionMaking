#pragma once
#include "Pathfinding.h"
#include "SensorySystem.h"
#include "Blackboard.h"
#include "DecisionMakingAlgorithm.h"

class Scene;

class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent* agent, float dtime) {};
	};
	Pathfinding* pathfinding;
	Vector2D* currentGoal;
	SensorySystem *sensors;

private:
	SteeringBehavior* steering_behaviour;
	Vector2D velocity;
	Vector2D target;
	bool hasSensorySystem;
	DecisionMakingAlgorithm* brain;

	Vector2D* wanderPosition;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture* sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;
	Vector2D cell2pix(Vector2D cell)
	{
		int offset = CELL_SIZE / 2;
		return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
	}

	Vector2D position;
public:
	Agent(Graph,bool, Scene*, bool _hasSensorySystem = false);
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Blackboard* blackBoard;
	void ReplaceWanderPosition();
	Path path;

	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior* behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	void ChooseNewGoal();
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event* event);
	void draw(bool);
	bool loadSpriteTexture(char* filename, int num_frames = 1);
	void ChooseNewGoal(Vector2D* newGoal);
	void ChooseNewGoal(std::vector<Vector2D*> coins);
	bool isInVersusScene = false;

};