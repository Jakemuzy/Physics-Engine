
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

void SHERR(unsigned int shdr);

/* ----- Shader Logic ------ */

typedef unsigned int Shader;
typedef struct ShaderProg {
    unsigned int prog; 
    Map* shdrs;
} ShaderProg;
extern Map* ShaderPrograms;

unsigned int ShaderProgInit(const char* vertPath, const char* fragPath);
unsigned int ShaderInit(GLenum stype, const char* src);

void ShaderProgUse(char* shaderProgName);
void ShaderProgsTerminate(); 


char*        ReadShaderFromFile(char* fpath);


#endif
