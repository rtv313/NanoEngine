#include "Globals.h"
#include "ModuleCameraEditor.h"



ModuleCameraEditor::ModuleCameraEditor()
{
	
	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, (GLint *)&viewPort);
	screenWidth = (GLfloat)viewPort[2];
	screenHeight = (GLfloat)viewPort[3];
	position.x = 0;
	position.y = 20;
	position.z = 2;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 0;

	forward = lookAt - position;

	zNear = 10;
	zFar = 1000;
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
	gluPerspective(50, 1, 1, 100);
	//glFrustum(position.x - 5, position.x + 5, position.y - 5, position.y + 5, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, up.x, up.y, up.z);
	forward = lookAt - position;
	//float4x4 aux = float4x4::LookAt(position, lookAt, forward, up, up);
	//aux.SetTranslatePart(position.x, position.y, position.z);
	//aux.Transpose();

	//glLoadMatrixf((const GLfloat*)&aux);
	
	
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
	
	//glRotatef(20, 1, 0, 0);
	//glLoadMatrixf((const GLfloat*)&float4x4::LookAt(forward, (lookAt - position), up, up));
	return UPDATE_CONTINUE;
}
