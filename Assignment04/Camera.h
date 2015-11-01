//
//  Camera.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/1/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__Camera__
#define __Assignment03__Camera__

#include "VisnessUtil.h"
#include "GameObject.h"

class Camera: public GameObject {
private:
    /**
     * If this camera is assigned to a scene, tell
     * that scene to update the projection matrix.
     */
    void updateSceneProjectionMatrixIfSafe();
protected:
    /**
     * An Empty positioned in front of the camera
     * so it has something to look at when no other
     * target is assigned.
     */
    GameObject* defaultTarget;
    
    /**
     * The GameObject for the camera to look at.
     */
    GameObject* lookAtTarget = nullptr;
    
    GLfloat fov = 45;
    GLfloat nearDistance = 1;
    GLfloat farDistance = 100;
public:
    Camera();
    GameObject* getTarget();
    void setTarget(GameObject* target);
    void removeTarget();
    
    /**
     * Gets the model view matrix from this camera to
     * serve as a starting point for other GameObjects.
     * Note that this is different from
     * GameObject::getModelViewMatrix().
     */
    Matrix4 getModelViewMatrix();
    
    /**
     * Gets a projection matrix based on the parameters
     * of this camera.
     */
    Matrix4 getProjectionMatrix();
    
    GLfloat getFOV();
    void setFOV(GLfloat newFOV);
    void setNearClippingDistance(GLfloat newNear);
    void setFarClippingDistance(GLfloat newFar);
};

#endif /* defined(__Assignment03__Camera__) */
