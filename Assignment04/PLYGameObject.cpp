//
//  PLYGameObject.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include <fstream>
#include <string>

#include "PLYGameObject.h"

int PLYGameObject::loadPLY(const char* filename) {
    std::ifstream infile(filename);
    
    std::string line;
    if (infile.is_open()) {
        // Check the first lines for correctness
        if (!getline(infile, line)) {
            return 2;
        }
        std::vector<std::string> firstLineTokens = split(line, ' ');
        if (firstLineTokens[0] != "ply") {
            return 3;
        }
        
        if (!getline(infile, line)) {
            return 4;
        }
        std::vector<std::string> secondLineTokens = split(line, ' ');
        if (secondLineTokens[0] != "format" && secondLineTokens[1] != "ascii") {
            return 5;
        }
        
        // Process the header
        int numVertsInFile = -1;
        int numFacesInFile = -1;
        while (getline(infile, line)) {
            std::vector<std::string> tokens = split(line, ' ');
            
            if (tokens[0] == "end_header") {
                break;
            } else if (tokens[0] == "element") {
                if (tokens[1] == "vertex") {
                    numVertsInFile = std::stoi(tokens[2]);
                } else if (tokens[1] == "face") {
                    numFacesInFile = std::stoi(tokens[2]);
                }
            }
        }
        
        if (numVertsInFile == -1 || numFacesInFile == -1) {
            return 6;
        }
        
        // Read all the vertices into a vector
        std::vector<Vector4> tempVertices = std::vector<Vector4>();
        std::vector<Vector4> tempColors = std::vector<Vector4>();
        for (int i = 0; i < numVertsInFile; i++) {
            if (!getline(infile, line)) {
                return 7;
            }
            
            std::vector<std::string> tokens = split(line, ' ');
            float x = std::stof(tokens[0]);
            float y = std::stof(tokens[1]);
            float z = std::stof(tokens[2]);
            float red = std::stoi(tokens[3]) / 255.0;
            float green = std::stoi(tokens[4]) / 255.0;
            float blue = std::stoi(tokens[5]) / 255.0;
            
            tempVertices.push_back(Vector4(x, y, z, 1));
            tempColors.push_back(Vector4(red, green, blue, 1));
        }
        
        // Read all the faces into the actual arrays
        numberOfVertices = numFacesInFile * 3;
        vertices = new Vector4[numberOfVertices];
        vertexColors = new Vector4[numberOfVertices];
        int k = 0;
        for (int i = 0; i < numFacesInFile; i++) {
            if (!getline(infile, line)) {
                return 8;
            }
            
            std::vector<std::string> tokens = split(line, ' ');
            if (tokens[0] != "3") {
                return 9;
            }
            
            for (int j = 1; j <= 3; j++) {
                int vIndex = std::stoi(tokens[j]);
                vertices[k] = tempVertices[vIndex];
                vertexColors[k] = tempColors[vIndex];
                k++;
            }
        }
        
        infile.close();
    } else {
        return 1;
    }
    
    initialized = true;
    return 0;
}

int PLYGameObject::getNumberOfVertices() {
    return numberOfVertices;
}

Vector4* PLYGameObject::getVertices() {
    return vertices;
}

Vector4* PLYGameObject::getVertexColors() {
    return vertexColors;
}
