//
//  Sphere.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__Sphere__
#define __Assignment03__Sphere__

#include "GameObject.h"
#include "GLMiddleman.h"

class Sphere: public GameObject {
private:
    void initSphere(float radius, int subdiv);
    Vector4 sphereColor;
    int numVertsSphere;
    Vector4* sphereVerts = nullptr;
    Vector4* sphereColors = nullptr;
protected:
    int getNumberOfVertices();
    Vector4* getVertices();
    Vector4* getVertexColors();
public:
    Sphere(float radius, int subdiv, Vector4 color) : GameObject() {
        sphereColor = color;
        initSphere(radius, subdiv);
    }
};

#endif /* defined(__Assignment03__Sphere__) */
