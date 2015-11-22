#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
// Create a GLSL program object from vertex and fragment shader files
GLuint
InitShader(const char* vShaderFile, const char* fShaderFile)
{
struct Shader {
const char* filename;
GLenum type;
GLchar* source;
} shaders[2] = {
{ vShaderFile, GL_VERTEX_SHADER, NULL },
{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
};
GLuint program = glCreateProgram();
for ( int i = 0; i < 2; ++i ) {
Shader& s = shaders[i];
std::ifstream shaderFile(s.filename);
if(!shaderFile.is_open())
{
std::cerr << "Failed to read " << s.filename << std::endl;
exit( EXIT_FAILURE );
}
std::stringstream shaderData;
shaderData << shaderFile.rdbuf();
shaderFile.close();
std::string ssrc = shaderData.str();
s.source = new char[ssrc.length()+1];
strcpy(s.source,ssrc.c_str());
GLuint shader = glCreateShader( s.type );
glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
glCompileShader( shader );
GLint compiled;
glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
if ( !compiled ) {
std::cerr << s.filename << " failed to compile:" << std::endl;
GLint logSize;
glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
char* logMsg = new char[logSize];
glGetShaderInfoLog( shader, logSize, NULL, logMsg );
std::cerr << logMsg << std::endl;
delete [] logMsg;
exit( EXIT_FAILURE );
}
delete [] s.source;
glAttachShader( program, shader );
}
/* link and error check */
glLinkProgram(program);
GLint linked;
glGetProgramiv( program, GL_LINK_STATUS, &linked );
if ( !linked ) {
std::cerr << "Shader program failed to link" << std::endl;
GLint logSize;
glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
char* logMsg = new char[logSize];
glGetProgramInfoLog( program, logSize, NULL, logMsg );
std::cerr << logMsg << std::endl;
delete [] logMsg;
exit( EXIT_FAILURE );
}
/* use program object */
glUseProgram(program);
return program;
}
