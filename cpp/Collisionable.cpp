#include "Colisionable.h"

bool Collisionable::isCollision(Collisionable &obj) const{
  return getBounds().intersects(obj.getBounds());
}
