//
//  Water.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/30/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__Water__
#define __Assignment02__Water__

#include "RenderedGameObject.h"

class Water: public RenderedGameObject {
protected:
    int getNumberOfVertices();
    Vector4* getVertices();
    Vector3* getVertexNormals();
    Vector4* getVertexColors();
public:
	Water() : RenderedGameObject() {
        material.specularAmount = 0.8;
        material.specularExponent = 1000;
    }
};

#endif /* defined(__Assignment02__Water__) */
