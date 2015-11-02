//
//  Light.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/1/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Light.h"
#include "Scene.h"

void Light::customInitGameObject() {
	lightId = scene->middleman->getLightId();
}

void Light::updateInMiddleman() {
	if (type != LIGHT_DIRECTIONAL) {
		scene->middleman->lightPositions[lightId] = getModelViewMatrix() * Vector4(0, 0, 0, 1);
	}
	if (type == LIGHT_SPOT) {
		GLfloat spotAngleCosine = cos(spotAngle * DEG_TO_RAD);
		scene->middleman->lightSpotAngleCosines[lightId] = cos(spotAngle * DEG_TO_RAD);
	}
	if (type == LIGHT_SPOT || type == LIGHT_DIRECTIONAL) {
		scene->middleman->lightDirections[lightId] = getModelViewMatrix() * Vector4(0, 0, 1, 0);
	}
	scene->middleman->lightColors[lightId] = color;
	scene->middleman->lightTypes[lightId] = type;
}
