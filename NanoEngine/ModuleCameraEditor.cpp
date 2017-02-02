#include "Globals.h"
#include "ModuleCameraEditor.h"



ModuleCameraEditor::ModuleCameraEditor()
{
	
	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, (GLint *)&viewPort);
	screenWidth = (GLfloat)viewPort[2];
	screenHeight = (GLfloat)viewPort[3];
	position.x = 2;
	position.y = 3;
	position.z = 5;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 0;


}


ModuleCameraEditor::~ModuleCameraEditor()
{
}

void ModuleCameraEditor::setFOV() {

}

void ModuleCameraEditor::setAspectRatio() {

}

void ModuleCameraEditor::setPlaneDistances() {
}

void ModuleCameraEditor::getProjectionMatrix() {
}

void ModuleCameraEditor::getViewMatrix() {

}

update_status ModuleCameraEditor::PreUpdate() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, screenWidth / screenHeight, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y,position.z, lookAt.x,lookAt.y, lookAt.z, up.x, up.y, up.z);

	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::Update() {
	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::PostUpdate() {
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, screenWidth / screenHeight, 1.0, 100.0);

	return UPDATE_CONTINUE;
}
