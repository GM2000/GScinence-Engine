#pragma once

#include "Graphical.h"

typedef struct
{
	GLenum       Type;
	const char*  FileName;
	GLuint       Shader;
} shaderInfo;

GLuint _loadShader(shaderInfo* Shaders);