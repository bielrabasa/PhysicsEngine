#pragma once
#include "Module.h"
#include "Globals.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	struct ball {
		int radius;
		float x;
		float y;
		float velocity;
	};

private:

	bool debug;
};