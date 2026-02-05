#include "Shader.h"

Map* ShaderPrograms;

/* ------ Lifetime Handling ----- */

void SHERR(GLuint shdr)
{
    char log[512];
    glGetShaderInfoLog(shdr, 512, NULL, log);
    printf("SHADER ERROR: %s\n", log); 
}

/* ------ Shader Logic ----- */

/* TODO: Make variadic */
GLuint ShaderProgInit(char* shaderProgName, char* vertPath, char* fragPath)
{
    if (!ShaderPrograms)
        ShaderPrograms = MapInit();

    const char* vertTxt = ReadShaderFromFile(vertPath);
    const char* fragTxt = ReadShaderFromFile(fragPath);
    GLuint vert = ShaderInit(GL_VERTEX_SHADER, vertTxt);
    GLuint frag = ShaderInit(GL_FRAGMENT_SHADER, fragTxt);

    GLuint shdrProg = glCreateProgram();
    glAttachShader(shdrProg, vert);
    glAttachShader(shdrProg, frag);
    glLinkProgram(shdrProg);

    int success;
    glGetProgramiv(shdrProg, GL_LINK_STATUS, &success);
    if (!success) {
        SHERR(shdrProg);
        return SHDR_ERR;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    MapPush(ShaderPrograms, shaderProgName, (void*)(uintptr_t)shdrProg);
    return shdrProg;
}

/* TODO: Allow for multiple shader creation via 2nd and 4th param */
GLuint ShaderInit(GLenum stype, const char* src)
{
    GLuint shdr = glCreateShader(stype);
    glShaderSource(shdr, 1, &src, NULL);
    glCompileShader(shdr);

    int success;
    glGetShaderiv(shdr, GL_COMPILE_STATUS, &success);
    if (!success) { 
        SHERR(shdr);
        return SHDR_ERR;
    }
    return shdr;
}

GLuint ShaderProgUse(char* shaderProgName)
{
    void* prog = MapLook(ShaderPrograms, shaderProgName);
    if (!prog) { printf("SHADER USE ERROR: No shader with name: %s\n", shaderProgName); return -1; }

    GLuint sprog = (GLuint)(uintptr_t)prog;
    glUseProgram(sprog);
    return sprog;
}

void ShaderSetVal(char* progName, char* varName, UNIFORM_TYPE type, void* value) 
{
    GLuint sprog = ShaderProgUse(progName);
    if (sprog == -1) return;

    GLint loc = glGetUniformLocation(sprog, varName);
    if (loc == -1) { printf("SHADER UNIFORM ERROR: No uniform with name: %s\n", varName); return; }

    switch (type)
    {
        case U_FLOAT:        glUniform1fv(loc, 1, (float*)value); break;
        case U_FLOAT2:       glUniform2fv(loc, 1, (float*)value); break;
        case U_FLOAT3:       glUniform3fv(loc, 1, (float*)value); break;
        case U_FLOAT4:       glUniform4fv(loc, 1, (float*)value); break;

        case U_DOUBLE:       glUniform1dv(loc, 1, (double*)value); break;
        case U_DOUBLE2:      glUniform2dv(loc, 1, (double*)value); break;
        case U_DOUBLE3:      glUniform3dv(loc, 1, (double*)value); break;
        case U_DOUBLE4:      glUniform4dv(loc, 1, (double*)value); break;

        case U_INT:          glUniform1iv(loc, 1, (int*)value); break;
        case U_INT2:         glUniform2iv(loc, 1, (int*)value); break;
        case U_INT3:         glUniform3iv(loc, 1, (int*)value); break;
        case U_INT4:         glUniform4iv(loc, 1, (int*)value); break;

        case U_UINT:         glUniform1uiv(loc, 1, (unsigned int*)value); break;
        case U_UINT2:        glUniform2uiv(loc, 1, (unsigned int*)value); break;
        case U_UINT3:        glUniform3uiv(loc, 1, (unsigned int*)value); break;
        case U_UINT4:        glUniform4uiv(loc, 1, (unsigned int*)value); break;

        case U_BOOL:         glUniform1iv(loc, 1, (int*)value); break;
        case U_BOOL2:        glUniform2iv(loc, 1, (int*)value); break;
        case U_BOOL3:        glUniform3iv(loc, 1, (int*)value); break;
        case U_BOOL4:        glUniform4iv(loc, 1, (int*)value); break;

        case U_MAT2:         glUniformMatrix2fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT3:         glUniformMatrix3fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT4:         glUniformMatrix4fv(loc, 1, GL_FALSE, (float*)value); break;

        case U_MAT2x3:       glUniformMatrix2x3fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT3x2:       glUniformMatrix3x2fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT2x4:       glUniformMatrix2x4fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT4x2:       glUniformMatrix4x2fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT3x4:       glUniformMatrix3x4fv(loc, 1, GL_FALSE, (float*)value); break;
        case U_MAT4x3:       glUniformMatrix4x3fv(loc, 1, GL_FALSE, (float*)value); break;

        case U_SAMPLER_1D:
        case U_SAMPLER_2D:
        case U_SAMPLER_3D:
        case U_SAMPLER_CUBE:
        case U_SAMPLER_1D_ARRAY:
        case U_SAMPLER_2D_ARRAY:
        case U_SAMPLER_CUBE_ARRAY:
        case U_SAMPLER_2D_SHADOW:
        case U_SAMPLER_CUBE_SHADOW:
            glUniform1iv(loc, 1, (int*)value);
            break;

        case U_IMAGE_1D:
        case U_IMAGE_2D:
        case U_IMAGE_3D:
        case U_IMAGE_CUBE:
        case U_IMAGE_2D_ARRAY:
            glUniform1iv(loc, 1, (int*)value);
            break;
    }
}

void ShadersTerminate()
{
    //MapFree(ShaderPrograms);
}

/* ----- Helpers ------ */

char* ReadShaderFromFile(char* fpath)
{
    FILE* fptr;
    fptr = fopen(fpath, "r");
    if (!fptr) { printf("FILE ERROR: Unable to open file %s\n", fpath); return NULL; }

    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char* buffer = malloc(sizeof(char) * (fsize + 1));
    size_t bytesRead = fread(buffer, 1, fsize, fptr);

    buffer[bytesRead] = '\0';
    fclose(fptr);
    return buffer;
}
