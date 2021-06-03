#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
//GLuint GenerateTexture(const char*, int, GLuint);
const char* lightning = "Libraries/include/lightning.png";
const char* galaxy = "Libraries/include/galaxyResize.png";
const char* waterRipple = "Libraries/include/waterRipple.png";
const char* kib = "Libraries/include/trueKibsR.jpg";
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);



class RenderManager
{
public:
    RenderManager();
    void   SetView();
    void   SetUpQuadShader(const char*, const char*, GLuint, GLuint, GLuint&);
    GLuint SetUpQuad(float*, int*, float*, float*, float*);
    void GenerateTexture(const char*, int, GLuint);
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
    GLuint textures[4];
    glm::mat4 Projection;
    const char* fb_image;
    const char* lr_image;
    //GLuint texture1;

    //front quad data
    GLuint fQ_vao;
    GLuint fQ_lcoeloc;
    GLuint fQ_varloc;
    GLuint fQ_texture;
    GLuint fQ_shader;
    

    //left quad data
    GLuint lQ_vao;
    GLuint lQ_lcoeloc;
    GLuint lQ_varloc;
    GLuint lQ_texture;
    GLuint lQ_shader;

    //back quad data
    GLuint bQ_vao;
    GLuint bQ_lcoeloc;
    GLuint bQ_varloc;
    GLuint bQ_texture;
    GLuint bQ_shader;

    //right quad data
    GLuint rQ_vao;
    GLuint rQ_lcoeloc;
    GLuint rQ_varloc;
    GLuint rQ_texture;
    GLuint rQ_shader;


};

RenderManager::RenderManager()
{

    window = SetUpWindow();

    origin = glm::vec3(0, 0, 0);
    up =     glm::vec3(0, 1, 0);
    camera = glm::vec3(0, 2, 0);

    rQ_texture = 0;
    lQ_texture = 0;
    bQ_texture = 0;
    fQ_texture = 0;

    Projection = glm::perspective(
        glm::radians(45.0f), (float)800 / (float)800, 1.0f, 200.0f);


    lr_image = lightning;
    fb_image = galaxy;

    glGenTextures(1, &textures[0]);

    glGenTextures(1, &textures[1]);

    glGenTextures(1, &textures[2]);

    glGenTextures(1, &textures[3]);


    fQ_vao = SetUpQuad(fQ_tri_points, fQ_tri_indices, fQ_colors, fQ_tri_normals, fQ_tri_texData);
    SetUpQuadShader(frontQuad_vert_shader, frontQuad_frag_shader, fQ_vao, fQ_lcoeloc, fQ_varloc);
    GenerateTexture(fb_image, 0, fQ_shader);
    
    bQ_vao = SetUpQuad(bQ_tri_points, bQ_tri_indices, bQ_colors, bQ_tri_normals, fQ_tri_texData);
    SetUpQuadShader(backQuad_vert_shader, backQuad_frag_shader, bQ_vao, bQ_lcoeloc, bQ_varloc);
    GenerateTexture(fb_image, 1, bQ_shader);

    lQ_vao = SetUpQuad(lQ_tri_points, lQ_tri_indices, lQ_colors, lQ_tri_normals, lQ_tri_texData);
    SetUpQuadShader(leftQuad_vert_shader, leftQuad_frag_shader, lQ_vao, lQ_lcoeloc, lQ_varloc);
    GenerateTexture(lr_image, 2, lQ_shader);

    rQ_vao = SetUpQuad(rQ_tri_points, rQ_tri_indices, rQ_colors, rQ_tri_normals, lQ_tri_texData);
    SetUpQuadShader(rightQuad_vert_shader, rightQuad_frag_shader, rQ_vao, rQ_lcoeloc, rQ_varloc);
    GenerateTexture(lr_image, 3, rQ_shader);
    

    glm::mat4 View = glm::lookAt(
        camera, // camera in world space
        origin, // looks at the origin
        up      // and the head is up
    );
    glm::mat4 Model = glm::mat4(1.0f);
    mvp = Projection * View * Model;



}

void RenderManager::SetUpQuadShader(const char* v, const char* f, GLuint vao, GLuint lcoeloc, GLuint& varloc)
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

    glm::vec4 lightcoeff(0.5, 0.4, 0.8, 70);
    lcoeloc = glGetUniformLocation(shader_programme, "lightcoeff");
    glUniform4fv(lcoeloc, 1, &lightcoeff[0]);

    varloc = glGetUniformLocation(shader_programme, "var");

    /*
    GLuint texcoord = glGetAttribLocation(shader_programme, "texCoord");
    glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(texcoord);*/
    

    //each quad has its own variable whose value needs to be independant of the other quads

    GLuint texloc = glGetUniformLocation(shader_programme, "ourTexture");

    if (vao == fQ_vao)
    {
        fQ_varloc = varloc;
        ModifyFqVar();
        fQ_shader = shader_programme;
        glUniform1i(texloc, 0);
    }
    
    else if (vao == bQ_vao)
    {
        bQ_varloc = varloc;
        ModifyBqVar();
        bQ_shader = shader_programme;
        glUniform1i(texloc, 0);
    }
   
    else if (vao == lQ_vao)
    {
        lQ_varloc = varloc;
        ModifyLqVar();
        lQ_shader = shader_programme;
        glUniform1i(texloc, 0);
    }
    
    else if (vao == rQ_vao)
    {   
        rQ_varloc = varloc;
        ModifyRqVar();
        rQ_shader = shader_programme;
        glUniform1i(texloc, 0);
    }

    


}

void RenderManager::GenerateTexture(const char* file, int val, GLuint shader_programme)
{
    // load and generate the texture
    //GLuint texture = 0;
    //how many textures and where we want to store them
    //glActiveTexture(GL_TEXTURE0);
    //glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, textures[val]);

    int width, height, nrChannels;
    //load image data
   
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if (data)
    {   
        cerr << width << "x" << height << endl;
        //after this call the currently bound texture object now has the texture image attached to it
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);
    

    //texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLuint texloc = glGetUniformLocation(shader_programme, "ourTexture");

    glUniform1i(texloc, 0);
    
}

void RenderManager::ModifyRqVar()
{
    static float var = 4;
    static bool goingDown = false;


    if (!goingDown)
    {
        var += 0.01;
        if (var >= 15 * M_PI)
            goingDown = true;

    }
    else
    {
        var -= 0.01;
        if (var <= 5)
            goingDown = false;
    }

    glUniform1f(rQ_varloc, var);
}

void RenderManager::ModifyBqVar()
{
    static float var = 4;
    static bool goingDown = false;

    if (!goingDown)
    {
        var += 0.01;
        if (var >= 10 * M_PI)
            goingDown = true;

    }
    else 
    {
        var -= 0.01;
        if (var <= 5)
            goingDown = false;
    }

    glUniform1f(bQ_varloc, var);
}

void RenderManager::ModifyLqVar()
{
    static float var = 4;
    static bool goingDown = false;

    if (!goingDown)
    {

        var += 0.01;
        if (var >= 15 * M_PI)
            goingDown = true;

    }
    else
    {
        var -= 0.01;
        if (var <= 5)
            goingDown = false;
    }

    glUniform1f(lQ_varloc, var);

}

void RenderManager::ModifyFqVar()
{
    /*
    static int counter = 0;
    static double angle = 0;
    angle = counter / 300.0 * 2 * M_PI;
    counter++;
    glUniform1f(fQ_varloc, angle);
    */

    static float var = 4;
    static bool goingDown = false;
    
    if (!goingDown)
    {   
        var += 0.01;
        if (var >= 10 * M_PI)
            goingDown = true;

    }
    else
    {
        var -= 0.01;
        if (var <= 4)
            goingDown = false;
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


GLuint RenderManager::SetUpQuad(float* tri_points, int* tri_indices, float* colors, float* tri_normals, float* texCoords)
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
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), colors, GL_STATIC_DRAW);

    GLuint texcoord_vbo = 0;
    glGenBuffers(1, &texcoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), texCoords, GL_STATIC_DRAW);

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

    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, texcoord_vbo);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

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

        rm.camera = glm::vec3(sin(angle*0.1), cos(angle*0.1), cos(angle*0.1));
        rm.SetView();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
      //  glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rm.textures[0]);
        rm.SetUpQuadShader(frontQuad_vert_shader, frontQuad_frag_shader, rm.fQ_vao, rm.fQ_lcoeloc, rm.fQ_varloc);
        glBindVertexArray(rm.fQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
       // glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rm.textures[1]);
        rm.SetUpQuadShader(backQuad_vert_shader, backQuad_frag_shader, rm.bQ_vao, rm.bQ_lcoeloc, rm.bQ_varloc);
        glBindVertexArray(rm.bQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rm.textures[2]);
        rm.SetUpQuadShader(leftQuad_vert_shader, leftQuad_frag_shader, rm.lQ_vao, rm.lQ_lcoeloc, rm.lQ_varloc);
        glBindVertexArray(rm.lQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rm.textures[3]);
        rm.SetUpQuadShader(rightQuad_vert_shader, rightQuad_frag_shader, rm.rQ_vao, rm.rQ_lcoeloc, rm.rQ_varloc);
        glBindVertexArray(rm.rQ_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        glfwPollEvents();
        glfwSwapBuffers(rm.window);
    }

    glfwDestroyWindow(rm.window);
    glfwTerminate();
    return 0;
}