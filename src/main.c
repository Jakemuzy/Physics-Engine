#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "Window.h"
#include "Input.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vlm.h"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static Camera* cam;

int main()
{
    // Must be set before window because the framebuffer_size_callback
    // directly depends on camera, and if it isn't set, program crashes
    cam = InitCamera(
        InitVec3(3.0, 0.0, 0.0),
        InitVec3(-2.0, 0.0, 0.0),
        InitVec3(0.0, 1.0, 0.0)
    );
    SetCameraProj(cam, 800.0f, 600.0f);


    Window* win = WindowInit("Physics", 800, 600);
    InputHandler* ih = InputHandlerInit(win);
   

    // Framebuffer size callback should live in the shared space between window and 
    // camera controller
    glfwSetFramebufferSizeCallback(win->wptr, framebuffer_size_callback);

    LoadGlad();

    Shader shdr = ShaderProgInit("BasicShader", "shaders/v1.vs", "shaders/f1.fs");

    float cubeVertices[] = {
        // Back face (soft red)
        -0.5f, -0.5f, -0.5f,  1.0f,0.6f,0.6f,
         0.5f, -0.5f, -0.5f,  0.9f,0.5f,0.5f,
         0.5f,  0.5f, -0.5f,  0.8f,0.4f,0.4f,
         0.5f,  0.5f, -0.5f,  0.8f,0.4f,0.4f,
        -0.5f,  0.5f, -0.5f,  0.9f,0.5f,0.5f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.6f,0.6f,

        // Front face (soft green)
        -0.5f, -0.5f, 0.5f,   0.6f,1.0f,0.6f,
         0.5f, -0.5f, 0.5f,   0.5f,0.9f,0.5f,
         0.5f, 0.5f, 0.5f,    0.4f,0.8f,0.4f,
         0.5f, 0.5f, 0.5f,    0.4f,0.8f,0.4f,
        -0.5f, 0.5f, 0.5f,    0.5f,0.9f,0.5f,
        -0.5f, -0.5f, 0.5f,   0.6f,1.0f,0.6f,

        // Left face (soft blue)
        -0.5f,  0.5f,  0.5f,  0.6f,0.8f,1.0f,
        -0.5f,  0.5f, -0.5f,  0.5f,0.7f,0.9f,
        -0.5f, -0.5f, -0.5f,  0.4f,0.6f,0.8f,
        -0.5f, -0.5f, -0.5f,  0.4f,0.6f,0.8f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.7f,0.9f,
        -0.5f,  0.5f,  0.5f,  0.6f,0.8f,1.0f,

        // Right face (soft yellow)
         0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.6f,
         0.5f,  0.5f, -0.5f,  0.9f,0.9f,0.5f,
         0.5f, -0.5f, -0.5f,  0.8f,0.8f,0.4f,
         0.5f, -0.5f, -0.5f,  0.8f,0.8f,0.4f,
         0.5f, -0.5f,  0.5f,  0.9f,0.9f,0.5f,
         0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.6f,

        // Bottom face (soft purple)
        -0.5f, -0.5f, -0.5f,  0.8f,0.6f,0.9f,
         0.5f, -0.5f, -0.5f,  0.7f,0.5f,0.8f,
         0.5f, -0.5f,  0.5f,  0.6f,0.4f,0.7f,
         0.5f, -0.5f,  0.5f,  0.6f,0.4f,0.7f,
        -0.5f, -0.5f,  0.5f,  0.7f,0.5f,0.8f,
        -0.5f, -0.5f, -0.5f,  0.8f,0.6f,0.9f,

        // Top face (soft cyan)
        -0.5f, 0.5f, -0.5f,   0.6f,1.0f,1.0f,
         0.5f, 0.5f, -0.5f,   0.5f,0.9f,0.9f,
         0.5f, 0.5f,  0.5f,   0.4f,0.8f,0.8f,
         0.5f, 0.5f,  0.5f,   0.4f,0.8f,0.8f,
        -0.5f, 0.5f,  0.5f,   0.5f,0.9f,0.9f,
        -0.5f, 0.5f, -0.5f,   0.6f,1.0f,1.0f,
    };
   
    Mat identity = InitMatIdentity(4,4,1);
    ShaderSetVal("BasicShader", "model", U_MAT4, identity.data);
    ShaderSetVal("BasicShader", "proj", U_MAT4, cam->projection.data);

    int vertexCount = 36;
    Mesh* mesh = MeshInit("tri", cubeVertices, vertexCount, true, false, false);

    /* Input settings */
    AttachInput(ih, "Escape", GLFW_KEY_ESCAPE, PRESS, (void*)&WindowClose, win->wptr);
    AttachInput(ih, "Left", GLFW_KEY_A, PRESS, (void*)&CameraLeft, cam);
    AttachInput(ih, "Right", GLFW_KEY_D, PRESS, (void*)&CameraRight, cam);
    AttachInput(ih, "Front", GLFW_KEY_W, PRESS, (void*)&CameraFront, cam);
    AttachInput(ih, "Back", GLFW_KEY_S, PRESS, (void*)&CameraBack, cam);
    AttachInput(ih, "Up", GLFW_KEY_SPACE, PRESS, (void*)&CameraUp, cam);
    AttachInput(ih, "Down", GLFW_KEY_LEFT_SHIFT, PRESS, (void*)&CameraDown, cam);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(win->wptr))
    {
        ProcessInputs(ih);
        //printf("here\n");

        glClearColor(0.15f, 0.43f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLuint sprog = ShaderProgUse("BasicShader"); /* Not required SetVal does this */
        ShaderSetVal("BasicShader", "model", U_MAT4, identity.data);
        ShaderSetVal("BasicShader", "view", U_MAT4, (void*)cam->view.data);
        ShaderSetVal("BasicShader", "proj", U_MAT4, cam->projection.data);
        MeshDraw("tri");

        glfwSwapBuffers(win->wptr);
        glfwPollEvents();
    }

    MeshsTerminate();
    ShadersTerminate();
    WindowsTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    printf("Framebuffer resize\n");
    glViewport(0, 0, width, height);
    SetCameraProj(cam, (float)width, (float)height);
}



