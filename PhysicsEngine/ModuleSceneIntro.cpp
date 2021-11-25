#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	//Colliders
	App->physics->CreateRectangleCollider(0, floor, 1024, 60);
	App->physics->CreateRectangleCollider(700, 400, 50, 300);
	App->physics->CreateRectangleCollider(300, 600, 50, 100);
	//App->physics->CreateRectangleCollider(100, 300, 100, 100);
	//App->physics->CreateCircleCollider(725, 320, 100);
	App->physics->CreateCircleCollider(500, 500, 100);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	SDL_Rect floor_rect = { 0, floor, 1024, 60 };
	App->renderer->DrawQuad(floor_rect, 0, 200, 250);

	return UPDATE_CONTINUE;
}