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

	Agent(Graph, bool, Scene*, bool _hasSensorySystem = false);
	~Agent();

	Blackboard* blackBoard;
	Pathfinding* pathfinding;
	SensorySystem* sensors;

	//std::unique_ptr<Blackboard> blackBoard;
	//std::unique_ptr<Pathfinding> pathfinding;
	//std::unique_ptr<SensorySystem> sensors;
	Vector2D currentGoal;
	Path path;

	void ReplaceWanderPosition();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior* behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void setMaxVelocity(float newVelocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	void RecalculatePath();
	void ChooseNewGoal();
	int getCurrentTargetIndex();
	int getPathSize();
	void clearPath();
	void update(float dtime, SDL_Event* event);
	void draw(bool);
	bool loadSpriteTexture(char* filename, int num_frames = 1);
	void ChooseNewGoal(Vector2D newGoal);
	bool isInVersusScene = false;
	Vector2D getPathPoint(int idx);
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();

private:
	bool hasSensorySystem;
	SteeringBehavior* steering_behaviour;
	Vector2D velocity;
	Vector2D target;

	//std::unique_ptr<DecisionMakingAlgorithm> brain;
	DecisionMakingAlgorithm* brain;

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

	Vector2D position;
};