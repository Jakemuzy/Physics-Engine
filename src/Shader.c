#include "Shader.h"

Map* ShaderPrograms;

/* ------ Lifetime Handling ----- */

void SHERR(unsigned int shdr)
{
    char log[512];
    glGetShaderInfoLog(shdr, 512, NULL, log);
    printf("SHADER ERROR: %s\n", log); 
}

/* ------ Shader Logic ----- */

/* TODO: Make variadic */
unsigned int ShaderProgInit(const char* vertPath, const char* fragPath)
{
    char* vertTxt, *fragTxt;  /* TODO: Read from file */
    unsigned int vert = ShaderInit(GL_VERTEX_SHADER, vertPath);
    unsigned int frag = ShaderInit(GL_FRAGMENT_SHADER, fragPath);

    unsigned int shdrProg = glCreateProgram();
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
    glDeleteShader(vert);

    /* TODO: Add to map, variadic delete */
    return shdrProg;
}

/* TODO: Allow for multiple shader creation via 2nd and 4th param */
unsigned int ShaderInit(GLenum stype, const char* src)
{
    unsigned int shdr = glCreateShader(stype);
    glShaderSource(shdr, 1, &src, NULL);
    glCompileShader(shdr);

    int success;
    glGetShaderiv(shdr, stype, &success);
    if (!success) { 
        SHERR(shdr);
        return SHDR_ERR;
    }
    return shdr;
}

char* ReadShaderFromFile(char* fpath)
{
    /* Read From file */
}
