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

/**
 * A class that handles shipping data over to
 * the graphics card using OpenGL methods.
 */
class GLMiddleman {
public:
    GLMiddleman();
    GLuint program;
    GLuint model_view;
    GLuint projection;
    GLuint vPosition;
    GLuint vColor;
    
    void updateProjectionMatrix(mat4 newMatrix);
    void updateModelViewMatrix(mat4 newMatrix);
    
    void bufferObject(GLuint vao,
                      GLuint* vbo,
                      int numberOfVertices,
                      Vector4* vertices,
                      int numberOfColors,
                      Vector4* vertexColors);
};

#endif /* defined(__Assignment02__GLMiddleman__) */
