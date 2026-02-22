#include "Camera.h"

Camera* InitCamera(Vec3 pos, Vec3 front, Vec3 up) {
    Camera* cam = malloc(sizeof(Camera));

    /* Directions */
    cam->pos = pos; 
    cam->target = Vec3Add(front, pos);
    cam->dir = Vec3Norm(Vec3Sub(pos, cam->target));

    cam->right = Vec3Norm(Vec3Cross(up, cam->dir));
    cam->up = Vec3Cross(cam->dir, cam->right);

    /* View Matrix */
    cam->view = MatLookAt(pos, cam->target, up);
    return cam;
}