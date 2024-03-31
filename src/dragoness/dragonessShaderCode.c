#include "dragonessShaderCode.h"
const char* fragmentShaderCode =
"#version 330 core\n"
"// Ouput data\n"
"out vec3 color;\n"

"//out vec3 color;\n"
"in vec3 fragmentColor;\n"

"void main() {\n"
"	color = fragmentColor;\n"
"}";
const char* vertexShaderCode =
"#version 330 core\n"

"// Input vertex data, different for all executions of this shader.\n"
"layout(location = 0) in vec3 vertices;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 fragmentColor;\n"

"uniform mat4 mvp;"
"void main() {\n"
"	gl_Position = mvp * vec4(vertices,1.0);\n"
"	fragmentColor = color;\n"
"}\n";
