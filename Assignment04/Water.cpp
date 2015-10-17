//
//  Water.cpp
//  Assignment02
//
//  Created by Benjamin Visness on 9/30/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Water.h"

const int numVertsWater = 6;

Vector4 waterVerts[numVertsWater];
Vector4 waterColors[numVertsWater];

void initWater() {
    for(int i=0; i<6; i++){
        waterColors[i] = Vector4(0.4, 0.4, 1.0, 1.0); //bottom
    }
    
    waterVerts[0] = Vector4(-1, 0, 1, 1.0);
    waterVerts[1] = Vector4(1, 0, 1, 1.0);
    waterVerts[2] = Vector4(1, 0, -1, 1.0);
    waterVerts[3] = Vector4(-1, 0, 1, 1.0);
    waterVerts[4] = Vector4(1, 0, -1, 1.0);
    waterVerts[5] = Vector4(-1, 0, -1, 1.0);
}

int Water::getNumberOfVertices() {
    return numVertsWater;
}

Vector4* Water::getVertices() {
    initWater();
    return waterVerts;
}

Vector4* Water::getVertexColors() {
    initWater();
    return waterColors;
}
