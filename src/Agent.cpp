#include <iostream>
#include "Agent.h"
#include "FSM.h"
#include "SDL_SimpleApp.h"
#include "ModifiedAStar.h"
#include "utils.h"

using namespace std;

Agent::Agent(Graph _graph, Scene* _scene, bool _implementsSensorySystem) : sprite_texture(0),
position(Vector2D(100, 100)),
target(Vector2D(1000, 100)),
velocity(Vector2D(0, 0)),
currentTargetIndex(-1),
mass(0.1f),
max_force(150),
max_velocity(200),
orientation(0),
sprite_num_frames(0),
sprite_w(0),
sprite_h(0),
draw_sprite(false),
hasSensorySystem(_implementsSensorySystem)
{
	blackBoard = std::unique_ptr<Blackboard>(new Blackboard(_graph));
	pathfinding = std::unique_ptr<ModifiedAStar>(new ModifiedAStar());

	//IF AGENT HAS A SENSORY SYSTEM, ADD HIM SENSORS AND BRAIN AND SET THEM LOWER SPEED
	if (hasSensorySystem)
	{
		max_velocity = 180;
		sensors = std::unique_ptr<SensorySystem>(new SensorySystem(_scene));
		brain = std::unique_ptr<FSM>(new FSM(this));
	}
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);

	if (steering_behaviour)
		delete steering_behaviour;
}

void Agent::setBehavior(SteeringBehavior* behavior)
{
	steering_behaviour = behavior;
}

//SET A VALID POSITION FOR THE AGENT TO WANDER TO
void Agent::ReplaceWanderPosition()
{
	int num_cell_x = SRC_WIDTH / CELL_SIZE;
	int num_cell_y = SRC_HEIGHT / CELL_SIZE;

	do {
		currentGoal = Vector2D((float)(rand() % num_cell_x), (float)(rand() % num_cell_y));
	} while (!blackBoard->graph.nodes[currentGoal.y][currentGoal.x]->isValid || (Vector2D::Distance(currentGoal, Vector2D::pix2cell(getPosition())) < 3));
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::setMaxVelocity(float newVelocity)
{
	max_velocity = newVelocity;
}

void Agent::update(float dtime, SDL_Event* event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}
	if (hasSensorySystem) // this will not happen with the player
	{
		sensors->Update(this, dtime);
		brain->Update(this, dtime);
	}

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);

	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::addPathPoint(Vector2D point)
{
	if (path.points.size() > 0)
		if (path.points[path.points.size() - 1] == point)
			return;

	path.points.push_back(point);
}

int Agent::getCurrentTargetIndex()
{
	return currentTargetIndex;
}

int Agent::getPathSize()
{
	return path.points.size();
}

Vector2D Agent::getPathPoint(int idx)
{
	return path.points[idx];
}

void Agent::clearPath()
{
	setCurrentTargetIndex(-1);
	path.points.clear();
}

void Agent::setCurrentTargetIndex(int idx)
{
	currentTargetIndex = idx;
}

void Agent::RecalculatePath()
{
	Vector2D start;
	if (currentTargetIndex >= 0)
		start = getPathPoint(currentTargetIndex);
	else
		start = position;

	clearPath();
	pathfinding->CalculatePath(blackBoard->graph, path, start, currentGoal);
}

void Agent::ChooseNewGoal() // Updates current goal to a random valid goal
{
	ReplaceWanderPosition();
	Vector2D start;
	if (currentTargetIndex >= 0)
		start = getPathPoint(currentTargetIndex);
	else
		start = position;

	clearPath();
	pathfinding->CalculatePath(blackBoard->graph, path, start, currentGoal);
}

void Agent::ChooseNewGoal(Vector2D newGoal) // Updates current goal to specific location
{
	currentGoal = newGoal;
	Vector2D start;
	if (currentTargetIndex >= 0)
		start = getPathPoint(currentTargetIndex);
	else
		start = position;

	clearPath();
	pathfinding->CalculatePath(blackBoard->graph, path, start, currentGoal);
}

void Agent::draw(bool drawCircles)
{
	// Path
	if (drawCircles)
		for (int i = 0; i < (int)path.points.size(); i++)
		{
			draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, 255, 255, 0, 255);
			if (i > 0)
				SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
		}

	if (draw_sprite)
	{
		Uint32 sprite;

		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1 * velocity.Length() + 250)) % sprite_num_frames;

		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation + 90, &center, SDL_FLIP_NONE);
	}
	else
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x + 15 * cos(orientation * DEG2RAD)), (int)(position.y + 15 * sin(orientation * DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface* image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}