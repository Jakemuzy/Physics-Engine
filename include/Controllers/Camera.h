/*
 *  Camera Controller for OpenGL
 *  ----------------------------
 *       Camera to Screen 
 *          Projection
*/

#ifndef _CAMERA_CONTROLLER_H
#define _CAMERA_CONTROLLER_H

#define SPEED 0.025f

#include "Window.h"
#include "Vlm.h"

typedef struct Camera {
    /* Math */
    Vec3 pos;
    Vec3 target, dir;
    Vec3 front, right, up;

    Mat view;
    Mat projection;

    /* Logic */
    float dt, last;

    /* Controls */
    float speed;
} Camera;

Camera* InitCamera(Vec3 pos, Vec3 front, Vec3 up);
void SetCameraProj(Camera* cam, float width, float height);


/* Void since input callback system is generic */
void CameraLeft(void* camera);
void CameraRight(void* camera);
void CameraFront(void* camera);
void CameraBack(void* camera);
void CameraUp(void* camera);
void CameraDown(void* camera);


#endif
