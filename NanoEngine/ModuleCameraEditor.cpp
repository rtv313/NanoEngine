#include "Application.h"
#include "Globals.h"
#include "ModuleCameraEditor.h"
#include "ModuleWindow.h"




ModuleCameraEditor::ModuleCameraEditor()
{
	
	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, (GLint *)&viewPort);
	screenWidth = (GLfloat)viewPort[2];
	screenHeight = (GLfloat)viewPort[3];
	position.x = 0;
	position.y = 5;
	position.z = 10;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 0;

	forward = lookAt - position;

	zNear = 10;
	zFar = 1000;
	moveSpeed = 6.0;
	rotationSpeed = 3.0;
	right = forward.Cross(up);
}


ModuleCameraEditor::~ModuleCameraEditor()
{
}

void ModuleCameraEditor::setFOV() {

}

void ModuleCameraEditor::setAspectRatio() {

}

void ModuleCameraEditor::setPlaneDistances(GLfloat zNear, GLfloat zFar) {
	this->zNear = zNear;
	this->zFar = zFar;
}

void ModuleCameraEditor::getProjectionMatrix() {
}

void ModuleCameraEditor::getViewMatrix() {

}

update_status ModuleCameraEditor::PreUpdate() {
	dt = 0.01;
	 
	iPoint mouseNewPosition = App->input->GetMousePosition();
	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		if (mouseNewPosition.y < mousePosition.y)  //Rotate down
		{
			lookAt = position + forward;
			float3 aux = forward.Lerp(up, 0.002*dt) - forward;
			forward = forward.Lerp(up*-1, rotationSpeed*dt);
			up -= aux;
			lookAt = position + forward;
		}

		if (mouseNewPosition.y > mousePosition.y)  // Rotate up
		{
			lookAt = position + forward;
			float3 aux = forward.Lerp(up, 0.002*dt) - forward;
			forward = forward.Lerp(up, rotationSpeed*dt);
			up += aux;
			lookAt = position + forward;
		}

		if (mouseNewPosition.x < mousePosition.x)  //Rotate right
		{
			lookAt = position + forward;
			forward = forward.Lerp(right, rotationSpeed*dt);
			right = forward.Cross(up);
			lookAt = position + forward;
		}

		if (mouseNewPosition.x > mousePosition.x)  //Rotate left
		{
			lookAt = position + forward;
			forward = forward.Lerp(right*-1, rotationSpeed*dt);
			right = forward.Cross(up);
			lookAt = position + forward;
		}
	}
		// Camera Inputs
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		moveSpeed;
		// Elevate
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) {
			position.y += moveSpeed*dt;
			lookAt.y += moveSpeed*dt;
		}
		//Descend
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) {
			position.y -= moveSpeed*dt;
			lookAt.y -= moveSpeed*dt;
		}
		//Forward
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			position += forward.Normalized()*moveSpeed*dt;
			lookAt += forward.Normalized()*moveSpeed*dt;
		}
		//Backwards
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			position -= forward.Normalized()*moveSpeed*dt;
			lookAt -= forward.Normalized()*moveSpeed*dt;
		}
		//Strafe Left
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			position -= right.Normalized()*moveSpeed*dt;
			lookAt -= right.Normalized()*moveSpeed*dt;
		}
		//Strafe Right
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			position += right.Normalized()*moveSpeed*dt;
			lookAt += right.Normalized()*moveSpeed*dt;
		}

		// End Camera inputs
		mousePosition = mouseNewPosition;
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int width,height;
	SDL_GetWindowSize(App->window->window,&width,&height);
	gluPerspective(60 ,(GLfloat)width/ height, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, up.x, up.y, up.z);
	forward = lookAt - position;
	right = forward.Cross(up);


	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::Update() {
	forward = forward.Normalized();
	right = right.Normalized();
	up = up.Normalized();
	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::PostUpdate() {
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(position.x - 1, position.x + 1, position.y - 1, position.y + 1, zNear, zFar);
	return UPDATE_CONTINUE;
}
