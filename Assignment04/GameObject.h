//
//  GameObject.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/26/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__GameObject__
#define __Assignment02__GameObject__

#include <vector>

#include "VisnessUtil.h"
#include "VisnessGL.h"
#include "GLMiddleman.h"

class Scene;

/**
 * An object to be displayed onscreen.
 */
class GameObject {
friend class Scene;
protected:
    bool initialized = false;
    Scene* scene = nullptr;
    void initGameObject();
    
    GLuint vao;
    GLuint vbo[2];
    GameObject* parent = nullptr;
    std::vector<GameObject*> children = std::vector<GameObject*>();
    
    virtual int getNumberOfVertices() = 0;
    virtual Vector4* getVertices() = 0;
    virtual Vector3* getVertexNormals() = 0;
    virtual Vector4* getVertexColors() = 0;
public:
    void setScene(Scene* newScene);
    
    GLuint getVAO();
    
    Vector3 position = Vector3();
    Vector3 rotation = Vector3();
    GLfloat scale = 1;
    
    GameObject* getParent();
    std::vector<GameObject*> getChildren();
    void addChild(GameObject* obj);
    
    /**
     * Gets the position of this object relative to the world
     * rather than to its parent.
     */
    Vector3 getWorldPosition();
    
    /**
     * Gets the rotation of this object relative to the world
     * rather than to its parent.
     */
    Vector3 getWorldRotation();
    
    /**
     * Gets the scale of this object relative to the world
     * rather than to its parent.
     */
    GLfloat getWorldScale();
    
    /**
     * Gets the model view matrix for this object, either relative
     * to a camera or to the world.
     *
     * @param forCamera Whether to get a model view matrix relative
     *          to the scene's active camera.
     */
    mat4 getModelViewMatrix(bool forCamera = true);
    
    /**
     * Draw the GameObject and all its children onscreen.
     */
    void draw();
};

#endif
