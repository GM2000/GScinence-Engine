
#include "Graphical.h"
#include "LoadTexture.h"

char GraphicalState = STATE_INIT;

//�������岢�Ҽ�����Դ
void _gsgCreateGraphicalThread(const char* WindowName)
{
	//��ʼ��glfw
	if (!glfwInit())
	{
		std::cerr << "[ERROR]:Cannot init glfw!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}

	//��������ģʽ
	GLFWwindow* Window = glfwCreateWindow(854, 480, WindowName, NULL, NULL);

	if (!Window)
	{
		std::cerr << "[ERROR]:Cannot create window!" << std::endl;
		GraphicalState = STATE_ERR;
		glfwTerminate();
		return;
	}

	//�л��豸������
	glfwMakeContextCurrent(Window);

	//��ʼ��glew
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "[ERROR]:Cannot init glew!" << std::endl;
		GraphicalState = STATE_ERR;
		return;
	}
	GraphicalState = STATE_OK;

	//����LOGO�ͽ�����
	int LogoTextureID = gsgLoadTexture(L"resources//Logo.png");
	
	//������Դ

	//ѭ��
	while (!glfwWindowShouldClose(Window))
	{

		//��������
		glfwSwapBuffers(Window);

		//�����¼�
		glfwPollEvents();
	}

	//��������
	glfwTerminate();
}

//��ʼ����Ⱦ����
bool gsgInit(const char* WindowName)
{
	//������Ⱦ�߳̿�ʼ��ʼ������Ⱦ
	std::thread RenderThread(_gsgCreateGraphicalThread, WindowName);
	RenderThread.detach();

	//�ȴ���ʼ�����
	while (GraphicalState == STATE_INIT);

	//����
	if (GraphicalState == STATE_OK)
	{
		return true;
	}
	return false;
}