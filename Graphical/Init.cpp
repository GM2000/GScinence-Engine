
#include "Graphical.h"

std::future<void> RenderThread;

GLFWwindow* Window;

void createGraphicalThread(char* WindowName)
{
	//��ʼ��glfw
	if (!glfwInit())
	{
		throw("ERROR:Cannot init glfw!");
		return;
	}

	//��������ģʽ
	Window = glfwCreateWindow(854, 480, WindowName, NULL, NULL);

	if (!Window)
	{
		glfwTerminate();
		throw("ERROR:Cannot create window!");
		return;
	}

	//��ʼ��glew
	if (glewInit() != GLEW_OK)
	{
		throw("ERROR:Cannot init glew!");
		return;
	}

	//�л��豸������
	glfwMakeContextCurrent(Window);

	//ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		//��ʼ��Ⱦ

		//��������
		glfwSwapBuffers(Window);

		//�����¼�
		glfwPollEvents();
	}

	glfwTerminate();
}

bool initGraphical(char* WindowName)
{
	//������Ⱦ�̲߳���ʼ��Ⱦ
	RenderThread = std::future<void>(std::async(createGraphicalThread, WindowName));
	RenderThread.valid();

	return true;
}