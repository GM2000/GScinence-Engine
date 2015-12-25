
#include "Graphical.h"

char GraphicalState = STATE_INIT;

void createGraphicalThread(const char* WindowName)
{
	//初始化glfw
	if (!glfwInit())
	{
		std::cerr << "ERROR:Cannot init glfw!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}

	//创建窗口模式
	GLFWwindow* Window = glfwCreateWindow(854, 480, WindowName, NULL, NULL);

	if (!Window)
	{
		std::cerr << "ERROR:Cannot create window!" << std::endl;
		GraphicalState = STATE_ERR;
		glfwTerminate();
		return;
	}

	//切换设备上下文
	glfwMakeContextCurrent(Window);

	//初始化glew
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "ERROR:Cannot init glew!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}
	GraphicalState = STATE_OK;
	//循环
	while (!glfwWindowShouldClose(Window))
	{
		//开始渲染

		//交换缓存
		glfwSwapBuffers(Window);

		//处理事件
		glfwPollEvents();
	}

	//结束程序
	glfwTerminate();
}
std::future<void> RenderThread;

bool initGraphical(const char* WindowName)
{
	//创建渲染线程开始初始化和渲染
	RenderThread = std::future<void>(std::async(createGraphicalThread, WindowName));

	//等待初始化结果
	while (GraphicalState == STATE_INIT);

	return (bool)(GraphicalState - 1);
}