#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update()
{

}

Component * GameObject::CreateComponent(component_type type)
{

  return new Component();
}
