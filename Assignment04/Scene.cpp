//
//  Scene.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/1/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Scene.h"

Scene::Scene() {
    middleman = new GLMiddleman();
}

Scene::Scene(GLMiddleman* newMiddleman) {
    middleman = newMiddleman;
}

void Scene::addGameObject(GameObject* obj) {
    obj->setScene(this);
    gameObjects.push_back(obj);
}

void Scene::init() {
    if (initialized) {
        return;
    }
    
    std::vector<GameObject*>::iterator it = gameObjects.begin();
    while (it != gameObjects.end()) {
        (*it)->initGameObject();
        it++;
    }
    
    initialized = true;
}

void Scene::draw() {
    glUniform4fv(middleman->uLightPosition, 1, activeCamera->getModelViewMatrix() * vec4(0, 5, 0, 1));
    glUniform4fv(middleman->uLightColor, 1, vec4(1, 1, 1, 1));
    glUniform4fv(middleman->uAmbientLight, 1, vec4(0.2, 0.2, 0.2, 1));
    
    std::vector<GameObject*>::iterator it = gameObjects.begin();
    while (it != gameObjects.end()) {
        (*it)->draw();
        it++;
    }
}

Camera* Scene::getActiveCamera() {
    return activeCamera;
}

void Scene::setActiveCamera(Camera* cam) {
    activeCamera = cam;
    updateProjectionMatrix();
}

void Scene::setAspectRatio(GLfloat newAspect) {
    aspect = newAspect;
    updateProjectionMatrix();
}

void Scene::setAspectRatio(GLfloat width, GLfloat height) {
    aspect = width / height;
    updateProjectionMatrix();
}

void Scene::updateProjectionMatrix() {
    if (activeCamera == nullptr) {
        abortWithMessage("In Scene::updateProjectionMatrix(): Scene has no active camera");
    }
    middleman->updateProjectionMatrix(activeCamera->getProjectionMatrix());
}
