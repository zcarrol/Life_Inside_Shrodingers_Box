//#pragma once


const char* frontQuad_vert_shader =
"#version 400\n"
"layout (location = 0) in vec3 vertex_position;\n"
"layout (location = 1) in vec3 vertex_normal;\n"
"layout (location = 2) in vec3 vertex_color;\n"
"layout (location = 3) in vec2 texCoord;\n"
"uniform float var;\n"
"uniform mat4 MVP;\n"
"uniform vec3 cameraloc;\n"
"uniform vec3 lightdir;\n"
"uniform vec4 lightcoeff;\n"
"out float var_to_fs;\n"
"out float shading_amount;\n"
"out vec3 color;\n"
"out vec2 tex_Coord;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"   gl_Position = MVP*position;\n"
"   color = vertex_color;\n"

//perform the transforms
"   shading_amount = lightcoeff.x;\n"
"   vec3 norm_v = normalize(vertex_normal);\n"
"   shading_amount += lightcoeff.y * max(0.0, dot(lightdir, norm_v));\n"
"   vec3 R = normalize(2.0*dot(lightdir, norm_v) * norm_v - lightdir);\n"
"   vec3 viewDir = normalize(vertex_position - cameraloc);\n"
"   shading_amount += lightcoeff.z * pow( max(0.0, dot(viewDir, R)), lightcoeff.w);\n"
"   var_to_fs = var;\n"
"	tex_Coord = texCoord;\n"
"}\n";



const char* frontQuad_frag_shader =
"#version 400\n"
"uniform sampler2D ourTexture;\n"
"in float shading_amount;\n"
"in float var_to_fs;\n"
"in vec3 color;\n"
"in vec2 tex_Coord;\n"
"out vec4 frag_color;\n"
"void main(){\n"
"  frag_color = texture(ourTexture, tex_Coord);\n"

"  frag_color.x = min(1.0, shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, shading_amount*frag_color.z);\n" 
"  frag_color.w = min(1.0, shading_amount*frag_color.w);\n"
"}\n";

const char* leftQuad_vert_shader =
"#version 400\n"
"layout (location = 0) in vec3 vertex_position;\n"
"layout (location = 1) in vec3 vertex_normal;\n"
"layout (location = 2) in vec3 vertex_color;\n"
"layout (location = 3) in vec2 texCoord;\n"
"uniform float var;\n"
"uniform mat4 MVP;\n"
"uniform vec3 cameraloc;\n"
"uniform vec3 lightdir;\n"
"uniform vec4 lightcoeff;\n"
"out float var_to_fs;\n"
"out vec2 tex_Coord;"
"out float shading_amount;\n"
"out vec3 color;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"   gl_Position = MVP*position;\n"
"   color = vertex_color;\n"

//perform the transforms
"   shading_amount = lightcoeff.x;\n"
"   vec3 norm_v = normalize(vertex_normal);\n"
"   shading_amount += lightcoeff.y * max(0.0, dot(lightdir, norm_v));\n"
"   vec3 R = normalize(2.0*dot(lightdir, norm_v) * norm_v - lightdir);\n"
"   vec3 viewDir = normalize(vertex_position - cameraloc);\n"
"   shading_amount += lightcoeff.z * pow( max(0.0, dot(viewDir, R)), lightcoeff.w);\n"
"   var_to_fs = var;\n"
"	tex_Coord = texCoord;\n"
"}\n";



const char* leftQuad_frag_shader =
"#version 400\n"
"uniform sampler2D ourTexture;\n"
"in float shading_amount;\n"
"in float var_to_fs;\n"
"in vec3 color;\n"
"in vec2 tex_Coord;\n"
"out vec4 frag_color;\n"
"void main(){\n"
"  frag_color = texture(ourTexture, tex_Coord)*shading_amount;\n"

"  frag_color.x = min(1.0, shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, shading_amount*frag_color.z);\n"
"  frag_color.w = min(1.0, shading_amount*frag_color.w);\n"
"}\n";


const char* backQuad_vert_shader =
"#version 400\n"
"layout (location = 0) in vec3 vertex_position;\n"
"layout (location = 1) in vec3 vertex_normal;\n"
"layout (location = 2) in vec3 vertex_color;\n"
"layout (location = 3) in vec2 texCoord;\n"
"uniform float var;\n"
"uniform mat4 MVP;\n"
"uniform vec3 cameraloc;\n"
"uniform vec3 lightdir;\n"
"uniform vec4 lightcoeff;\n"
"out float var_to_fs;\n"
"out vec2 tex_Coord;\n"
"out float shading_amount;\n"
"out vec3 color;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"   gl_Position = MVP*position;\n"
"   color = vertex_color;\n"

//perform the transforms
"   shading_amount = lightcoeff.x;\n"
"   vec3 norm_v = normalize(vertex_normal);\n"
"   shading_amount += lightcoeff.y * max(0.0, dot(lightdir, norm_v));\n"
"   vec3 R = normalize(2.0*dot(lightdir, norm_v) * norm_v - lightdir);\n"
"   vec3 viewDir = normalize(vertex_position - cameraloc);\n"
"   shading_amount += lightcoeff.z * pow( max(0.0, dot(viewDir, R)), lightcoeff.w);\n"
"   var_to_fs = var;\n"
"	tex_Coord = texCoord;\n"
"}\n";



const char* backQuad_frag_shader =
"#version 400\n"
"uniform sampler2D ourTexture;\n"
"in float shading_amount;\n"
"in float var_to_fs;\n"
"in vec3 color;\n"
"in vec2 tex_Coord;\n"
"out vec4 frag_color;\n"
"void main(){\n"
"  frag_color = texture(ourTexture, tex_Coord)*shading_amount;\n"

"  frag_color.x = min(1.0, shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, shading_amount*frag_color.z);\n"
"  frag_color.w = min(1.0, shading_amount*frag_color.w);\n"
"}\n";

const char* rightQuad_vert_shader =
"#version 400\n"
"layout (location = 0) in vec3 vertex_position;\n"
"layout (location = 1) in vec3 vertex_normal;\n"
"layout (location = 2) in vec3 vertex_color;\n"
"layout (location = 3) in vec2 texCoord;\n"
"uniform float var;\n"
"uniform mat4 MVP;\n"
"uniform vec3 cameraloc;\n"
"uniform vec3 lightdir;\n"
"uniform vec4 lightcoeff;\n"
"out vec2 tex_Coord;\n"
"out float var_to_fs;\n"
"out float shading_amount;\n"
"out vec3 color;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"   gl_Position = MVP*position;\n"
"   color = vertex_color;\n"

//perform the transforms
"   shading_amount = lightcoeff.x;\n"
"   vec3 norm_v = normalize(vertex_normal);\n"
"   shading_amount += lightcoeff.y * max(0.0, dot(lightdir, norm_v));\n"
"   vec3 R = normalize(2.0*dot(lightdir, norm_v) * norm_v - lightdir);\n"
"   vec3 viewDir = normalize(vertex_position - cameraloc);\n"
"   shading_amount += lightcoeff.z * pow( max(0.0, dot(viewDir, R)), lightcoeff.w);\n"
"   var_to_fs = var;\n"
"	tex_Coord = texCoord;\n"
"}\n";



const char* rightQuad_frag_shader =
"#version 400\n"
"uniform sampler2D ourTexture;\n"
"in float shading_amount;\n"
"in float var_to_fs;\n"
"in vec3 color;\n"
"in vec2 tex_Coord;\n"
"out vec4 frag_color;\n"
"void main(){\n"
"  frag_color = texture(ourTexture, tex_Coord)*shading_amount;\n"

"  frag_color.x = min(1.0, shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, shading_amount*frag_color.z);\n"
"  frag_color.w = min(1.0, shading_amount*frag_color.w);\n"
"}\n";