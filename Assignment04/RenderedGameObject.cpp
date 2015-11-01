//
//  RenderedGameObject.cpp
//  Assignment02
//
//  Created by Benjamin Visness on 9/26/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "RenderedGameObject.h"
#include "Scene.h"

void RenderedGameObject::customInitGameObject() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(VBO_COUNT, vbo);

	scene->middleman->bufferObject(vao, vbo, getNumberOfVertices(), getVertices(), getVertexNormals(), getVertexColors(), material);
}

GLuint RenderedGameObject::getVAO() {
	return vao;
}

void RenderedGameObject::drawGameObject() {
	mat4 mv = getModelViewMatrix();

	scene->middleman->updateModelViewMatrix(mv);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices());
}
