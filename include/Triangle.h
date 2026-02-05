/*
 *  Triangle Structures For OpenGL
 *  ------------------------------
 *   Stores Triangle Information
 *    For VAO and Shader Manip
*/

#ifndef _TRIANGLE_H__
#define _TRIANGLE_H__

/* ----- Triangle Logic ----- */

typedef struct Vec3 { float x, y, z; } Vec3;

typedef struct Vertex {
    Vec3 coord;
    Vec3 color;
    Vec3 normal;
    Vec3 tcoord;
    bool hasColor, hasNormal, hasTcoord;
} Vertex;

typedef struct Triangle {
    Vertex verts[3]; 
} Triangle;

/* ----- Helper Functions ----- */

Vec3 Color(float r, float g, float b);
Vec3 Coord(float x, float y, float z);
Vec3 Normal(float x, float y, float z);
Vec3 TexCoord(float u, float v, float w);

#endif 
