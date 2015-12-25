
#include "Graphical.h"

std::future<void> RenderThread;

GLFWwindow* Window;

void createGraphicalThread(char* WindowName)
{
	//初始化glfw
	if (!glfwInit())
	{
		throw("ERROR:Cannot init glfw!");
		return;
	}

	//创建窗口模式
	Window = glfwCreateWindow(854, 480, WindowName, NULL, NULL);

	if (!Window)
	{
		glfwTerminate();
		throw("ERROR:Cannot create window!");
		return;
	}

	//初始化glew
	if (glewInit() != GLEW_OK)
	{
		throw("ERROR:Cannot init glew!");
		return;
	}

	//切换设备上下文
	glfwMakeContextCurrent(Window);

	//循环
	while (!glfwWindowShouldClose(Window))
	{
		//开始渲染

		//交换缓存
		glfwSwapBuffers(Window);

		//处理事件
		glfwPollEvents();
	}

	glfwTerminate();
}

bool initGraphical(char* WindowName)
{
	//创建渲染线程并开始渲染
	RenderThread = std::future<void>(std::async(createGraphicalThread, WindowName));
	RenderThread.valid();

	return true;
}