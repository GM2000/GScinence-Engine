#pragma once

#include "Graphical.h"

typedef struct
{
	GLenum       Type;
	const char*  FileName;
	GLuint       Shader;
} shaderInfo;

int _loadShader(shaderInfo* Shaders);