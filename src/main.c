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
void processInput(GLFWwindow *window);

int main()
{
    Window* win = WindowInit("Physics", 800, 600);
    InputHandler* ih = InputHandlerInit(win);
    
    glfwSetFramebufferSizeCallback(win->wptr, framebuffer_size_callback);
    LoadGlad();

    //AttachInput(ih, "Escape", GLFW_KEY_ESCAPE, PRESS, glfwSetWindowShouldClose(win, true));

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

    const float radius = 3.0f;
    Camera* cam = InitCamera(
        InitVec3(0.0, 0.0, 3.0),
        InitVec3(0.0, 0.0, 0.0),
        InitVec3(0.0, 1.0, 0.0)
    );
   
    Mat identity = InitMatIdentity(4,4,1);
    Mat proj = MatPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    ShaderSetVal("BasicShader", "model", U_MAT4, identity.data);
    ShaderSetVal("BasicShader", "proj", U_MAT4, proj.data);

    int vertexCount = 36;
    Mesh* mesh = MeshInit("tri", cubeVertices, vertexCount, true, false, false);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(win->wptr))
    {
        processInput(win->wptr);

        glClearColor(0.15f, 0.43f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float camx = sin(glfwGetTime()) * radius;
        float camz = cos(glfwGetTime()) * radius;
        
        cam->view = MatLookAt(
            InitVec3(camx, 0.0, camz),
            InitVec3(0.0, 0.0, 0.0),
            InitVec3(0.0, 1.0, 0.0)
        );

        GLuint sprog = ShaderProgUse("BasicShader"); /* Not required SetVal does this */
        ShaderSetVal("BasicShader", "model", U_MAT4, identity.data);
        ShaderSetVal("BasicShader", "view", U_MAT4, (void*)cam->view.data);
        ShaderSetVal("BasicShader", "proj", U_MAT4, proj.data);
        MeshDraw("tri");

        glfwSwapBuffers(win->wptr);
        glfwPollEvents();
    }

    MeshsTerminate();
    ShadersTerminate();
    WindowsTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (!window)
        printf("INVALID WINDOW\n");
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
        printf("E");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
}


