//
//  OpenGL 3.2 Template for Mac
//  Ben Visness
//

// Suppress GLUT deprecated warnings on Mac
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "VisnessGL.h"
#include "Boat.h"
#include "Fan.h"
#include "Rudder.h"
#include "Searchlight.h"
#include "Water.h"
#include "Empty.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "PLYGameObject.h"
#include <math.h>
#pragma comment(lib, "glew32.lib")

#include <stdio.h>

//store window width and height
int ww = 1000, wh = 700;

//our modelview and perspective matrices
mat4 mv, p;

const int numRudders = 3;
const GLfloat rudderSpacing = 0.7;
const Vector4 rudderColors[3] = {
    Vector4(1.0, 0.8, 0.8, 1.0),
    Vector4(0.8, 1.0, 0.8, 1.0),
    Vector4(0.8, 0.8, 1.0, 1.0)
};

Scene* scene;

Boat* boat;
Fan* fan;
Rudder* rudders[numRudders];
Searchlight* searchlight;
Water* water;

Camera* freeCam;
Camera* chaseCam;
Camera* topCam;
Camera* lightCam;

const GLfloat waterScale = 10;
const GLfloat boatSpeed = 0.1;
const GLfloat boatRotateSpeed = 2;
const GLfloat fanSpeed = 10;
const GLfloat rudderAngle = 35;
const GLfloat searchlightSpeed = 1;
const GLfloat cameraDollySpeed = 0.2;
const GLfloat cameraDollyMinDistance = 5;
const GLfloat cameraDollyMaxDistance = 20;

bool keyUpArrow = false;
bool keyDownArrow = false;
bool keyLeftArrow = false;
bool keyRightArrow = false;
bool keyZoomIn = false;
bool keyZoomOut = false;
bool keyDollyIn = false;
bool keyDollyOut = false;
bool keySwitchLookTarget = false;
bool keyResetCamera = false;
bool keySearchlightClockwise = false;
bool keySearchlightCounterclockwise = false;

void resetFreeCamera() {
    freeCam->setFOV(45);
    freeCam->position = Vector3(0, 10, 20);
    freeCam->setTarget(water);
}

void display(void)
{
    /*clear all pixels*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
#ifdef __APPLE__
		printf("%s\n", gluErrorString(error));
#else
//        printf("%s\n", glewErrorString(error));
#endif
	}

    scene->draw();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	/*exit when the escape key is pressed*/
    if (key == 27) {
		exit(0);
    }
    
    if (key == 'a') {
        keySearchlightCounterclockwise = true;
    } else if (key == 'd') {
        keySearchlightClockwise = true;
    } else if (key == 'c') {
        if (scene->getActiveCamera() == freeCam) {
            scene->setActiveCamera(chaseCam);
        } else if (scene->getActiveCamera() == chaseCam) {
            scene->setActiveCamera(topCam);
        } else if (scene->getActiveCamera() == topCam) {
            scene->setActiveCamera(lightCam);
        } else {
            scene->setActiveCamera(freeCam);
        }
    }
    
    if (scene->getActiveCamera() == freeCam) {
        if (key == 'x') {
            keyZoomIn = true;
        } else if (key == 'z') {
            keyZoomOut = true;
        } else if (key == 'q') {
            keyDollyIn = true;
        } else if (key == 'e') {
            keyDollyOut = true;
        } else if (key == 'f' && !keySwitchLookTarget) {
            keySwitchLookTarget = true;
            if (freeCam->getTarget() == boat) {
                freeCam->setTarget(water);
            } else {
                freeCam->setTarget(boat);
            }
        } else if (key == 'r' && !keyResetCamera) {
            keyResetCamera = true;
            resetFreeCamera();
        }
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    if (key == 'x') {
        keyZoomIn = false;
    } else if (key == 'z') {
        keyZoomOut = false;
    } else if (key == 'q') {
        keyDollyIn = false;
    } else if (key == 'e') {
        keyDollyOut = false;
    } else if (key == 'f') {
        keySwitchLookTarget = false;
    } else  if (key == 'r') {
        keyResetCamera = false;
    } else if (key == 'a') {
        keySearchlightCounterclockwise = false;
    } else if (key == 'd') {
        keySearchlightClockwise = false;
    }
}

void special(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        keyUpArrow = true;
    } else if (key == GLUT_KEY_DOWN) {
        keyDownArrow = true;
    } else if (key == GLUT_KEY_LEFT) {
        keyLeftArrow = true;
    } else if (key == GLUT_KEY_RIGHT) {
        keyRightArrow = true;
    }
}

void specialUp(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        keyUpArrow = false;
    } else if (key == GLUT_KEY_DOWN) {
        keyDownArrow = false;
    } else if (key == GLUT_KEY_LEFT) {
        keyLeftArrow = false;
    } else if (key == GLUT_KEY_RIGHT) {
        keyRightArrow = false;
    }
}

void createObjects() {
    scene = new Scene();
    
    boat = new Boat();
    
    fan = new Fan();
    fan->position = Vector3(0, 1.35, -1.95);
    boat->addChild(fan);
    
    for (int i = 0; i < numRudders; i++) {
        rudders[i] = new Rudder();
        
        rudders[i]->position.x = -rudderSpacing + (rudderSpacing * i);
        rudders[i]->position.z = -2.2;
        
        boat->addChild(rudders[i]);
    }
        
    searchlight = new Searchlight();
    searchlight->position = Vector3(0, 0.5, 1.75);
    boat->addChild(searchlight);
    
    water = new Water();
    water->scale = 10;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            
            GLfloat pillarX = (i * 10) - 10;
            GLfloat pillarZ = (j * 10) - 10;
            
            for (int k = 0; k < 10; k++) {
                Sphere* pillarSphere = new Sphere(0.25, 36, Vector4(i % 2, j % 2, 1, 1));
                pillarSphere->position = Vector3(pillarX, k * 0.5, pillarZ);
                scene->addGameObject(pillarSphere);
            }
        }
    }
    
    // The free-roaming camera has no particular trick
    // to it. The default parameters can be found in the
    // resetFreeCamera() method.
    freeCam = new Camera();
    resetFreeCamera();
    
    // The chase camera is a child of the boat, so it
    // inherits the boat's transformation before applying
    // its own.
    chaseCam = new Camera();
    chaseCam->position = Vector3(0, 5, -5);
    chaseCam->rotation = Vector3(30, 0, 0);
    
    // The top camera is pretty much the same as the
    // chase camera, but from a different angle.
    topCam = new Camera();
    topCam->position = Vector3(0, 15, 0);
    topCam->rotation.x = 90;
    
    // The light camera is a child of the searchlight,
    // so it will be automatically rotated to stay
    // behind the searchlight when the searchlight
    // rotates. Easy!
    lightCam = new Camera();
    lightCam->position = Vector3(0, 0.85, -1.1);
    lightCam->setNearClippingDistance(0.1);
    searchlight->addChild(lightCam);
    
    boat->addChild(chaseCam);
    boat->addChild(topCam);
    
    scene->addGameObject(boat);
    scene->addGameObject(water);
    scene->addGameObject(freeCam);
    scene->setActiveCamera(freeCam);
    
    scene->init();
}

void init() {
    /*select clearing (background) color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    createObjects();
    
    //Only draw the things in the front layer
	glEnable(GL_DEPTH_TEST);
}

//reshape will be called at least once when the window is created,
//so we can handle projection matrix work here
void reshape(int width, int height){
	ww= width;
	wh = height;
	//field of view angle, aspect ratio, closest distance from camera to object, largest distance from camera to object
    
    //send over projection matrix to vertex shader
    scene->setAspectRatio((float)width, (float)height);
	
	glViewport(0, 0, width, height);
}

void timer(GLint v) {
    if (keyUpArrow) {
        boat->position.x += sin(boat->rotation.y * DEG_TO_RAD) * boatSpeed;
        boat->position.z += cos(boat->rotation.y * DEG_TO_RAD) * boatSpeed;
        fan->rotation.z += fanSpeed;
    } else if (keyDownArrow) {
        boat->position.x -= sin(boat->rotation.y * DEG_TO_RAD) * boatSpeed;
        boat->position.z -= cos(boat->rotation.y * DEG_TO_RAD) * boatSpeed;
        fan->rotation.z -= fanSpeed;
    }
    
    boat->position.x = clamp(boat->position.x, -waterScale + 1, waterScale - 1);
    boat->position.z = clamp(boat->position.z, -waterScale + 1, waterScale - 1);
    
    if (keyLeftArrow) {
        boat->rotation.y += boatRotateSpeed;
        for (int i = 0; i < numRudders; i++) {
            rudders[i]->rotation.y = -rudderAngle;
        }
    } else if (keyRightArrow) {
        boat->rotation.y -= boatRotateSpeed;
        for (int i = 0; i < numRudders; i++) {
            rudders[i]->rotation.y = rudderAngle;
        }
    } else {
        for (int i = 0; i < numRudders; i++) {
            rudders[i]->rotation.y = 0;
        }
    }
    
    if (keySearchlightCounterclockwise) {
        searchlight->rotation.y += searchlightSpeed;
    } else if (keySearchlightClockwise) {
        searchlight->rotation.y -= searchlightSpeed;
    }
    
    searchlight->rotation.y = clamp(searchlight->rotation.y, -55, 55);
    
    if (keyZoomIn) {
        freeCam->setFOV(freeCam->getFOV() - 1);
    } else if (keyZoomOut) {
        freeCam->setFOV(freeCam->getFOV() + 1);
    }
    
    if (keyDollyIn || keyDollyOut) {
        Vector3 toOrigin = Vector3(0, 0, 0) - freeCam->position;
        GLfloat distanceToOrigin = length(toOrigin);
        
        if (keyDollyIn && distanceToOrigin > cameraDollyMinDistance) {
            freeCam->position += normalize(toOrigin) * cameraDollySpeed;
        } else if (keyDollyOut && distanceToOrigin < cameraDollyMaxDistance) {
            freeCam->position -= normalize(toOrigin) * cameraDollySpeed;
        }
    }
    
	glutPostRedisplay();
	glutTimerFunc(1000 / v, timer, v);
}

int main(int argc, char **argv)
{
    /*set up window for display*/
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0); 
    glutInitWindowSize(ww, wh);
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#else
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutCreateWindow("OpenGL 3.2");

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif
    
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 60);

    glutMainLoop();
    return 0;
}
