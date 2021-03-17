#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <cmath>

namespace
{
    void errorCallback(int error, const char *description)
    {
        fprintf(stderr, "GLFW error %d: %s\n", error, description);
    }

    GLFWwindow *initialize()
    {
        int glfwInitRes = glfwInit();
        if (!glfwInitRes)
        {
            fprintf(stderr, "Unable to initialize GLFW\n");
            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow *window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
        if (!window)
        {
            fprintf(stderr, "Unable to create GLFW window\n");
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);

        int gladInitRes = gladLoadGL();
        if (!gladInitRes)
        {
            fprintf(stderr, "Unable to initialize glad\n");
            glfwDestroyWindow(window);
            glfwTerminate();
            return nullptr;
        }

        return window;
    }
}

int main(int argc, char *argv[])
{
    glfwSetErrorCallback(errorCallback);

    GLFWwindow *window = initialize();
    if (!window)
    {
        return 0;
    }

    int cnt = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        const GLfloat color[] = {
            sinf(cnt) * 0.5f + 0.5f,
            cosf(cnt) + 0.5f + 0.5f,
            0.0f,
            1.0f};
        glClearBufferfv(GL_COLOR, 0, color);
        cnt++;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}