#pragma once
#include "Pathfinding.h"
#include "SensorySystem.h"
#include "Blackboard.h"
#include "DecisionMakingAlgorithm.h"
#include <memory>

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

	Agent(Graph, Scene*, bool _hasSensorySystem = false);
	~Agent();

	//WE USE SMART POINTERS SO MEMORY MANAGEMENT IS DONE FOR US WHEN THESE ATTRIBUTES GO OUT OF SCOPE (DESTROYED OBJECT)
	std::unique_ptr<Blackboard> blackBoard;
	std::unique_ptr<SensorySystem> sensors;

	Vector2D currentGoal;

	void update(float dtime, SDL_Event* event);
	void draw(bool);

	void ReplaceWanderPosition();
	void RecalculatePath();
	void ChooseNewGoal();
	bool loadSpriteTexture(char* filename, int num_frames = 1);
	void ChooseNewGoal(Vector2D newGoal);
	
	void setBehavior(SteeringBehavior* behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setMaxVelocity(float newVelocity);
	void setCurrentTargetIndex(int idx);
	
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();

private:
	SDL_Texture* sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	int currentTargetIndex;
	float mass;
	float orientation;
	float max_force;
	float max_velocity;
	bool hasSensorySystem;

	Path path;
	std::unique_ptr<Pathfinding> pathfinding;
	std::unique_ptr<DecisionMakingAlgorithm> brain;
	SteeringBehavior* steering_behaviour;
	Vector2D velocity;
	Vector2D target;
	Vector2D position;

	void clearPath();
	void addPathPoint(Vector2D point);
};