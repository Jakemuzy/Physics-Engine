#ifndef _SHAPES_H__
#define _SHAPES_H__

#include "Vlm.h"

#define SHAPE_ATTRIBUTE_NULL NULL

typedef struct Shape {
    float* vertices;
    float* normals;
    float* colors;

    size_t triCount;
} Shape;

Shape GenerateShape()

#endif
