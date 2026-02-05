/* 
 *  Window Manager for OpenGL
 *  -------------------------
 *      Initalizes Glad 
 *         and GLFW
*/ 

#ifndef _WINDOW_MANAGER_H__
#define _WINDOW_MANAGER_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "Map.h"

#define MAJOR 4
#define MINOR 6

#define MAX_WNDWS 10

/* ----- Lifetime Handling ------ */

static bool WGLFW_INITIALIZED = false;
void WERR(char* msg);


/* ----- Window Logic ------ */

typedef struct Window {
    GLFWwindow* wptr;
    char* name;
    unsigned int WIDTH, HEIGHT;
} Window;
extern Map* Windows;

Window* WindowInit(char* name, int width, int height); 
void    WindowsTerminate();
void    WindowSwap(char* name);
void    WindowSwapBuff(Window* window);

void WindowAttachCallback(Window* window, void (*glCallback)(void*), void* glParams, void (userCallback)(void*));

int LoadGlad();

#endif
