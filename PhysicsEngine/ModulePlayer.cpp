#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		if (ang > 0)
			ang--;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		if (ang < 90)
			ang++;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		App->physics->CreateBall(x, y, 10, v, ang);
	}
	return UPDATE_CONTINUE;
}


update_status ModulePlayer::PostUpdate()
{

	return UPDATE_CONTINUE;
}