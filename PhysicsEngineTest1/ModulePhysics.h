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

	class Ball {
	public:
		int radius;

		double x;
		double y;

		double vx;
		double vy;

		double ax;
		double ay;

		double fx;
		double fy;

		double mass;
	};

	float fps = 30;

private:

	bool debug;
};