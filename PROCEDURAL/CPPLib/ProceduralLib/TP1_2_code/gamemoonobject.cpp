#include "gamemoonobject.h"

void GameMoonObject::update(){
    transform.rotateLocal(1, QVector3D(0,1,0));
    updateChildren();
}
