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
	cannon_ball_texture = App->textures->Load("Assets/cannon_ball.png");
	return true;
}


update_status ModulePhysics::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update()
{

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

	//DeleteBalls();
	DrawBalls();
	DrawColliders();

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
	p2List_item<Collider*>* current_collider = colliders.getFirst();
	while (current_collider != NULL) {
		if (current_collider->data->rectangle) {
			if ((ball->x + ball->radius > current_collider->data->rect.x) && 
				(ball->x - ball->radius < current_collider->data->rect.x + current_collider->data->rect.w) && 
				(ball->y + ball->radius > current_collider->data->rect.y) && 
				(ball->y - ball->radius < current_collider->data->rect.y + current_collider->data->rect.h)) {

				if ((ball->x + ball->radius > current_collider->data->rect.x) &&
					(ball->x - ball->radius < current_collider->data->rect.x + current_collider->data->rect.w) &&
					(ball->y + ball->radius - ball->vy > current_collider->data->rect.y) &&
					(ball->y - ball->radius - ball->vy < current_collider->data->rect.y + current_collider->data->rect.h)) { //Horizontal Colision

					if (ball->vx > 0) { //Right colision
						ball->x -= 2 * (ball->x - (current_collider->data->rect.x - ball->radius));
					}
					else { //Left colision
						ball->x = current_collider->data->rect.x + (-ball->x + (current_collider->data->rect.x + current_collider->data->rect.w));
					}
					ball->vy = ball->vy * ball->cr;
					ball->vx = -ball->vx * ball->cr;
				}
				else if ((ball->x + ball->radius - ball->vx > current_collider->data->rect.x) &&
					(ball->x - ball->radius - ball->vx < current_collider->data->rect.x + current_collider->data->rect.w) &&
					(ball->y + ball->radius > current_collider->data->rect.y) &&
					(ball->y - ball->radius < current_collider->data->rect.y + current_collider->data->rect.h)) { //Vertical Colision

					if (ball->vy > 0) { //Floor colision
						ball->y -= 2*(ball->y - (current_collider->data->rect.y - ball->radius));
					}
					else { //Ceiling colision
						ball->y = current_collider->data->rect.y + (-ball->y + (current_collider->data->rect.y + current_collider->data->rect.h));
					}
					ball->vy = -ball->vy * ball->cr;
					ball->vx = ball->vx * ball->cr;
				}
				else {//diagonal colision FUYM
					if (ball->vy > 0) { //floor colision
						ball->y = current_collider->data->rect.y - ball->radius;
					}
					else {	//ceiling colision
						ball->y = current_collider->data->rect.y + current_collider->data->rect.h + ball->radius;
					}

					ball->vy = -ball->vy * ball->cr;
					ball->vx = -ball->vx * ball->cr;
				}
			}
		}
		else { //CIRCLE
			double vecX = ball->x - current_collider->data->rect.x;
			double vecY = ball->y - current_collider->data->rect.y;
			double distance = sqrt(vecX * vecX + vecY * vecY);
			if (current_collider->data->r + ball->radius > distance) {	//Ball colliding ARREGLAR
				
				//unitary vector
				vecX = vecX / distance;
				vecY = vecY / distance;
																		
				//tp out
				ball->x = current_collider->data->rect.x + vecX * (current_collider->data->r + ball->radius);
				ball->y = current_collider->data->rect.y + vecY * (current_collider->data->r + ball->radius);

				//solver
				/*double aux = ball->vx;
				ball->vx += ball->vy * vecX * ball->cr;
				ball->vy += -aux * vecY * ball->cr;*/
			}
		}
		current_collider = current_collider->next;
	}
}

void ModulePhysics::DeleteBalls() {
	p2List_item<Ball*>* current_ball = balls.getFirst();
	while (current_ball != NULL) {
		if (current_ball->data->y > 700) {
			Ball* b = current_ball->data;
			current_ball = current_ball->next;
			balls.del(balls.findNode(b));
			delete b;
		}
		else {
			current_ball = current_ball->next;
		}
	}
}

void ModulePhysics::DrawBalls() {
	p2List_item<Ball*>* current_ball = balls.getFirst();
	while (current_ball != NULL) {
		//App->renderer->Blit(cannon_ball_texture, current_ball->data->x - 16, current_ball->data->y - 16, NULL, 2);
		App->renderer->DrawCircle(current_ball->data->x, current_ball->data->y, current_ball->data->radius, 250, 250, 250);
		current_ball = current_ball->next;
	}
}

void ModulePhysics::DrawColliders() {
	p2List_item<Collider*>* current_collider = colliders.getFirst();
	while (current_collider != NULL) {
		if (current_collider->data->rectangle) { //RECTANGLE
			App->renderer->DrawQuad(current_collider->data->rect, 100, 100, 100, 255, false);
		}
		else { //CIRCLE
			App->renderer->DrawCircle(current_collider->data->rect.x, 
				current_collider->data->rect.y, current_collider->data->r, 100, 100, 100);
		}
		current_collider = current_collider->next;
	}
}
