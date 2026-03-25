#include "Camera.h"

Camera* InitCamera(Vec3 pos, Vec3 front, Vec3 up) {
    Camera* cam = malloc(sizeof(Camera));

    /* Directions */
    cam->pos = pos; 
    cam->target = Vec3Add(front, pos);
    cam->dir = Vec3Norm(Vec3Sub(pos, cam->target));

    cam->front = front;
    cam->right = Vec3Norm(Vec3Cross(up, cam->dir));
    cam->up = Vec3Cross(cam->dir, cam->right);

    /* View Matrix */
    cam->view = MatLookAt(pos, cam->target, up);

    /* Other */
    cam->speed = SPEED;
    return cam;
}

void CameraLeft(void* camera)
{
    Camera* cam = (Camera*)camera;
    Vec3 moveDir = Vec3Scalar(cam->right, cam->speed);
    cam->pos = Vec3Sub(cam->pos, moveDir);
    cam->target = Vec3Add(cam->pos, cam->front);

    MatFree(cam->view);
    cam->view = MatLookAt(cam->pos, cam->target, cam->up); 
}

void CameraRight(void* camera)
{
    Camera* cam = (Camera*)camera;
    Vec3 moveDir = Vec3Scalar(cam->right, cam->speed);
    cam->pos = Vec3Add(cam->pos, moveDir);
    cam->target = Vec3Add(cam->pos, cam->front);

    MatFree(cam->view);
    cam->view = MatLookAt(cam->pos, cam->target, cam->up); 
}

void CameraFront(void* camera)
{
    Camera* cam = (Camera*)camera;
    Vec3 moveDir = Vec3Scalar(cam->front, cam->speed);
    cam->pos = Vec3Add(cam->pos, moveDir);
    cam->target = Vec3Add(cam->pos, cam->front);

    MatFree(cam->view);
    cam->view = MatLookAt(cam->pos, cam->target, cam->up); 
}

void CameraBack(void* camera)
{
    Camera* cam = (Camera*)camera;
    Vec3 moveDir = Vec3Scalar(cam->front, cam->speed);
    cam->pos = Vec3Sub(cam->pos, moveDir);
    cam->target = Vec3Add(cam->pos, cam->front);

    MatFree(cam->view);
    cam->view = MatLookAt(cam->pos, cam->target, cam->up); 
}

void CameraUp(void* camera)
{
    Camera* cam = (Camera*)camera;
    Vec3 moveDir = Vec3Scalar(cam->up, cam->speed);
    cam->pos = Vec3Add(cam->pos, moveDir);
    cam->target = Vec3Add(cam->pos, cam->front);

    MatFree(cam->view);
    cam->view = MatLookAt(cam->pos, cam->target, cam->up); 
}

void CameraDown(void* camera)
{
    Camera* cam = (Camera*)camera;
    Vec3 moveDir = Vec3Scalar(cam->up, cam->speed);
    cam->pos = Vec3Sub(cam->pos, moveDir);
    cam->target = Vec3Add(cam->pos, cam->front);

    MatFree(cam->view);
    cam->view = MatLookAt(cam->pos, cam->target, cam->up); 
}