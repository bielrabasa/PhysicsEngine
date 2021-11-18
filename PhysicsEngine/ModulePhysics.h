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
		double cr = 0;	//restitution coeficient
		double cf = 0;	//friction coeficient

		bool physics_enabled = true;

		Ball(double x, double y, int radius, double v, int angle, double mass, double cr) {
			this->x = x;
			this->y = y;
			this->vx = v * cos(-angle * DEGTORAD);
			this->vy = v * sin(-angle * DEGTORAD);
			this->mass = mass;
			this->radius = radius;
			this->cr = cr;
		}
		~Ball() {
		}
	};

	class Collider {
	public:
		SDL_Rect rect = { 0, 0, 0, 0 };
		int r = 0;
		bool rectangle = true;
		Collider(SDL_Rect rect, int r, bool rectangle) {
			this->rect = rect;
			this->rectangle = rectangle;
			this->r = r;
		}
		~Collider() {
		}
	};

	float dt = 1.0f / FPS;

	p2List<Ball*> balls;
	p2List<Collider*> colliders;

	//crea una bola i la posa a la llista
	Ball* CreateBall(double x, double y, int radius, double v = 0, int angle = 0, double mass = 1, double cr = 0) {
		Ball* b = new Ball(x, y, radius, v, angle, mass, cr);
		balls.add(b);
		return b;
	}

	Collider* CreateRectangleCollider(int x, int y, int w, int h) {
		Collider* c = new Collider({ x, y, w, h }, 0, true);
		colliders.add(c);
		return c;
	}
	Collider* CreateCircleCollider(int x, int y, int r) {
		Collider* c = new Collider({ x, y, 0, 0 }, r, false);
		colliders.add(c);
		return c;
	}

private:
	void DrawBalls();
	void DeleteBalls();
	void DrawColliders();

	void ResetForces(Ball*);
	void ComputeForces(Ball*);
	void NewtonsLaw(Ball*);
	void Integrator(Ball*);
	void CollisionSolver(Ball*);
	
	bool debug;
	enum class integrators{ VERLET, EULER_BACK, EULER_FORW }integrator_type = integrators::VERLET;
	SDL_Texture* cannon_ball_texture = nullptr;
};