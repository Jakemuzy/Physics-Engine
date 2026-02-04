#include "Window.h"

Map* Windows = NULL;

/* ----- Lifetime Handling ----- */ 

void WERR(char* msg) {
    printf("%s\n", msg);
}

/* ----- Window Logic ----- */

Window* WindowInit(char* name, int width, int height)
{
    if (!WGLFW_INITIALIZED) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        Windows = MapInit();        
        WGLFW_INITIALIZED = true;
    }

    Window* win = malloc(sizeof(Window));
    win->wptr = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!win->wptr) { WERR("GLFW window creation failed"); WindowsTerminate(); return NULL; }

    glfwMakeContextCurrent(win->wptr);
    MapPush(Windows, name, (void*)win);
    return win;
}

void WindowsTerminate()
{
    glfwTerminate();
    MapFree(Windows);
    WGLFW_INITIALIZED = false;
}

void WindowSwap(char* name)
{
    Window* win = (Window*)MapLook(Windows, name);
    if(!win) { WERR("Window with name does not exist\n"); return; }

    glfwMakeContextCurrent(win->wptr);
}


int LoadGlad() 
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        WERR("GLAD failed to initalize");
        return 0;
    }
    return 1;
}
