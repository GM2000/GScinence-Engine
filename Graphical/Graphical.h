#pragma once

//标准库
#include <thread>
#include <iostream>
#include <vector>
#include <future>

//Opengl库
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//定义宏
#define STATE_INIT	0
#define STATE_ERR	1
#define STATE_OK	2

//当前渲染状态
extern char GraphicalState;
