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
"	if(vertex_color.x == 0 && vertex_color.y == 0 && vertex_color.z ==0)"
"		position.x += var;\n"
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
"  vec2 txMod = vec2(sqrt(0.25-pow(tex_Coord.y-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*.2, sqrt(0.5-pow(tex_Coord.x-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*0.2);"
"  frag_color = texture(ourTexture, txMod);\n"
"  frag_color.x = min(1.0, var_to_fs*0.2*shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, var_to_fs*0.8*shading_amount*frag_color.z);\n" 
"  frag_color.w = min(1.0, 0.8*shading_amount*frag_color.w);\n"
"  if(frag_color.x >= 1 && frag_color.y >= 1 && frag_color.z >= 1)\n"
"	frag_color = vec4(0.17f, 0.5f*var_to_fs*0.3, 0.3f, 1.0f);\n"
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
"out float shading_amount;\n"
"out vec3 color;\n"
"out vec2 tex_Coord;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"	if(vertex_color.x == 0 && vertex_color.y == 0 && vertex_color.z ==0)"
"		position.x += var;\n"
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
"  vec2 txMod = vec2(sqrt(0.25-pow(tex_Coord.y-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*.2, sqrt(0.5-pow(tex_Coord.x-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*0.2);"//vec2(sin(tex_Coord.y*var_to_fs), cos(tex_Coord.x*var_to_fs));\n"
"  frag_color = texture(ourTexture, txMod);\n"
"  frag_color.x = min(1.0, shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, var_to_fs*0.3*shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, var_to_fs*shading_amount*frag_color.z);\n"
"  frag_color.w = min(1.0, 0.8*shading_amount*frag_color.w);\n"
//"  if(frag_color.x >= 0.9 && frag_color.y >= 0.9 && frag_color.z >= 0.9)\n"
//"	frag_color = vec4(0.1f, 0.6f, 0.9f, 1.0f);\n"
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
"out float shading_amount;\n"
"out vec3 color;\n"
"out vec2 tex_Coord;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"	if(vertex_color.x == 0 && vertex_color.y == 0 && vertex_color.z ==0)"
"		position.x += var;\n"
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
"  vec2 txMod = vec2(sqrt(0.25-pow(tex_Coord.y-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*.2, sqrt(0.5-pow(tex_Coord.x-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*0.2);"//vec2(sin(tex_Coord.y*var_to_fs), cos(tex_Coord.x*var_to_fs));\n"
"  frag_color = texture(ourTexture, txMod);\n"
"  frag_color.x = min(1.0, var_to_fs*0.12*shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, var_to_fs*0.2*shading_amount*frag_color.z);\n"
"  frag_color.w = min(1.0, 0.8*shading_amount*frag_color.w);\n"
//"  if(frag_color.x <= 0.5 && frag_color.y <= 0.5 && frag_color.z <= 0.5)\n"
//"	  frag_color = vec4(0.0, min(1.0,0.3f*var_to_fs), 0.3f, 1.0f);\n"
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
"out float var_to_fs;\n"
"out float shading_amount;\n"
"out vec3 color;\n"
"out vec2 tex_Coord;\n"
"void main(){\n"
"   vec4 position = vec4(vertex_position, 1.0);\n"
"	if(vertex_color.x == 0 && vertex_color.y == 0 && vertex_color.z ==0)"
"		position.x += var;\n"
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
"  vec2 txMod = vec2(sqrt(0.25-pow(tex_Coord.y-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*.2, sqrt(0.5-pow(tex_Coord.x-0.5,max(2,noise1(2*var_to_fs))))*var_to_fs*0.2);"//vec2(sin(tex_Coord.y*var_to_fs), cos(tex_Coord.x*var_to_fs));\n"
"  frag_color = texture(ourTexture, txMod);\n"
"  frag_color.x = min(1.0, var_to_fs*0.2*shading_amount*frag_color.x);\n"
"  frag_color.y = min(1.0, shading_amount*frag_color.y); \n"
"  frag_color.z = min(1.0, var_to_fs*0.2*shading_amount*frag_color.z);\n"
"  frag_color.w = min(1.0, var_to_fs*0.05);\n"
//"  frag_color.w = min(1.0, 0.8*shading_amount*frag_color.w);\n"
//"  if(frag_color.x <= 0.2 && frag_color.y <= 0.2 && frag_color.z <= 0.2)\n"
//"	frag_color = vec4(0.0f, var_to_fs+0.8f, var_to_fs*0.5f, 1.0f);\n"
"}\n";
