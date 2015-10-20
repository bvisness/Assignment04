//
//  Boat.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/28/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__Boat__
#define __Assignment02__Boat__

#include "PLYGameObject.h"

class Boat: public PLYGameObject {
public:
    Boat() : PLYGameObject("Boat.ply") {
        material.specularAmount = 0.2;
        material.specularExponent = 10;
    }
};

#endif /* defined(__Assignment02__Boat__) */
