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


//void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const float CUBEDIM = 6.0;

class Triangle
{
public:
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
};

const char* vert_shader =
"#version 400\n"
"layout (location = 0) in vec3 vertex_position;\n"
//"layout (location = 1) in vec3 vertex_normal;\n"
"uniform mat4 MVP;\n"
"uniform vec3 cameraloc;\n"
"uniform vec3 lightdir;\n"
"uniform vec4 lightcoeff;\n"
"out float shading_amount;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"   gl_Position = position;\n"
"}\n";

//"   gl_Position = MVP*position;\n"

const char* frag_shader =
"#version 400\n"
"in float shading_amount;\n"
"out vec4 frag_color;\n"
"void main(){\n"
"   frag_color = vec4(0.0, 0.0, 0.0, 1.0);\n"
"}\n";


class Quad
{
public:
    vector<Triangle> face; //cube is made up of 4 visible sides possible 6 for top and bottom
};



GLFWwindow* SetUpWindow()
{

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

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


GLuint SetUpBox()
{
    float tri_points[] =
    {
        //each line represents one triangle of each respective quad
        /*
        2, -2, -2, -2, 2 , -2, -2, -2, -2, //-z quad
        2, -2, -2, -2, 2, -2, 2, 2, -2
        */
        
       /* -6, 6, 6, -6, -6, 6, 6, 6, 6, //+z quad
         6, -6, 6, -6, -6, 6, 6, 6, 6,*/

          0.5f, 0.0f, 0.0f,
          0.0f, 0.0f, 0.0f,
          0.0f, 0.5f, 0.0f,
          -0.5f, 0.0f, 0.0f
        
    };

    int tri_indices[] =
    {
        0, 1, 2,
        1, 2, 3
    };

    //the vector pointing from each vertex to the origin is just (0,0,0) - vertex
    //so take the negative of each element of tri_points
    float tri_normals[18]
    {
        -2, 2, 2, 2, -2 , 2, 2, 2, 2, //-z quad normals
        -2, 2, 2, 2, -2, 2, -2, -2, 2

    };

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);//get handle
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);//what type of data points works on GL_ARRAY_BUFFER type
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), tri_points, GL_STATIC_DRAW);

    GLuint normals_vbo = 0;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), tri_normals, GL_STATIC_DRAW);

    GLuint indices_vbo = 0;
    glGenBuffers(1, &indices_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), tri_indices, GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    return vao;



}

//A lot of the initialization code is borrowed from project2A
int main()
{   
    GLFWwindow* window = SetUpWindow();
    //glViewport(0, 0, 800, 800);

    //set up data to render
    GLuint vao = SetUpBox();

    const char* vertex_shader = vert_shader;
    const char* fragment_shader = frag_shader;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL); //this tells gl that vertex_shader is the source and vs is where it goes
    glCompileShader(vs);
    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params); //did it compile?
    if (GL_TRUE != params) {
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
        //_print_shader_info_log(vs);
        exit(EXIT_FAILURE);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params) {
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", fs);
       // _print_shader_info_log(fs);
        exit(EXIT_FAILURE);
    }

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs); //i intend to attach fs
    glAttachShader(shader_programme, vs); //i intend to attach vs
    glLinkProgram(shader_programme); //this means as prog executing it will use this shader

    glUseProgram(shader_programme);

    //CAMERA TRANSFORMATIONS
    //projection matrix 
    //  fov:           30deg
    //  display size:  1000x1000
    //  display range: 5 <-> 200
    glm::mat4 Projection = glm::perspective(
        glm::radians(30.0f), (float)800 / (float)800, 5.0f, 200.0f);
    glm::vec3 origin(0, 0, 0);
    glm::vec3 up(0, 1, 0);
    glm::vec3 camera(0, 0, -5);
    //Camera matrix
    glm::mat4 View = glm::lookAt(
        camera, // camera in world space
        origin, // looks at the origin
        up      // and the head is up
    );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;

    GLuint mvploc = glGetUniformLocation(shader_programme, "MVP");

    //send transformation to the currently bound shader
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);

    //SHADING PARAMETERS
    GLuint camloc = glGetUniformLocation(shader_programme, "cameraloc");
    glUniform3fv(camloc, 1, &camera[0]);
    glm::vec3 lightdir = glm::normalize(camera - origin);
    GLuint ldirloc = glGetUniformLocation(shader_programme, "lightdir");
    glUniform3fv(ldirloc, 1, &lightdir[0]);
    
    glm::vec4 lightcoeff(0.2, 0.5, 2, 50);
    GLuint lcoeloc = glGetUniformLocation(shader_programme, "lightcoeff");
    glUniform4fv(lcoeloc, 1, &lightcoeff[0]);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}