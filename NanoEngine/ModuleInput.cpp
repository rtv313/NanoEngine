#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCameraEditor.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouse({0, 0}), mouse_motion({0,0})
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	RELEASE_ARRAY(keyboard);
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG_GLOBALS("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG_GLOBALS("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool ModuleInput::Start()
{
	return true;
}

// Called each loop iteration
update_status ModuleInput::PreUpdate()
{
	static SDL_Event event;
	float cameraSpeed, cameraRotSpeed;
	mouse_motion = {0, 0};
	memset(windowEvents, false, WE_COUNT * sizeof(bool));
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		// Camera Inputs
		cameraSpeed = App->cameraEditor->moveSpeed;
				// Elevate
				if (keys[SDL_SCANCODE_Q]) {
					App->cameraEditor->position.y += cameraSpeed*App->dt;
					App->cameraEditor->lookAt.y += cameraSpeed*App->dt;
				}
				//Descend
				if (keys[SDL_SCANCODE_E]) {
					App->cameraEditor->position.y -= cameraSpeed*App->dt;
					App->cameraEditor->lookAt.y -= cameraSpeed*App->dt;
				}
				//Forward
				if (keys[SDL_SCANCODE_W]) {
					App->cameraEditor->position +=App->cameraEditor->forward.Normalized()*cameraSpeed*App->dt;
					App->cameraEditor->lookAt += App->cameraEditor->forward.Normalized()*cameraSpeed*App->dt;
				}
				//Backwards
				if (keys[SDL_SCANCODE_S]) {
					App->cameraEditor->position -= App->cameraEditor->forward.Normalized()*cameraSpeed*App->dt;
					App->cameraEditor->lookAt -= App->cameraEditor->forward.Normalized()*cameraSpeed*App->dt;
				}
				//Strafe Left
				if (keys[SDL_SCANCODE_A]) {
					App->cameraEditor->position -= App->cameraEditor->right.Normalized()*cameraSpeed*App->dt;
					App->cameraEditor->lookAt -= App->cameraEditor->right.Normalized()*cameraSpeed*App->dt;
				}
				//Strafe Right
				if (keys[SDL_SCANCODE_D]) {
					App->cameraEditor->position += App->cameraEditor->right.Normalized()*cameraSpeed*App->dt;
					App->cameraEditor->lookAt += App->cameraEditor->right.Normalized()*cameraSpeed*App->dt;
				}
				cameraRotSpeed = App->cameraEditor->rotationSpeed;
				//Rotate Left
				if (keys[SDL_SCANCODE_Z]) {

					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;
					App->cameraEditor->forward = App->cameraEditor->forward.Lerp(App->cameraEditor->right*-1, cameraRotSpeed*App->dt);
					App->cameraEditor->right = App->cameraEditor->forward.Cross(App->cameraEditor->up);
					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;

				}
				//Rotate Right
				if (keys[SDL_SCANCODE_X]) {
					
					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;
					App->cameraEditor->forward=App->cameraEditor->forward.Lerp(App->cameraEditor->right, cameraRotSpeed*App->dt);
					App->cameraEditor->right = App->cameraEditor->forward.Cross(App->cameraEditor->up);
					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;

				}
				//Rotate Up
				if (keys[SDL_SCANCODE_C]) {
					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;
					float3 aux = App->cameraEditor->forward.Lerp(App->cameraEditor->up, 0.002*App->dt) - App->cameraEditor->forward;
					App->cameraEditor->forward = App->cameraEditor->forward.Lerp(App->cameraEditor->up*-1, cameraRotSpeed*App->dt);
					App->cameraEditor->up -= aux;
					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;
					

				}
				//Rotate Down
				if (keys[SDL_SCANCODE_V]) {

					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;
					float3 aux = App->cameraEditor->forward.Lerp(App->cameraEditor->up, 0.002*App->dt) - App->cameraEditor->forward;
					App->cameraEditor->forward = App->cameraEditor->forward.Lerp(App->cameraEditor->up, cameraRotSpeed*App->dt);
					App->cameraEditor->up += aux;
					App->cameraEditor->lookAt = App->cameraEditor->position + App->cameraEditor->forward;

				}
		// End Camera inputs
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
			break;

			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					// case for detect resize
					case SDL_WINDOWEVENT_SIZE_CHANGED: 
					    //App->renderer->Resize();
						App->cameraEditor->screenWidth = event.window.data1;
						App->cameraEditor->screenHeight = event.window.data2;
						LOG_GLOBALS("RESIZING");
						break;
					
					//case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;

			break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
			break;

			case SDL_MOUSEMOTION:
				mouse_motion.x = event.motion.xrel / SCREEN_SIZE;
				mouse_motion.y = event.motion.yrel / SCREEN_SIZE;
				mouse.x = event.motion.x / SCREEN_SIZE;
				mouse.y = event.motion.y / SCREEN_SIZE;
			break;

		}
	}

	if(GetWindowEvent(EventWindow::WE_QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG_GLOBALS("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool ModuleInput::GetWindowEvent(EventWindow ev) const
{
	return windowEvents[ev];
}

const iPoint& ModuleInput::GetMousePosition() const
{
	return mouse;
}

const iPoint& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}