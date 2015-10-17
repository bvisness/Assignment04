//
//  GLMiddleman.cpp
//  Assignment02
//
//  Created by Benjamin Visness on 9/29/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "GLMiddleman.h"

GLMiddleman::GLMiddleman() {
    program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );
    
    //grab pointers for our modelview and perspective uniform matrices
    model_view = glGetUniformLocation(program, "model_view");
    projection = glGetUniformLocation(program, "projection");
}

void GLMiddleman::updateProjectionMatrix(mat4 newMatrix) {
    glUniformMatrix4fv(projection, 1, GL_TRUE, newMatrix);
}

void GLMiddleman::updateModelViewMatrix(mat4 newMatrix) {
    glUniformMatrix4fv(model_view, 1, GL_TRUE, newMatrix);
}

void GLMiddleman::bufferObject(GLuint vao, GLuint* vbo, int numberOfVertices, Vector4* vertices, int numberOfColors, Vector4* vertexColors) {
	glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * (sizeof(GLfloat) * 4), vertices, GL_STATIC_DRAW);
    vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, numberOfColors * (sizeof(GLfloat) * 4), vertexColors, GL_STATIC_DRAW);
    vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
