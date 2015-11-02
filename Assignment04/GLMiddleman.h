//
//  GLMiddleman.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/29/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__GLMiddleman__
#define __Assignment02__GLMiddleman__

#include "VisnessGL.h"
#include "VisnessUtil.h"
#include "Material.h"

#ifndef MAX_LIGHTS
#define MAX_LIGHTS 6
#endif

/**
 * A class that handles shipping data over to
 * the graphics card using OpenGL methods.
 */
class GLMiddleman {
private:
	int numRegisteredLights = 0;
public:
    GLMiddleman();
    GLuint program;
    GLuint model_view;
    GLuint projection;
    GLuint vPosition;
    GLuint vNormal;
    GLuint vAmbientDiffuseColor;
    GLfloat vDiffuseAmount;
    GLfloat vSpecularAmount;
    GLfloat vSpecularExponent;
    GLuint uAmbientLight;
    GLuint uLightType;
    GLuint uLightColor;
    GLuint uLightPosition;
    GLuint uLightDirection;

	Vector4 lightPositions[MAX_LIGHTS];
	Vector4 lightDirections[MAX_LIGHTS];
	Vector4 lightColors[MAX_LIGHTS];
	int lightTypes[MAX_LIGHTS];
    
    void updateProjectionMatrix(mat4 newMatrix);
    void updateModelViewMatrix(mat4 newMatrix);
    
    /**
     * Buffer an object over to the graphics card.
     *
     * @param vao The id of the vao for this object.
     * @param vbo An array of vbo ids for this object.
     * @param numberOfVertices The number of vertices in this object.
     * @param vertices The vertices of this object.
     * @param vertexNormals The vertex normal vectors for this object.
     * @param vertexColors The vertex colors for this object.
     * @param material The material for this object.
     */
    void bufferObject(GLuint vao,
                      GLuint* vbo,
                      int numberOfVertices,
                      Vector4* vertices,
                      Vector3* vertexNormals,
                      Vector4* vertexColors,
                      Material material);

	int getLightId();
	void bufferLights();
};

#endif /* defined(__Assignment02__GLMiddleman__) */
