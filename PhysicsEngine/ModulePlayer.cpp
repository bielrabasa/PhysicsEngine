#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "SString.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	cannon_texture = App->textures->Load("Assets/cannon.png");
	cannon_base_texture = App->textures->Load("Assets/cannon_base.png");

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
			ang -= 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		if (ang < 90)
			ang += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) {
		//for(int i=0;i<100;i++)		//Prova per matar les fisiques
		App->physics->CreateBall(x + 32, y + 32, 16, v, ang, 4, 0.8);
	}

	return UPDATE_CONTINUE;
}


update_status ModulePlayer::PostUpdate()
{
	App->renderer->Blit(cannon_texture, x, y, NULL, 4, 1.0f, -ang + 90, 32, 32);
	App->renderer->Blit(cannon_base_texture, x, y + 40, NULL, 4);

	SString changing_title(TITLE "  ____  Angle: %i _ Velocity: %.2lf", ang, v);
	App->window->SetTitle(changing_title.GetString());
	return UPDATE_CONTINUE;
}