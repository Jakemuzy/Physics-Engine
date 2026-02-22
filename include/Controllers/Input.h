/*
 *   Input Controller for OpenGL
 *  -----------------------------
 *      Attach Callbacks For 
 *          Input Keys
*/

#ifndef _INPUT_HANDLER_H__
#define _INPUT_HANDLER_H__

#include "Window.h"

/* ----- Error Handling ------ */

void INPERR(char* msg);

/* ----- Input Logic ------ */

#define IH_MAX 4

typedef enum InputType {
    PRESS = GLFW_PRESS,
    RELEASE = GLFW_RELEASE,
    HOLD 
} InputType;

typedef struct InputAction {
    char* name;

    GLint key;
    InputType type;

    void (*action)(void);
} InputAction;

typedef struct InputHandler {
    /* Should lowk be a map based on # of opengl keys */
    InputAction* callbacks; 
    size_t count, max;

    Window* target;
} InputHandler;

InputHandler* InputHandlerInit(Window* target);

void AttachInput(InputHandler* handler, char* name, GLint key, InputType type, void (*callback)(void));
void ProcessInputs(InputHandler* handler);

#endif