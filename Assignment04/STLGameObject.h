//
//  STLGameObject.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__STLGameObject__
#define __Assignment03__STLGameObject__

#include "GameObject.h"

class STLGameObject: public GameObject {
private:
    bool initialized = false;
    int numberOfVertices = 0;
    Vector4* vertices;
    Vector4* vertexColors;
protected:
    int getNumberOfVertices();
    Vector4* getVertices();
    Vector4* getVertexColors();
public:
    int loadSTL(const char* filename);
    STLGameObject() : GameObject() {}
    STLGameObject(const char* filename) : GameObject() {
        loadSTL(filename);
    }
};

#endif /* defined(__Assignment03__STLGameObject__) */
