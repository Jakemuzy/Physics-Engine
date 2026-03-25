#include "Vlm.h"

void VERR(char* msg)
{
    printf("%s\n", msg);
}

/* ----- Vectors ----- */

Vec3 InitVec3(float x, float y, float z) { return (Vec3){x, y, z}; };
Vec4 InitVec4(float x, float y, float z, float w) { return (Vec4){x, y, z, w}; };

/* Operations */
Vec3 Vec3Add(Vec3 v1, Vec3 v2) {
    return (Vec3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
Vec3 Vec3Sub(Vec3 v1, Vec3 v2) {
    return (Vec3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
Vec3 Vec3Cross(Vec3 v1, Vec3 v2) {
    return (Vec3){ 
        (v1.y * v2.z - v1.z * v2.y), 
        (v1.z * v2.x - v1.x * v2.z),
        (v1.x * v2.y - v1.y * v2.x)
    };
}
float Vec3Dot(Vec3 v1, Vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vec3 Vec3Scalar(Vec3 v, float d) {
    return (Vec3){ v.x * d, v.y * d, v.z * d };
}

/* Modifiers */
Vec3 Vec3Norm(Vec3 v) {
    float r = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    return (Vec3){ v.x / r, v.y / r, v.z / r };
}

/* ----- Matricies ----- */
void MATERR(char* category, char* msg) { printf("MATRIX:%s:ERROR: %s\n", category, msg); }

Mat InitMat(unsigned int rows, unsigned int cols, float* data) {
    Mat m = (Mat){rows, cols, malloc(sizeof(float) * rows * cols)};
    for (size_t i = 0; i < rows * cols; i ++) 
        m.data[i] = data[i];
    
    return m;
}

Mat InitMatIdentity(unsigned int rows, unsigned int cols, float fill)
{
    /* Unreadable method to create diagonal pattern */
    int index = 0;
    Mat m = (Mat){rows, cols, malloc(sizeof(float) * rows * cols)};
    for (size_t i = 0; i < rows * cols; i ++) 
        m.data[i] = i == index ? index += rows + 1, fill : 0;
    
    return m;
}

float MatAt(Mat m, unsigned int row, unsigned int col) {
    return m.data[row + col * m.rows];
}

void MatSet(Mat* m, unsigned int row, unsigned int col, float val) {
    m->data[row + col * m->rows] = val;
}


/* Operations */
Mat MatAdd(Mat m1, Mat m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) { MATERR("ADD", "Size mismatch"); return m1; }

    Mat m = (Mat){m1.rows, m1.cols, malloc(sizeof(float) * m1.rows * m1.cols)};
    for (size_t i = 0; i < m1.rows * m1.cols; i++) {
        m.data[i] = m1.data[i] + m2.data[i];
    }

    return m;
}

Mat MatSub(Mat m1, Mat m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) { MATERR("SUB", "Size mismatch"); return m1; }

    Mat m = (Mat){m1.rows, m1.cols, malloc(sizeof(float) * m1.rows * m1.cols)};
    for (size_t i = 0; i < m1.rows * m1.cols; i++) {
        m.data[i] = m1.data[i] - m2.data[i];
    }

    return m;
}

Mat MatMult(Mat m1, Mat m2) {
    if (m1.cols != m2.rows) { MATERR("MULT", "Size mismatch"); return m1; }

    Mat m = (Mat){m1.rows, m2.cols, malloc(sizeof(float) * m1.rows * m2.cols) };
    for (size_t i = 0; i < m1.rows; i++) {
        for (size_t j = 0; j < m2.cols; j++) {
            float d = 0;
            for (size_t k = 0; k < m1.cols; k++) 
                d += MatAt(m1, i, k) * MatAt(m2, k, j);
            MatSet(&m, i, j, d);
        }
    }

    return m;
}

Mat MatScalar(Mat m, float d) {
    Mat newm = (Mat){m.rows, m.cols, malloc(sizeof(float) * m.rows * m.cols)};
    for (size_t i = 0; i < m.rows * m.cols; i++) {
        newm.data[i] = m.data[i] * d;
    }
    return newm;
}

Mat MatTranspose(Mat m);

Mat MatInverse(Mat m);



size_t MatRank(Mat m);

Mat MatLookAt(Vec3 eye, Vec3 center, Vec3 worldUp) {
    Vec3 f = Vec3Norm(Vec3Sub(center, eye));    // forward
    Vec3 s = Vec3Norm(Vec3Cross(f, worldUp));   // right
    Vec3 u = Vec3Cross(s, f);                   // up

    float data[16] = {
        s.x,  u.x,  -f.x,  0.0f,
        s.y,  u.y,  -f.y,  0.0f,
        s.z,  u.z,  -f.z,  0.0f,
        -Vec3Dot(s, eye), -Vec3Dot(u, eye), Vec3Dot(f, eye), 1.0f
    };

    return InitMat(4, 4, data);
}

Mat MatPerspective(float angle, float aspect, float near, float far) 
{
    float fovRad = angle * (3.14159265359f / 180.0f);
    float f = 1.0f / tanf(fovRad / 2.0f);

    float data[16] = {
        f/aspect, 0.0f, 0.0f, 0.0f,
        0.0f,    f,    0.0f, 0.0f,
        0.0f,    0.0f, -(far+near)/(far-near), -1.0f,
        0.0f,    0.0f, -(2*far*near)/(far-near), 0.0f
    };

    return InitMat(4, 4, data);
}

Mat MatTranslate(Mat m1, Vec3 v) 
{
    /* TODO: make this generic */
    if (m1.rows != 4 || m1.cols != 4) { MATERR("TRANSLATE", "Size mismatch"); return m1; }

    Mat result = m1;
    result.data[12] += v.x; // col 4, row 1
    result.data[13] += v.y; // col 4, row 2
    result.data[14] += v.z; // col 4, row 3
    return result;
}



void MatPrint(Mat m)
{
    for (unsigned int r = 0; r < m.rows; r++) {
        for (unsigned int c = 0; c < m.cols; c++) {
            printf("%8.3f ", m.data[r * m.cols + c]);
        }
        printf("\n");
    }
}


void MatFree(Mat m) 
{
    free(m.data);
}