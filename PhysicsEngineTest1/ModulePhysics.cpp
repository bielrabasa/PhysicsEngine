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

	ball* cannonball = new ball;
	
	return true;
}


update_status ModulePhysics::PreUpdate()
{


	return UPDATE_CONTINUE;
}


update_status ModulePhysics::PostUpdate()
{

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
