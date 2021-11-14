#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	return true;
}


update_status ModulePhysics::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update()
{
	/*
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		CreateBall(100, 700, 10, 100, 90, 5);
	}
	*/
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	p2List_item<Ball*>* current_ball = balls.getFirst();
	while (current_ball != NULL) {
		if (current_ball->data->physics_enabled) {
			ResetForces(current_ball->data);
			ComputeForces(current_ball->data);
			NewtonsLaw(current_ball->data);
			Integrator(current_ball->data);
			CollisionSolver(current_ball->data);
		}
		current_ball = current_ball->next;
	}

	DrawBalls();

	//Debug
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	//Debug options (mode debug activated)

	return UPDATE_CONTINUE;
}


bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");


	return true;
}

void ModulePhysics::ResetForces(Ball* ball) {
	ball->fx = ball->fy = 0.0;
	ball->ax = ball->ay = 0.0;
}

void ModulePhysics::ComputeForces(Ball* ball) {
	//Apply Gravity
	ball->fgx = ball->mass * GRAVITY_X;
	ball->fgy = ball->mass * GRAVITY_Y;
	ball->fx += ball->fgx;
	ball->fy += ball->fgy;

	//Apply Aerodinamic lift / drag
}

void ModulePhysics::NewtonsLaw(Ball* ball) {
	//ForceSum = m * a
	ball->ax = ball->fx / ball->mass;
	ball->ay = ball->fy / ball->mass;
}

void ModulePhysics::Integrator(Ball* ball) {
	if (integrator_type == integrators::VERLET) {
		ball->x += ball->vx * dt + 0.5 * ball->ax * dt * dt;
		ball->y += ball->vy * dt + 0.5 * ball->ay * dt * dt;
		ball->vx += ball->ax * dt;
		ball->vy += ball->ay * dt;
	}
	if (integrator_type == integrators::EULER_BACK) {

	}
	if (integrator_type == integrators::EULER_FORW) {

	}
}

void ModulePhysics::CollisionSolver(Ball* ball) {

}

void ModulePhysics::DrawBalls() {
	p2List_item<Ball*>* current_ball = balls.getFirst();
	while (current_ball != NULL) {
		App->renderer->DrawCircle(current_ball->data->x, current_ball->data->y, current_ball->data->radius, 250, 250, 250);
		current_ball = current_ball->next;
	}
}
