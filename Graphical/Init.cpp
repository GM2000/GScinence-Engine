
#include "Graphical.h"
#include "LoadTexture.h"
#include "Model.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	int LogoTextureID = gsgLoadTexture(L"resources//test.png");
	
	glBindTexture(GL_TEXTURE_2D, LogoTextureID);
	//������Դ
	model t;
	t.loadModel("resources//T.GMesh");

	//����
	GLuint Vao = 0;
	GLuint Buffer = 0;

	std::vector<GLfloat> tt;
	tt.push_back(0.5);
	tt.push_back(1.0);
	tt.push_back(0.0);
	tt.push_back(-1.0);
	tt.push_back(-1.0);
	tt.push_back(0.0);
	tt.push_back(1.0);
	tt.push_back(-1.0);
	tt.push_back(0.0);

	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER,Buffer);

	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * t.size(), t.getVerticesData(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * t.size(), t.getTextureData(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	shaderInfo s1[] = {
		{ GL_VERTEX_SHADER, "GLSL\\Normail3D.vert" },
		{ GL_FRAGMENT_SHADER, "GLSL\\Normail3D.frag" },
		{ GL_NONE, NULL } };

	GLuint shader = _loadShader(s1);

	glUseProgram(shader);

	GLint f = glGetUniformLocation(shader, "Frustum");
	GLint ttt = glGetUniformLocation(shader, "Translate");

	glm::mat4 GobalProjection = glm::perspective(45.0f, (GLfloat)854 / (GLfloat)480, 0.1f, 500.0f);
	glm::mat4 Ts = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 3.0));

	glUniformMatrix4fv(f, 1, GL_TRUE, glm::value_ptr(GobalProjection));
	glUniformMatrix4fv(ttt, 1, GL_TRUE, glm::value_ptr(Ts));

	glViewport(0, 0, 854, 480);

	//ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, t.size() / 3);

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