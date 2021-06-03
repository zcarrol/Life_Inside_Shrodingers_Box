//#pragma once
const float S = 10.0;
//Front quad data

float fQ_tri_points[] =
{
     0.5, -0.5, 0.5, //bottom right
    -0.5, 0.5 , 0.5, //top left
    -0.5, -0.5, 0.5,// bottom left

     0.5, -0.5, 0.5, 
    -0.5,  0.5, 0.5,
     0.5,  0.5, 0.5 //top right
};
/*
float fQ_tri_points[] =
{
     S, -S, S, //bottom right
    -S,  S, S, //top left
    -S, -S, S,// bottom left

     S, -S, S,
    -S,  S, S,
     S,  S, S //top right
};*/

int fQ_tri_indices[] =
{
    0,
    1,
    2, 
    0,
    1,
    5

};

float fQ_colors[] = { 1.0f, 1.0f, 1.0f,//1.0f, 0.4f, 0.9f, // bottom right - "Rose pink"
                       1.0f, 1.0f, 1.0f,//1.0f, 0.5f, 1.0f, // top left - "Orange"
                      0.0f, 1.0f, 0.0f, // bottom left - "electric green"

                       1.0f, 1.0f, 1.0f,//1.0f, 0.5f, 1.0f, //"Orange"
                      0.0f, 1.0f, 0.0f, // "Electric green"
                       1.0f, 0.5f, 0.5f// top right
};

//the vector pointing from each vertex to the origin is just (0,0,0) - vertex
//so take the negative of each element of tri_points
float fQ_tri_normals[18]
{
    -0.5,  0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5, 

    -0.5,  0.5, 0.5,
     0.5, -0.5, 0.5,
    -0.5, -0.5, 0.5

};

float fQ_tri_texData[]=
{
     // positions          texture coords
    /* 0.5, -0.5, 0.5,*/   1.0f, 0.0f, //bottom right
    /*-0.5, 0.5 , 0.5,*/   0.0f, 1.0f, //top left
    /*-0.5, -0.5, 0.5,*/   0.0f, 0.0f, //bottom left

    /* 0.5, -0.5, 0.5,*/   1.0f, 0.0f,
    /*-0.5,  0.5, 0.5,*/   0.0f, 1.0f,
    /* 0.5,  0.5, 0.5,*/   1.0f, 1.0f //top right
};



//Left quad data
float lQ_tri_points[] =
{
     //0.5, -0.5, 0.5, //-z quad tri1
    -0.5, -0.5, -0.5,
    -0.5,  0.5,  0.5,
    -0.5, -0.5,  0.5,

    -0.5, -0.5, -0.5,
    -0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5
};

float lQ_tri_texData[] =
{
     /*-0.5, -0.5, -0.5,*/   0.0f, 0.0f, //bottom left
    /*-0.5, 0.5 , 0.5,*/     1.0f, 1.0f, //top right
    /*-0.5, -0.5, 0.5,*/     1.0f, 0.0f, //bottom right

    /*-0.5, -0.5, -0.5,*/    0.0f, 0.0f,
    /*-0.5, 0.5 , 0.5,*/     1.0f, 1.0f,
    /* -0.5,  0.5, -0.5*/    0.0f, 1.0f, //top left
};

int lQ_tri_indices[] =
{
    0,
    1,
    2,
    0,
    1,
    5

};

float lQ_colors[] = { 
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f
};


float lQ_tri_normals[18]
{
    -0.5,  -0.5, -0.5,
    -0.5, 0.5,  0.5,
    -0.5,  -0.5,  0.5,

    -0.5,  -0.5, -0.5,
    -0.5, 0.5,  0.5,
    -0.5, 0.5, -0.5

};

//back quad data
float bQ_tri_points[] =
{
   
   -0.5,  0.5, -0.5,
    0.5, -0.5, -0.5,
   -0.5, -0.5, -0.5,

   -0.5,  0.5, -0.5,
    0.5, -0.5, -0.5,
    0.5,  0.5, -0.5
};

int bQ_tri_indices[] =
{
    0,
    1,
    2,
    0,
    1,
    5

};

float bQ_colors[] = { 1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f
};


float bQ_tri_normals[18]
{
     0.5, -0.5, -0.5,
    -0.5, 0.5, -0.5,
     0.5, 0.5,   -0.5,

     0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5

};


//right quad data
float rQ_tri_points[] =
{

    0.5,  -0.5, 0.5,
    0.5, 0.5, -0.5,
     0.5, 0.5, 0.5,

    0.5,  -0.5, 0.5,
    0.5, 0.5, -0.5,
    0.5,  -0.5, -0.5
};

int rQ_tri_indices[] =
{
    0,
    1,
    2,
    0,
    1,
    5

};

float rQ_colors[] = { 1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f
};


float rQ_tri_normals[18]
{
    0.5,  -0.5,  0.5,
    0.5, 0.5,  -0.5,
     0.5, 0.5, 0.5,

    0.5,  -0.5,  0.5,
    0.5, 0.5, -0.5,
    0.5,  -0.5, -0.5

};