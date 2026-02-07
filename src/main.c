#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vlm.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    Window* win = WindowInit("Physics", 800, 600);
    
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

    InitMat(2, 2, (double[]){1, 2, 3, 4});


    int vertexCount = 36;
    Mesh* mesh = MeshInit("tri", cubeVertices, vertexCount, true, false, false);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(win->wptr))
    {
        processInput(win->wptr);

        glClearColor(0.15f, 0.43f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLuint sprog = ShaderProgUse("BasicShader");
        MeshDraw("tri");

        glfwSwapBuffers(win->wptr);
        glfwPollEvents();
    }

    MeshsTerminate();
    ShadersTerminate();
    WindowsTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (!window)
        printf("INVALID WINDOW\n");
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
        printf("E");
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
}


