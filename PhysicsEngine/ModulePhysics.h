#pragma once
#include "Module.h"
#include "Globals.h"

#define FPS 30
#define GRAVITY_X 0
#define GRAVITY_Y 10

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	class Ball {
	public:
		int radius;

		double x = 0;
		double y = 0;

		double vx = 0;
		double vy = 0;

		double ax = 0;
		double ay = 0;

		double fx = 0;
		double fy = 0;

		double fgx = 0;
		double fgy = 0;

		double mass = 1;
		double rc = 0;	//restitution coeficient
		double dc = 0;	//drag coeficient

		bool physics_enabled = true;

		Ball(double x, double y, int radius, double v, int angle, double mass, double rc) {
			this->x = x;
			this->y = y;
			this->vx = v * cos(-angle * DEGTORAD);
			this->vy = v * sin(-angle * DEGTORAD);
			this->mass = mass;
			this->radius = radius;
			this->rc = rc;
		}
		~Ball() {
		}
	};

	float dt = 1.0f / FPS;

	p2List<Ball*> balls;

	//crea una bola i la posa a la llista
	Ball* CreateBall(double x, double y, int radius, double v = 0, int angle = 0, double mass = 1, double rc = 0) {
		Ball* b = new Ball(x, y, radius, v, angle, mass, rc);
		balls.add(b);
		return b;
	}

private:
	void DrawBalls();
	void DeleteBalls();

	void ResetForces(Ball*);
	void ComputeForces(Ball*);
	void NewtonsLaw(Ball*);
	void Integrator(Ball*);
	void CollisionSolver(Ball*);
	
	bool debug;
	enum class integrators{ VERLET, EULER_BACK, EULER_FORW }integrator_type = integrators::VERLET;
	SDL_Texture* cannon_ball_texture = nullptr;
};