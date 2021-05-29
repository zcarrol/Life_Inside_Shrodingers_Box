#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ShaderPrograms.h"
#include "QuadData.h"

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

GLFWwindow* SetUpWindow();
GLuint SetUpQuad();

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);



class RenderManager
{
public:
    RenderManager();
    void   SetView();
    void   SetUpQuadShader(const char*, const char*);
    GLuint SetUpQuad(float*, int*, float*, float*);
    void   ModifyFqVar();
    void   ModifyLqVar();
    void   ModifyBqVar();
    void   ModifyRqVar();

    GLFWwindow* window;
    glm::vec3 origin;
    glm::vec3 up;
    glm::vec3 camera;
    glm::mat4 mvp;
    GLuint camloc;
    GLuint ldirloc;
    glm::mat4 Projection;

    //front quad data
    GLuint fQ_vao;
    GLuint fQ_lcoeloc;
    GLuint fQ_varloc;

    //left quad data
    GLuint lQ_vao;
    GLuint lQ_lcoeloc;
    GLuint lQ_varloc;

    //back quad data
    GLuint bQ_vao;
    GLuint bQ_lcoeloc;
    GLuint bQ_varloc;

    //right quad data
    GLuint rQ_vao;
    GLuint rQ_lcoeloc;
    GLuint rQ_varloc;


};

RenderManager::RenderManager()
{
    window = SetUpWindow();
    origin = glm::vec3(0, 0, 0);
    up =     glm::vec3(0, 1, 0);
    camera = glm::vec3(0, 0, 0);

    Projection = glm::perspective(
        glm::radians(45.0f), (float)800 / (float)800, 1.0f, 200.0f);
    fQ_vao = SetUpQuad(fQ_tri_points, fQ_tri_indices, fQ_colors, fQ_tri_normals);
    lQ_vao = SetUpQuad(lQ_tri_points, lQ_tri_indices, lQ_colors, lQ_tri_normals);
    bQ_vao = SetUpQuad(bQ_tri_points, bQ_tri_indices, bQ_colors, bQ_tri_normals);
    rQ_vao = SetUpQuad(rQ_tri_points, rQ_tri_indices, rQ_colors, rQ_tri_normals);

    glm::mat4 View = glm::lookAt(
        camera, // camera in world space
        origin, // looks at the origin
        up      // and the head is up
    );
    glm::mat4 Model = glm::mat4(1.0f);

    mvp = Projection * View * Model;

}

void RenderManager::SetUpQuadShader(const char* v, const char* f)
{
    const char* vertex_shader = v;
    const char* fragment_shader = f;

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

    GLuint mvploc = glGetUniformLocation(shader_programme, "MVP");

    //send transformation to the currently bound shader
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);

    //SHADING PARAMETERS
    camloc = glGetUniformLocation(shader_programme, "cameraloc");
    glUniform3fv(camloc, 1, &camera[0]);

    glm::vec3 lightdir = glm::normalize(origin - camera);
    ldirloc = glGetUniformLocation(shader_programme, "lightdir");
    glUniform3fv(ldirloc, 1, &lightdir[0]);

    glm::vec4 lightcoeff(0.2, 0.4, 0.6, 50);
    fQ_lcoeloc = glGetUniformLocation(shader_programme, "lightcoeff");
    glUniform4fv(fQ_lcoeloc, 1, &lightcoeff[0]);

    fQ_varloc = glGetUniformLocation(shader_programme, "var");
    
    //each quad has its own variable whose value needs to be independant of the other quads
    if (vertex_shader = frontQuad_vert_shader)
        ModifyFqVar();

    else if (vertex_shader = leftQuad_vert_shader)
        ModifyLqVar();

    else if (vertex_shader = backQuad_vert_shader)
        ModifyBqVar();

    else if (vertex_shader = rightQuad_vert_shader)
        ModifyRqVar();
}

void RenderManager::ModifyRqVar()
{
    static GLfloat var = -0.1;
    static bool goingUp = true;
    if (var < 2 * M_PI && goingUp)
        var += 0.01;
    else
    {
        if (var >= 2 * M_PI)
        {
            goingUp = false;
        }
        else if (var <= 0)
        {
            goingUp = true;
            var = -0.1;
        }
        var -= 0.01;
    }

    glUniform1f(rQ_varloc, var);


}

void RenderManager::ModifyBqVar()
{
    static GLfloat var = -0.1;
    static bool goingUp = true;
    if (var < 2 * M_PI && goingUp)
        var += 0.01;
    else
    {
        if (var >= 2 * M_PI)
        {
            goingUp = false;
        }
        else if (var <= 0)
        {
            goingUp = true;
            var = -0.1;
        }
        var -= 0.01;
    }

    glUniform1f(bQ_varloc, var);

}

void RenderManager::ModifyLqVar()
{
    static GLfloat var = -0.1;
    static bool goingUp = true;
    if (var < 2 * M_PI && goingUp)
        var += 0.01;
    else
    {
        if (var >= 2 * M_PI)
        {
            goingUp = false;
        }
        else if (var <= 0)
        {
            goingUp = true;
            var = -0.1;
        }
        var -= 0.01;
    }

    glUniform1f(lQ_varloc, var);

}


void RenderManager::ModifyFqVar()
{
    static GLfloat var = -0.1;
    static bool goingUp = true;
    if (var < 2 * M_PI && goingUp)
        var += 0.01;
    else
    {
        if (var >= 2 * M_PI)
        {
            goingUp = false;
        }
        else if (var <= 0)
        {
            goingUp = true;
            var = -0.1;
        }
        var -= 0.01;
    }

    glUniform1f(fQ_varloc, var);
}



void RenderManager::SetView()
{
    glm::mat4 v = glm::lookAt(
        camera, // Camera in world space
        origin, // looks at the origin
        up      // and the head is up
    );
    //view = v;

    //this function is used to load a uniform variable of type vec3
    glUniform3fv(camloc, 1, &camera[0]);

    // Direction of light
    glm::vec3 lightdir = glm::normalize(origin - camera);
    glUniform3fv(ldirloc, 1, &lightdir[0]);

    glm::mat4 Model = glm::mat4(1.0f);

    mvp = Projection * v * Model;

}

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

    GLFWwindow* window = glfwCreateWindow(800, 800, "Life inside Shrodinger's box", NULL, NULL);
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


GLuint RenderManager::SetUpQuad(float* tri_points, int* tri_indices, float* colors, float* tri_normals)
{


    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);//get handle
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);//what type of data points works on GL_ARRAY_BUFFER type
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), tri_points, GL_STATIC_DRAW);

    GLuint normals_vbo = 0;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), tri_normals, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), &colors[0], GL_STATIC_DRAW);

    GLuint indices_vbo = 0;
    glGenBuffers(1, &indices_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), &tri_indices[0], GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    return vao;



}

//A lot of the initialization code is borrowed from project2A
int main()
{   

    RenderManager rm;

    double angle = 0;

    int counter = 0;

    while (!glfwWindowShouldClose(rm.window))
    {   
        double angle = counter / 300.0 * 2 * M_PI;
        counter++;

        rm.camera = glm::vec3( sin(angle*0.2), rm.camera.y, cos(angle*0.2));
        rm.SetView();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        rm.SetUpQuadShader(frontQuad_vert_shader, frontQuad_frag_shader);
        glBindVertexArray(rm.fQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        rm.SetUpQuadShader(leftQuad_vert_shader, leftQuad_frag_shader);
        glBindVertexArray(rm.lQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        rm.SetUpQuadShader(backQuad_vert_shader, backQuad_frag_shader);
        glBindVertexArray(rm.bQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        rm.SetUpQuadShader(rightQuad_vert_shader, rightQuad_frag_shader);
        glBindVertexArray(rm.rQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwPollEvents();
        glfwSwapBuffers(rm.window);
    }

    glfwDestroyWindow(rm.window);
    glfwTerminate();
    return 0;
}