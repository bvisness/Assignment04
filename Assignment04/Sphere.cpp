//
//  Sphere.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Sphere.h"

void Sphere::initSphere(float radius, int subdiv) {
    numVertsSphere = ceil(subdiv / 2.0) * subdiv * 6;
    
    sphereVerts = new Vector4[numVertsSphere];
    sphereColors = new Vector4[numVertsSphere];
    
    float step = (360.0 / subdiv)*(M_PI / 180.0);
    
    int k = 0;
    for (float i = -M_PI / 2; i <= M_PI / 2; i += step){
        for (float j = -M_PI; j <= M_PI; j += step){
            //triangle 1
            sphereVerts[k] = vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
            k++;
            
            sphereVerts[k] = vec4(radius*sin(j)*cos(i + step), radius*cos(j)*cos(i + step), radius*sin(i + step), 1.0);
            k++;
            
            sphereVerts[k] = vec4(radius*sin((j + step))*cos((i + step)), radius*cos(j + step)*cos(i + step), radius*sin(i + step), 1.0);
            k++;
            
            //triangle 2
            sphereVerts[k] = vec4(radius*sin((j + step))*cos((i + step)), radius*cos(j + step)*cos(i + step), radius*sin(i + step), 1.0);
            k++;
            
            sphereVerts[k] = vec4(radius*sin(j + step)*cos(i), radius*cos(j + step)*cos(i), radius*sin(i), 1.0);
            k++;
            
            sphereVerts[k] = vec4(radius*sin(j)*cos(i), radius*cos(j)*cos(i), radius*sin(i), 1.0);
            k++;
        }
    }
    
    for (int i = 0; i < numVertsSphere; i++) {
        sphereColors[i] = sphereColor;
    }
}

int Sphere::getNumberOfVertices() {
    return numVertsSphere;
}

Vector4* Sphere::getVertices() {
    return sphereVerts;
}

Vector3* Sphere::getVertexNormals() {
    return nullptr;
}

Vector4* Sphere::getVertexColors() {
    return sphereColors;
}
