//
//  Cylinder.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__Cylinder__
#define __Assignment03__Cylinder__

#include "GameObject.h"
#include "GLMiddleman.h"

class Cylinder: public GameObject {
private:
    void initCylinder(float radius, float depth, int verts, Vector4 color);
    int numVertsCircle;
    int numVertsCylinder;
    Vector4* cylinderVerts = nullptr;
    Vector4* cylinderColors = nullptr;
protected:
    int getNumberOfVertices();
    Vector4* getVertices();
    Vector3* getVertexNormals();
    Vector4* getVertexColors();
public:
    Cylinder(float radius, float depth, int verts, Vector4 color) : GameObject() {
        numVertsCircle = verts;
        initCylinder(radius, depth, verts, color);
    }
    void setCapTopColor(Vector4 color);
    void setCapBottomColor(Vector4 color);
};

#endif /* defined(__Assignment03__Cylinder__) */
