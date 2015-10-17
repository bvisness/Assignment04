//
//  PLYGameObject.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__PLYGameObject__
#define __Assignment03__PLYGameObject__

#include "GameObject.h"

class PLYGameObject: public GameObject {
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
    int loadPLY(const char* filename);
    PLYGameObject() : GameObject() {}
    PLYGameObject(const char* filename) : GameObject() {
        printf("%d\n", loadPLY(filename));
    }
};

#endif /* defined(__Assignment03__PLYGameObject__) */
