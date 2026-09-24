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

    win->name = name;
    win->WIDTH = width;
    win->HEIGHT = height;

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

void WindowClose(void* param)
{
    glfwSetWindowShouldClose((GLFWwindow*)param, true);
}

void WindowSwap(char* name)
{
    Window* win = (Window*)MapLook(Windows, name);
    if(!win) { WERR("Window with name does not exist\n"); return; }

    glfwMakeContextCurrent(win->wptr);
}





void WindowAttachCallback(Window* window, GLFWwindowsizefun glFunc, void (userCallback)(void*), void* userParams)
{
    userCallback(userParams); 
    // TODO: 
    // 1.) Attach framebuffer_size_callback, and a custom user callback
      //  framebuffer_size_callback will update glView() with the framebuffer size
      //  custom user callback will update the persepective matrix (prefarably in the camera)
   
    //glfwSetWindowSizeCallback(window->wptr, window_size_callback)

    // Honestly what we could do is pass glfwSetWindowSizeCallback(window->wptr, with the actual callback)
    //and then pass any custom functions as well as any custom params 

}





int LoadGlad() 
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        WERR("GLAD failed to initalize");
        return 0;
    }
    return 1;
}
