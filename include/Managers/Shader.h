
/* 
 *  Shader Manager for OpenGL
 *  -------------------------
 *      Initalizes Glad 
 *         and GLFW
*/ 

#ifndef _SHADER_MANAGER_H__
#define _SHADER_MANAGER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "Map.h"

#define SHDR_ERR -1     /* TODO: -1 is stupid since funcs return unsigned */
#define MAX_SHDRS 10

/* ----- Lifetime Handling ------ */

void SHERR(GLuint shdr);

/* ----- Shader Logic ------ */

typedef enum UNIFORM_TYPE {
    U_DOUBLE, U_DOUBLE2, U_DOUBLE3, U_DOUBLE4,
    U_FLOAT, U_FLOAT2, U_FLOAT3, U_FLOAT4,
    U_UINT, U_UINT2, U_UINT3, U_UINT4,
    U_INT, U_INT2, U_INT3, U_INT4, 

    U_BOOL,    U_BOOL2,    U_BOOL3,    U_BOOL4,

    U_MAT2,    U_MAT3,    U_MAT4,
    U_MAT2x3,  U_MAT3x2,
    U_MAT2x4,  U_MAT4x2,
    U_MAT3x4,  U_MAT4x3,

    U_SAMPLER_1D,
    U_SAMPLER_2D,
    U_SAMPLER_3D,
    U_SAMPLER_CUBE,
    U_SAMPLER_1D_ARRAY,
    U_SAMPLER_2D_ARRAY,
    U_SAMPLER_CUBE_ARRAY,
    U_SAMPLER_2D_SHADOW,
    U_SAMPLER_CUBE_SHADOW,

    U_IMAGE_1D,
    U_IMAGE_2D,
    U_IMAGE_3D,
    U_IMAGE_CUBE,
    U_IMAGE_2D_ARRAY
    
} UNIFORM_TYPE;

typedef GLuint Shader;
typedef struct ShaderProg {
    GLuint prog; 
    Map* shdrs;
} ShaderProg;
extern Map* ShaderPrograms;

GLuint ShaderProgInit(char* shaderProgName, char* vertPath, char* fragPath);
GLuint ShaderInit(GLenum stype, const char* src);

GLuint ShaderProgUse(char* shaderProgName);
void ShaderSetVal(char* progName, char* varName, UNIFORM_TYPE type, void* value);
void ShadersTerminate(); 


/* ----- Helpers ----- */

char*        ReadShaderFromFile(char* fpath);


#endif
