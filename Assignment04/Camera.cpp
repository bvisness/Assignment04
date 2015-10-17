//
//  Camera.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/1/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Camera.h"
#include "Scene.h"

void Camera::updateSceneProjectionMatrixIfSafe() {
    if (scene != nullptr) {
        scene->updateProjectionMatrix();
    }
}

Camera::Camera() {
    defaultTarget = new Empty();
    defaultTarget->position = Vector3(0, 0, 1);
    addChild(defaultTarget);
}

GameObject* Camera::getTarget() {
    return lookAtTarget;
}

void Camera::setTarget(GameObject* target) {
    lookAtTarget = target;
}

void Camera::removeTarget() {
    lookAtTarget = nullptr;
}

Matrix4 Camera::getModelViewMatrix() {
    GameObject* targetToUse = lookAtTarget;
    if (lookAtTarget == nullptr) {
        targetToUse = defaultTarget;
    }
    
    if (position == targetToUse->position) {
        warnWithMessage("In Camera::getModelViewMatrix(): Camera in same position as lookAtTarget");
    }
    
    Vector3 worldRot = getWorldRotation();
    Vector4 up = RotateX(worldRot.x) * Vector3(0, 1, 0);
    up = RotateY(worldRot.y) * up;
    
    return LookAt(getWorldPosition(), targetToUse->getWorldPosition(), up);
}

Matrix4 Camera::getProjectionMatrix() {
    return Perspective(fov, scene->aspect, nearDistance, farDistance);
}

GLfloat Camera::getFOV() {
    return fov;
}

void Camera::setFOV(GLfloat newFOV) {
    fov = clamp(newFOV, 1, 90);
    updateSceneProjectionMatrixIfSafe();
}

void Camera::setNearClippingDistance(GLfloat newNear) {
    nearDistance = newNear;
    updateSceneProjectionMatrixIfSafe();
}

void Camera::setFarClippingDistance(GLfloat newFar) {
    farDistance = newFar;
    updateSceneProjectionMatrixIfSafe();
}
