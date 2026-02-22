/*
 *  Simple Vector Math Library
 *        Column Major
*/

#ifndef _VLM_H__
#define _VLM_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ----- Vectors ----- */

void VERR(char* msg);

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

Vec3 InitVec3(float  x, float y, float z);
Vec4 InitVec4(float x, float y, float z, float w);

/* Operations */
Vec3 Vec3Add(Vec3 v1, Vec3 v2);
Vec3 Vec3Sub(Vec3 v1, Vec3 v2);
Vec3 Vec3Cross(Vec3 v1, Vec3 v2);
float Vec3Dot(Vec3 v1, Vec3 v2);
Vec3 Vec3Scalar(Vec3 v, float d);

/* Modifiers */
Vec3 Vec3Norm(Vec3 v);

/* ----- Matricies ----- */

void MATERR(char* category, char* msg);

typedef struct Mat {
    unsigned int rows, cols;
    float* data;
} Mat;

Mat InitMat(unsigned int rows, unsigned int cols, float* data);
Mat InitMatIdentity(unsigned int rows, unsigned int cols, float fill);

float MatAt(Mat m, unsigned int row, unsigned int col);
void MatSet(Mat* m, unsigned int row, unsigned int col, float val);

/* Operations */
Mat MatAdd(Mat m1, Mat m2);
Mat MatSub(Mat m1, Mat m2);
Mat MatMult(Mat m1, Mat m2);
Mat MatScalar(Mat m, float d);
Mat MatTranspose(Mat m);
Mat MatInverse(Mat m);

/* Etc Functions */
Mat MatLookAt(Vec3 camPos, Vec3 camTarget, Vec3 worldUp);
Mat MatPerspective(float angle, float aspect, float near, float far);
Mat MatTranslate(Mat m1, Vec3 v);
size_t MatRank(Mat m);

void MatPrint(Mat m);

void MatFree(Mat m);
#endif