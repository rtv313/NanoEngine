#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

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
  Component* ct;

  switch (type) {
  case TRANSFORM:
    ct = new ComponentTransform();
    break;
  case MESH:
    ct = new ComponentMesh();
    break;
  case MATERIAL:
    ct = new ComponentMaterial();
    break;
  }

  ct->my_go = this;
  return ct;
}
