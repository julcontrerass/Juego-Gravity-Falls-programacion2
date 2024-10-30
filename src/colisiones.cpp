#include "colisiones.h"

bool Colisiones::isCollision(Colisiones &obj) const{
  return getBounds().intersects(obj.getBounds());
}
