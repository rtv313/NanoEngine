#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRANSFORM_H__

#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Component.h"

class ComponentTransform : public Component
{
public:
  ComponentTransform();
  ~ComponentTransform();
  ComponentTransform(aiMatrix4x4 matrix);

  aiMatrix4x4 transform;
};

#endif