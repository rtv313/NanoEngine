#include "Globals.h"
#include "ModuleCameraEditor.h"



ModuleCameraEditor::ModuleCameraEditor()
{
	
	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, (GLint *)&viewPort);
	screenWidth = (GLfloat)viewPort[2];
	screenHeight = (GLfloat)viewPort[3];
	position.x = 0;
	position.y = 0.5;
	position.z = 0;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 0;

	zNear = 1;
	zFar = 100;
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
	//gluPerspective(60.0, screenWidth / screenHeight, 1.0, 100.0);
	glFrustum(position.x - 1, position.x + 1, position.y - 1, position.y + 1, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glFrustrum(position.x, position.y,position.z, lookAt.x,lookAt.y, lookAt.z, up.x, up.y, up.z);
	
	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::Update() {
	return UPDATE_CONTINUE;
}

update_status ModuleCameraEditor::PostUpdate() {
	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(position.x - 1, position.x + 1, position.y - 1, position.y + 1, zNear, zFar);
	return UPDATE_CONTINUE;
}
