#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using     std::endl;
using     std::cerr;


#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/vec3.hpp>   // glm::vec3
#include <glm/glm/vec4.hpp>   // glm::vec4
#include <glm/glm/mat4x4.hpp> // glm::mat4
#include <glm/glm/gtx/string_cast.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale

//class RenderManager;

const char* GetVertexShader();
const char* GetFragmentShader();
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);


class Triangle
{
public:
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
};

class Cube
{
public:
    vector<Triangle> side; //each side is made up of two triangles
    vector<vector<Triangle>> cube; //cube is made up of 4 visible sides possible 6 for top and bottom

};

GLFWwindow* SetUpWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Beginning", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return window;

}

void SetUpVBOS()
{

}

int main()
{   
    GLFWwindow* window = SetUpWindow();
    //glViewport(0, 0, 800, 800);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.05f, 0.52f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}