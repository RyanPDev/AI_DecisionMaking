#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "SensorySystemScene.h"

using namespace std;

int main(int argc, char** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp* app = SDL_SimpleApp::Instance();

	Scene* curr_scene = new SensorySystemScene;
	app->setWindowTitle(curr_scene->getTitle());

	if (argc > 1) {
		cout << argv[1] << endl;
		exit(0);
	}

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) // quit
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			delete curr_scene;
			break;
		}
	}
	return 0;
}