//
//  STLGameObject.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include <fstream>
#include <string>

#include "STLGameObject.h"

int STLGameObject::loadSTL(const char* filename) {
    std::ifstream infile(filename);
    
    std::string line;
    if (infile.is_open()) {
        if (!getline(infile, line)) {
            return 2;
        }
        
        // Check the first line for correctness
        std::vector<std::string> firstLineTokens = split(line, ' ');
        if (firstLineTokens[0] != "solid") {
            return 2;
        }
        
        // Work through the rest of the file
        std::vector<Vector4> tempVertices = std::vector<Vector4>();
        while (getline(infile, line)) {
            std::vector<std::string> tokens = split(line, ' ');
            if (tokens[0] == "vertex") {
                float x = std::stof(tokens[1]);
                float y = std::stof(tokens[2]);
                float z = std::stof(tokens[3]);
                
                tempVertices.push_back(Vector4(x, y, z, 1));
            }
        }
        
        numberOfVertices = (int) tempVertices.size();
        vertices = new Vector4[numberOfVertices];
        vertexColors = new Vector4[numberOfVertices];
        for (int i = 0; i < numberOfVertices; i++) {
            vertices[i] = tempVertices[i];
            vertexColors[i] = Vector4(1, 1, 1, 0);
        }
        
        infile.close();
    } else {
        return 1;
    }
    
    initialized = true;
    return 0;
}

int STLGameObject::getNumberOfVertices() {
    return numberOfVertices;
}

Vector4* STLGameObject::getVertices() {
    return vertices;
}

Vector4* STLGameObject::getVertexColors() {
    return vertexColors;
}
