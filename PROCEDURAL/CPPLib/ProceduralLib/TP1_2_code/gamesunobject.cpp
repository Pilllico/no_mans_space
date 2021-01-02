#include "gamesunobject.h"

void GameSunObject::update(){
    transform.rotateLocal(-1, QVector3D(0,1,0));
    transform.rotate(1, QVector3D(0,1,0) );
    updateChildren();
}
