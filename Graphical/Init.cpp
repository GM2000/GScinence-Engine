
#include "Graphical.h"
#include "LoadTexture.h"

char GraphicalState = STATE_INIT;

//创建窗体并且加载资源
void _gsgCreateGraphicalThread(const char* WindowName)
{
	//初始化glfw
	if (!glfwInit())
	{
		std::cerr << "[ERROR]:Cannot init glfw!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}

	//创建窗口模式
	GLFWwindow* Window = glfwCreateWindow(854, 480, WindowName, NULL, NULL);

	if (!Window)
	{
		std::cerr << "[ERROR]:Cannot create window!" << std::endl;
		GraphicalState = STATE_ERR;
		glfwTerminate();
		return;
	}

	//切换设备上下文
	glfwMakeContextCurrent(Window);

	//初始化glew
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "[ERROR]:Cannot init glew!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}
	GraphicalState = STATE_OK;

	//加载LOGO和进度条
	int LogoTextureID = gsgLoadTexture(L"resources//Logo.png");
	
	//加载资源

	//循环
	while (!glfwWindowShouldClose(Window))
	{

		//交换缓存
		glfwSwapBuffers(Window);

		//处理事件
		glfwPollEvents();
	}

	//结束程序
	glfwTerminate();
}

//初始化渲染程序
bool gsgInit(const char* WindowName)
{
	//创建渲染线程开始初始化和渲染
	std::thread RenderThread(_gsgCreateGraphicalThread, WindowName);
	RenderThread.detach();

	//等待初始化结果
	while (GraphicalState == STATE_INIT);

	//返回
	if (GraphicalState == STATE_OK)
	{
		return true;
	}
	return false;
}