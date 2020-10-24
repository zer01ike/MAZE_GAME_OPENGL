#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
class Shader
{
public:
	Shader();
	~Shader();
	static char* file_read(const char* filename);
	static void print_log(GLuint object);
	static GLuint create_shader(const char* filename, GLenum type);
	static GLuint create_program(const char* vertexfile, const char *fragmentfile, const char *geometryfile = nullptr);
};

