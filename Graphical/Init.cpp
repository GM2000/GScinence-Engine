
#include "Graphical.h"

char GraphicalState = STATE_INIT;

void createGraphicalThread(const char* WindowName)
{
	//��ʼ��glfw
	if (!glfwInit())
	{
		std::cerr << "ERROR:Cannot init glfw!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}

	//��������ģʽ
	GLFWwindow* Window = glfwCreateWindow(854, 480, WindowName, NULL, NULL);

	if (!Window)
	{
		std::cerr << "ERROR:Cannot create window!" << std::endl;
		GraphicalState = STATE_ERR;
		glfwTerminate();
		return;
	}

	//�л��豸������
	glfwMakeContextCurrent(Window);

	//��ʼ��glew
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "ERROR:Cannot init glew!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}
	GraphicalState = STATE_OK;
	//ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		//��ʼ��Ⱦ

		//��������
		glfwSwapBuffers(Window);

		//�����¼�
		glfwPollEvents();
	}

	//��������
	glfwTerminate();
}
std::future<void> RenderThread;

bool initGraphical(const char* WindowName)
{
	//������Ⱦ�߳̿�ʼ��ʼ������Ⱦ
	RenderThread = std::future<void>(std::async(createGraphicalThread, WindowName));

	//�ȴ���ʼ�����
	while (GraphicalState == STATE_INIT);

	return (bool)(GraphicalState - 1);
}