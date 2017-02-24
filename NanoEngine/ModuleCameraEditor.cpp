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
	moveSpeed = 0.1;
	rotationSpeed = 0.002;
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
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_LSHIFT]|| keys[SDL_SCANCODE_RSHIFT]) {
		moveSpeed = 0.2;
		rotationSpeed = 0.004;
	}
	else {
		moveSpeed = 0.1;
		rotationSpeed = 0.002;
	}
	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::PostUpdate() {
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(position.x - 1, position.x + 1, position.y - 1, position.y + 1, zNear, zFar);
	
	//glRotatef(20, 1, 0, 0);
	//glLoadMatrixf((const GLfloat*)&float4x4::LookAt(forward, (lookAt - position), up, up));
	return UPDATE_CONTINUE;
}
