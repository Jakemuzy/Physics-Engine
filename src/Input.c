#include "Input.h"

/* ----- Error Handling ------ */

void INPERR(char* msg)
{
    printf("INPUT ERROR: %s\n", msg);
}

/* ----- Input Logic ------ */

InputHandler* InputHandlerInit(Window* target) 
{
    InputHandler* ih = malloc(sizeof(InputHandler));
    ih->target = target;

    ih->count = 0;
    ih->max = IH_MAX;
    ih->callbacks = calloc(ih->max, sizeof(InputAction));
    return ih;
}

void AttachInput(InputHandler* handler, char* name, GLint key, InputType type, void (*callback)(void))
{
    if (handler->count >= handler->max) {
        handler->max *= 2;
        handler->callbacks = realloc(handler->callbacks, handler->max * sizeof(InputAction));
    }

    handler->callbacks[handler->count] = (InputAction){name, key, type, callback};
    handler->count++;
}

void ProcessInputs(InputHandler* handler)
{
    for (size_t i = 0; i < handler->count; i++) {
        InputAction ia = handler->callbacks[i];

        if (glfwGetKey(handler->target->wptr, ia.key) == ia.type) 
            ia.action();
    }
}