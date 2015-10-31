//
//  GLMiddleman.cpp
//  Assignment02
//
//  Created by Benjamin Visness on 9/29/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "GLMiddleman.h"

GLfloat* floatArrayWithValue(int size, GLfloat value) {
    GLfloat* result = new GLfloat[size];
    for (int i = 0; i < size; i++) {
        result[i] = value;
    }
    return result;
}

GLMiddleman::GLMiddleman() {
    program = InitShader("vshader-phongshading.glsl", "fshader-phongshading.glsl");
    glUseProgram(program);
    
    //grab pointers for our uniforms
    model_view = glGetUniformLocation(program, "uModelView");
    projection = glGetUniformLocation(program, "uProjection");
    uAmbientLight = glGetUniformLocation(program, "uAmbientLight");
    uLightType = glGetUniformLocation(program, "uLightType");
    uLightColor = glGetUniformLocation(program, "uLightColor");
    uLightPosition = glGetUniformLocation(program, "uLightPosition");
    uLightDirection = glGetUniformLocation(program, "uLightDirection");
}

void GLMiddleman::updateProjectionMatrix(mat4 newMatrix) {
    glUniformMatrix4fv(projection, 1, GL_TRUE, newMatrix);
}

void GLMiddleman::updateModelViewMatrix(mat4 newMatrix) {
    glUniformMatrix4fv(model_view, 1, GL_TRUE, newMatrix);
}

void GLMiddleman::bufferObject(GLuint vao, GLuint* vbo, int numberOfVertices, Vector4* vertices, Vector3* vertexNormals, Vector4* vertexColors, Material material) {
	glBindVertexArray(vao);

    // Vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * (sizeof(GLfloat) * 4), vertices, GL_STATIC_DRAW);
    vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Vertex normal vectors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * (sizeof(GLfloat) * 3), vertexNormals, GL_STATIC_DRAW);
    vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Vertex ambient colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * (sizeof(GLfloat) * 4), vertexColors, GL_STATIC_DRAW);
    vAmbientDiffuseColor = glGetAttribLocation(program, "vAmbientDiffuseColor");
    glEnableVertexAttribArray(vAmbientDiffuseColor);
    glVertexAttribPointer(vAmbientDiffuseColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Vertex diffuse amount
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(GLfloat), floatArrayWithValue(numberOfVertices, material.diffuseAmount), GL_STATIC_DRAW);
    vDiffuseAmount = glGetAttribLocation(program, "vDiffuseAmount");
    glEnableVertexAttribArray(vDiffuseAmount);
    glVertexAttribPointer(vDiffuseAmount, 1, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Vertex specular amount
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(GLfloat), floatArrayWithValue(numberOfVertices, material.specularAmount), GL_STATIC_DRAW);
    vSpecularAmount = glGetAttribLocation(program, "vSpecularAmount");
    glEnableVertexAttribArray(vSpecularAmount);
    glVertexAttribPointer(vSpecularAmount, 1, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Vertex specular exponents
    glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(GLfloat), floatArrayWithValue(numberOfVertices, material.specularExponent), GL_STATIC_DRAW);
    vSpecularExponent = glGetAttribLocation(program, "vSpecularExponent");
    glEnableVertexAttribArray(vSpecularExponent);
    glVertexAttribPointer(vSpecularExponent, 1, GL_FLOAT, GL_FALSE, 0, 0);
}
