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
    
    bool hasNormals = false;
    bool hasColors = false;
    
    int xIndex = -1;
    int yIndex = -1;
    int zIndex = -1;
    int nxIndex = -1;
    int nyIndex = -1;
    int nzIndex = -1;
    int redIndex = -1;
    int greenIndex = -1;
    int blueIndex = -1;
    
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
        if (line != "format ascii 1.0") {
            return 5;
        }
        
        // Process the header
        int numVertsInFile = -1;
        int numFacesInFile = -1;
        int propertyIndex = 0;
        while (getline(infile, line)) {
            std::vector<std::string> tokens = split(line, ' ');
            
            if (tokens[0] == "comment" || (tokens[0] == "property" && tokens[1] == "list")) {
                continue;
            } else if (tokens[0] == "end_header") {
                break;
            } else if (tokens[0] == "element") {
                if (tokens[1] == "vertex") {
                    numVertsInFile = std::stoi(tokens[2]);
                } else if (tokens[1] == "face") {
                    numFacesInFile = std::stoi(tokens[2]);
                }
            } else if (tokens[0] == "property") {
                if (tokens[2] == "x") {
                    xIndex = propertyIndex;
                } else if (tokens[2] == "y") {
                    yIndex = propertyIndex;
                } else if (tokens[2] == "z") {
                    zIndex = propertyIndex;
                } else if (tokens[2] == "nx") {
                    nxIndex = propertyIndex;
                } else if (tokens[2] == "ny") {
                    nyIndex = propertyIndex;
                } else if (tokens[2] == "nz") {
                    nzIndex = propertyIndex;
                } else if (tokens[2] == "red") {
                    redIndex = propertyIndex;
                } else if (tokens[2] == "green") {
                    greenIndex = propertyIndex;
                } else if (tokens[2] == "blue") {
                    blueIndex = propertyIndex;
                } else {
                    return 6;
                }
                propertyIndex++;
            }
        }
        
        // Check for both vertices and faces
        if (numVertsInFile == -1 || numFacesInFile == -1) {
            return 7;
        }
        
        // Check for all vertex position properties
        if (xIndex == -1 || yIndex == -1 || zIndex == -1) {
            return 11;
        }
        
        // Check for normals to be completely present
        if (nxIndex != -1 && nyIndex != -1 && nzIndex != -1) {
            hasNormals = true;
        } else {
            warnWithMessage(std::string(filename) + " has no normals");
        }
        
        // Check for colors to be completely present
        if (redIndex != -1 && greenIndex != -1 && blueIndex != -1) {
            hasColors = true;
        } else {
            warnWithMessage(std::string(filename) + " has no vertex colors");
        }
        
        // Read all the vertices into a vector
        std::vector<Vector4> tempVertices = std::vector<Vector4>();
        std::vector<Vector3> tempNormals = std::vector<Vector3>();
        std::vector<Vector4> tempColors = std::vector<Vector4>();
        for (int i = 0; i < numVertsInFile; i++) {
            if (!getline(infile, line)) {
                return 8;
            }
            
            std::vector<std::string> tokens = split(line, ' ');
            
            float x = std::stof(tokens[xIndex]);
            float y = std::stof(tokens[yIndex]);
            float z = std::stof(tokens[zIndex]);
            tempVertices.push_back(Vector4(x, y, z, 1));
            
            if (hasColors) {
                float red = std::stoi(tokens[redIndex]) / 255.0;
                float green = std::stoi(tokens[greenIndex]) / 255.0;
                float blue = std::stoi(tokens[blueIndex]) / 255.0;
                tempColors.push_back(Vector4(red, green, blue, 1));
            } else {
                tempColors.push_back(Vector4(1, 1, 1, 1));
            }
            
            if (hasNormals) {
                float nx = std::stof(tokens[nxIndex]);
                float ny = std::stof(tokens[nyIndex]);
                float nz = std::stof(tokens[nzIndex]);
                tempNormals.push_back(Vector3(nx, ny, nz));
            } else {
                tempNormals.push_back(Vector3(0, 0, 0));
            }
        }
        
        // Read all the faces into the actual arrays
        numberOfVertices = numFacesInFile * 3;
        vertices = new Vector4[numberOfVertices];
        vertexNormals = new Vector3[numberOfVertices];
        vertexColors = new Vector4[numberOfVertices];
        int k = 0;
        for (int i = 0; i < numFacesInFile; i++) {
            if (!getline(infile, line)) {
                return 9;
            }
            
            std::vector<std::string> tokens = split(line, ' ');
            if (tokens[0] != "3") {
                return 10;
            }
            
            for (int j = 1; j <= 3; j++) {
                int vIndex = std::stoi(tokens[j]);
                vertices[k] = tempVertices[vIndex];
                vertexNormals[k] = tempNormals[vIndex];
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

Vector3* PLYGameObject::getVertexNormals() {
    return vertexNormals;
}

Vector4* PLYGameObject::getVertexColors() {
    return vertexColors;
}
