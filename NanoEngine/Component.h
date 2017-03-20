#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Application;
class GameObject;

enum component_type {
  TRANSFORM,
  MESH,
  MATERIAL,
  CAMERA
};

class Component
{
  public:
  Component() 
  {}

  virtual ~Component()
  {}

  virtual void Enable()
  {}

  virtual void Update()
  {}

  virtual void Disable()
  {}

  component_type type;
  bool active;
  GameObject* my_go;
};

#endif