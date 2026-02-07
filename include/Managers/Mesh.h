/* 
 *  Object Manager for OpenGL
 *  -------------------------
 *      Initalizes VAO
 *       VBO and EBOs
*/ 

#ifndef _MESH_H__
#define _MESH_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Map.h"
#include "Triangle.h"

/* ----- Lifetime Handling ----- */

void MERR(char* msg);

/* ----- Mesh Logic ----- */

typedef struct Mesh {
    char* name;
    GLuint VBO, VAO, EBO;
    bool color, normal, tcoord;

    Triangle* tris; /* Will be unused for now */
    unsigned int vertCount;
} Mesh; 
extern Map* Meshs;

/* TODO: Maybe make this triangle, that way normal and texture data can also be initalized */
Mesh* MeshInit(char* name, float* points, int vcount, bool hasColor, bool hasNormal, bool hasTexture);    
void MeshDraw(char* name);
void MeshsTerminate(); 

#endif
