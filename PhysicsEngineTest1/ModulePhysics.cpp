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

	balls.add(CreateBall(100, 100, 50));
	balls.add(CreateBall(200, 50, 10));

	return true;
}


update_status ModulePhysics::PreUpdate()
{
	return UPDATE_CONTINUE;
}


update_status ModulePhysics::PostUpdate()
{
	App->renderer->DrawCircle(balls.getLast()->data->x, balls.getLast()->data->y, balls.getLast()->data->radius, 250, 250, 250);

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	//Debug options

	return UPDATE_CONTINUE;
}


bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");


	return true;
}
