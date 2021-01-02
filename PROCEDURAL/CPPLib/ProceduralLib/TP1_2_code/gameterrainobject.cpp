#include "gameterrainobject.h"

void GameTerrainObject::init(){

    int size = 124;
    QVector<VertexData> vertices;

    for(int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j) {
            vertices.push_back({QVector3D((1.0f*j-size/2) *32 /size, 0.0f, (-(1.0f*i-size/2)) *32 /size), QVector2D((float)i/(size-1), (float)j/(size-1) )});
        }
    }

    QVector<GLushort> indices;
    for (int i = 0; i < size-1; ++i) {
        if(i != 0){
            indices.push_back( i*size+size ); //beggin duplication
            //cout << indices[indices.size()-1] << " ";
        }
        for (int j = 0; j < size; ++j) {
            indices.push_back(i*size+j+size); //lower one
            //cout << indices[indices.size()-1] << " ";

            indices.push_back(i*size+j); //top one
            //cout << indices[indices.size()-1] << " ";

        }
        if(i != size-2){
            indices.push_back( i*size+size-1); //end duplication
            //cout << indices[indices.size()-1] << " " << endl;
        }
    }
    this->size = indices.size();

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices.data(), indices.size() * sizeof(GLushort));

    initChildren();
}
