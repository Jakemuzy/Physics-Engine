/*
 *  Camera Controller for OpenGL
 *  ----------------------------
 *       Camera to Screen 
 *          Projection
*/

#ifndef _CAMERA_CONTROLLER_H
#define _CAMERA_CONTROLLER_H

#define SPEED 2.5f

#include "Window.h"
#include "Vlm.h"

typedef struct Camera {
    /* Math */
    Vec3 pos;
    Vec3 target, dir;
    Vec3 right, up;

    Mat view;

    /* Logic */
    float dt, last;

    /* Controls */
    float speed;
} Camera;

Camera* InitCamera(Vec3 pos, Vec3 front, Vec3 up);
void Input(Camera* cam);


#endif