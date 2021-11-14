#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	double x = 50;
	double y = 620;
	int ang = 0;
	double v = 100;
	SDL_Texture* cannon_texture = nullptr;
	SDL_Texture* cannon_base_texture = nullptr;
};