#include "ComponentTransform.h"

ComponentTransform::ComponentTransform()
{
  type = TRANSFORM;
  active = true;
  my_go = nullptr;
}

ComponentTransform::~ComponentTransform()
{

}
