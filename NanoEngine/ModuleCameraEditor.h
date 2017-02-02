#ifndef __MODULECAMERAEDITOR_H__
#define __MODULECAMERAEDITOR_H__
#include "Module.h"

class ModuleCameraEditor :
	public Module
{
public:
	ModuleCameraEditor();
	~ModuleCameraEditor();
	void setFOV();
	void setAspectRatio();
	void setPlaneDistances();
	void getProjectionMatrix();
	void getViewMatrix();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
};
#endif
