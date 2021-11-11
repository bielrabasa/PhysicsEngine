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
		int angle;

		double x = 0;
		double y = 0;

		double v = 0;
		double vx = 0;
		double vy = 0;

		double ax = 0;
		double ay = 0;

		double fx = 0;
		double fy = 0;

		double mass = 1;

		Ball(double ix, double iy, double rad, double vel, double ang, double m){
			x = ix;
			y = iy;
			v = vel;
			mass = m;
			angle = ang;
			radius = rad;
		}

		~Ball() {

		}
	};

	float fps = 30;

	Ball CreateBall(double ix, double iy, double rad, double vel, double ang, double m) {
		Ball b(ix, iy, rad, vel, ang, m);
		return b;
	}

private:

	bool debug;
};