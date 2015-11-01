//
//  RenderedGameObject.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/26/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment04__RenderedGameObject__
#define __Assignment04__RenderedGameObject__

#include "VisnessUtil.h"
#include "VisnessGL.h"
#include "Material.h"
#include "GameObject.h"

#ifndef VBO_COUNT
#define VBO_COUNT 6 // position, normal vector, ambient and diffuse colors, diffuse amount, specular amount, specular exponent
#endif

class RenderedGameObject : public GameObject {
protected:
	GLuint vao;
	GLuint vbo[VBO_COUNT];

	void drawGameObject();
	void customInitGameObject();

	virtual int getNumberOfVertices() = 0;
	virtual Vector4* getVertices() = 0;
	virtual Vector3* getVertexNormals() = 0;
	virtual Vector4* getVertexColors() = 0;
public:
	GLuint getVAO();
	Material material;
};

#endif
