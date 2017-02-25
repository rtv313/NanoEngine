#ifndef __MODULECAMERAEDITOR_H__
#define __MODULECAMERAEDITOR_H__
#include "Module.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include "SDL/include/SDL.h"
#include "ModuleInput.h"
class ModuleCameraEditor :
	public Module
{
public:
	
	float3 position,up,lookAt,forward,right;
	GLfloat fieldOfView, screenWidth, screenHeight;
	GLfloat zNear, zFar;
	float moveSpeed, rotationSpeed;
	iPoint mouseMotion;
	iPoint mousePosition;

	
ModuleCameraEditor();
	~ModuleCameraEditor();
	void setFOV();
	void setAspectRatio();
	void setPlaneDistances(GLfloat zNear, GLfloat zFar);
	void getProjectionMatrix();
	void getViewMatrix();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	Frustum frustum;
};
#endif
