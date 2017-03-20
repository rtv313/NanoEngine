#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Component.h"
#include <vector>
#include <string>

class GameObject
{
public:
  GameObject();
  ~GameObject();

  void Update();
  Component* CreateComponent(component_type type);

  bool active;
  std::string name;
  std::vector<Component*> components;
};

#endif