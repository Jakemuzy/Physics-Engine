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
    double x, y, z;
} Vec3;

typedef struct Vec4 {
    double x, y, z, w;
} Vec4;

Vec3 InitVec3(double  x, double y, double z);
Vec4 InitVec4(double x, double y, double z, double w);

/* Operations */
Vec3 Vec3Add(Vec3 v1, Vec3 v2);
Vec3 Vec3Sub(Vec3 v1, Vec3 v2);
Vec3 Vec3Cross(Vec3 v1, Vec3 v2);
double Vec3Dot(Vec3 v1, Vec3 v2);
Vec3 Vec3Scalar(Vec3 v, double d);

/* Modifiers */
Vec3 VecNorm(Vec3 v1);

/* ----- Matricies ----- */

void MATERR(char* category, char* msg);

typedef struct Mat {
    unsigned int rows, cols;
    double* data;
} Mat;

Mat InitMat(unsigned int rows, unsigned int cols, double* data);
double MatAt(Mat m, unsigned int row, unsigned int col);
void MatSet(Mat* m, unsigned int row, unsigned int col, double val);

Mat MatAdd(Mat m1, Mat m2);
Mat MatSub(Mat m1, Mat m2);
Mat MatMult(Mat m1, Mat m2);
Mat MatScalar(Mat m, double d);
Mat MatTrans(Mat m);
Mat MatInverse(Mat m);

size_t MatRank(Mat m);
/* Modifiers */

void MatFree(Mat m);
#endif