#include "Vlm.h"

void VERR(char* msg)
{
    printf("%s\n", msg);
}

/* ----- Vectors ----- */

Vec3 InitVec3(double x, double y, double z) { return (Vec3){x, y, z}; };
Vec4 InitVec4(double x, double y, double z, double w) { return (Vec4){x, y, z, w}; };

/* Operations */
Vec3 VecAdd(Vec3 v1, Vec3 v2) {
    return (Vec3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
Vec3 VecSub(Vec3 v1, Vec3 v2) {
    return (Vec3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
Vec3 VecCross(Vec3 v1, Vec3 v2) {
    return (Vec3){ 
        (v1.y * v2.z - v1.z * v2.y), 
        (v1.z * v2.x - v1.x * v2.z),
        (v1.x * v2.y - v1.y * v2.x)
    };
}
double VecDot(Vec3 v1, Vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z + v2.z;
}
Vec3 Vec3Scalar(Vec3 v, double d) {
    return (Vec3){ v.x * d, v.y * d, v.z * d };
}

/* Modifiers */
Vec3 Vec3Norm(Vec3 v) {
    double r = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    return (Vec3){ v.x / r, v.y / r, v.z / r };
}

/* ----- Matricies ----- */
void MATERR(char* category, char* msg) { printf("MATRIX:%s:ERROR: %s\n", category, msg); }

Mat InitMat(unsigned int rows, unsigned int cols, double* data) {
    Mat m = (Mat){rows, cols, malloc(sizeof(double) * rows * cols)};
    for (size_t i = 0; i < rows * cols; i ++) 
        m.data[i] = data[i];
    
    return m;
}

double MatAt(Mat m, unsigned int row, unsigned int col) {
    return m.data[row + col * m.rows];
}

void MatSet(Mat* m, unsigned int row, unsigned int col, double val) {
    m->data[row + col * m->rows] = val;
}


/* Operations */
Mat MatAdd(Mat m1, Mat m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) { MATERR("ADD", "Size mismatch"); return m1; }

    Mat m = (Mat){m1.rows, m1.cols, malloc(sizeof(double) * m1.rows * m1.cols)};
    for (size_t i = 0; i < m1.rows * m1.cols; i++) {
        m.data[i] = m1.data[i] + m2.data[i];
    }

    return m;
}

Mat MatSub(Mat m1, Mat m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) { MATERR("SUB", "Size mismatch"); return m1; }

    Mat m = (Mat){m1.rows, m1.cols, malloc(sizeof(double) * m1.rows * m1.cols)};
    for (size_t i = 0; i < m1.rows * m1.cols; i++) {
        m.data[i] = m1.data[i] - m2.data[i];
    }

    return m;
}

Mat MatMult(Mat m1, Mat m2) {
    if (m1.cols != m2.rows) { MATERR("MULT", "Size mismatch"); return m1; }

    Mat m = (Mat){m1.rows, m2.cols, malloc(sizeof(double) * m1.rows * m2.cols) };
    for (size_t i = 0; i < m1.rows; i++) {
        for (size_t j = 0; j < m2.cols; j++) {
            double d = 0;
            for (size_t k = 0; k < m1.cols; k++) 
                d += MatAt(m1, i, k) * MatAt(m2, k, j);
            MatSet(&m, i, j, d);
        }
    }

    return m;
}

Mat MatScalar(Mat m, double d) {
    Mat newm = (Mat){m.rows, m.cols, malloc(sizeof(double) * m.rows * m.cols)};
    for (size_t i = 0; i < m.rows * m.cols; i++) {
        newm.data[i] = m.data[i] * d;
    }
    return newm;
}

Mat MatTrans(Mat m);
Mat MatInverse(Mat m);

size_t MatRank(Mat m);