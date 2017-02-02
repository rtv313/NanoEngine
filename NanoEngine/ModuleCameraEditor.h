#ifndef __MODULECAMERAEDITOR_H__
#define __MODULECAMERAEDITOR_H__
#include "Module.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "Glew/include/GL/glew.h"
#include <gl/GL.h>

class ModuleCameraEditor :
	public Module
{
public:
	float3 position,up,lookAt;
	GLfloat fieldOfView, screenWidth, screenHeight;
	GLfloat zNear, zFar;
	
ModuleCameraEditor();
	~ModuleCameraEditor();
	void setFOV();
	void setAspectRatio();
	void setPlaneDistances(GLfloat zNear, GLFloat zFar);
	void getProjectionMatrix();
	void getViewMatrix();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	Frustum frustum;
};
#endif
