//
//  Cylinder.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Cylinder.h"

void Cylinder::initCylinder(float radius, float depth, int verts, Vector4 color) {
    numVertsCylinder = (2 * (3 * verts)) + (6 * verts);
    
    cylinderVerts = new Vector4[numVertsCylinder];
    cylinderColors = new Vector4[numVertsCylinder];
    
    int k = 0;
    
    float angle = 2 * M_PI / verts;
    float topY = depth / 2;
    float bottomY = -depth / 2;
    
    // Top cap
    for (int i = 0; i < verts; i++) {
        float currentAngle = i * angle;
        float nextAngle = (i + 1) * angle;
        
        cylinderVerts[k] = Vector4(0, topY, 0, 1); // center top
        k++;
        
        cylinderVerts[k] = Vector4(sin(currentAngle) * radius, topY, cos(currentAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(nextAngle) * radius, topY, cos(nextAngle) * radius, 1);
        k++;
    }
    
    // Bottom cap
    for (int i = 0; i < verts; i++) {
        float currentAngle = i * angle;
        float nextAngle = (i + 1) * angle;
        
        cylinderVerts[k] = Vector4(0, bottomY, 0, 1); // center bottom
        k++;
        
        cylinderVerts[k] = Vector4(sin(currentAngle) * radius, bottomY, cos(currentAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(nextAngle) * radius, bottomY, cos(nextAngle) * radius, 1);
        k++;
    }
    
    // Sides
    for (int i = 0; i < verts; i++) {
        float currentAngle = i * angle;
        float nextAngle = (i + 1) * angle;
        
        cylinderVerts[k] = Vector4(sin(currentAngle) * radius, topY, cos(currentAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(currentAngle) * radius, bottomY, cos(currentAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(nextAngle) * radius, bottomY, cos(nextAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(currentAngle) * radius, topY, cos(currentAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(nextAngle) * radius, bottomY, cos(nextAngle) * radius, 1);
        k++;
        
        cylinderVerts[k] = Vector4(sin(nextAngle) * radius, topY, cos(nextAngle) * radius, 1);
        k++;
    }
    
    for (int i = 0; i < numVertsCylinder; i++) {
        cylinderColors[i] = color;
    }
}

int Cylinder::getNumberOfVertices() {
    return numVertsCylinder;
}

Vector4* Cylinder::getVertices() {
    return cylinderVerts;
}

Vector3* Cylinder::getVertexNormals() {
    return nullptr;
}

Vector4* Cylinder::getVertexColors() {
    return cylinderColors;
}

void Cylinder::setCapTopColor(Vector4 color) {
    for (int i = 0; i < numVertsCircle * 3; i++) {
        cylinderColors[i] = color;
    }
}

void Cylinder::setCapBottomColor(Vector4 color) {
    for (int i = numVertsCircle * 3; i < (numVertsCircle * 3) * 2; i++) {
        cylinderColors[i] = color;
    }
}
