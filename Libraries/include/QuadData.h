//#pragma once
float fQ_tri_points[] =
{
     0.5, -0.5, 0.5, //-z quad tri1
    -0.5, 0.5 , 0.5,
    -0.5, -0.5, 0.5,

     0.5, -0.5, 0.5, //-z quad tri2
    -0.5,  0.5, 0.5,
     0.5,  0.5, 0.5
};

int fQ_tri_indices[] =
{
    0,
    1,
    2,
    0,
    1,
    5

};

float fQ_colors[] = { 1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,

                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f
};

//the vector pointing from each vertex to the origin is just (0,0,0) - vertex
//so take the negative of each element of tri_points
float fQ_tri_normals[18]
{
    -0.5,  0.5,  0.5,
     0.5, -0.5, 0.5,
     0.5,  0.5,  0.5, //-z quad normals

    -0.5,  0.5, 0.5,
     0.5, -0.5, 0.5,
    -0.5, -0.5, 0.5

};
