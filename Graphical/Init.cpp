
#include "Graphical.h"
#include "LoadTexture.h"
#include "Model.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	//int LogoTextureID = gsgLoadTexture(L"resources//test.png");
	
	//glBindTexture(GL_TEXTURE_2D, LogoTextureID);
	//加载资源
	model t;
	t.loadModel("resources//T.GMesh");

	//测试
	GLuint Vao = 0;
	GLuint Buffer = 0;

	//glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &Vao);
	glBindVertexArray(Vao);

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER,Buffer);

	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * t.size(), t.getVerticesData(), GL_DYNAMIC_DRAW);

	GLfloat* mmmm=(GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * t.size(), t.getTextureData(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	shaderInfo s1[] = {
		{ GL_VERTEX_SHADER, "GLSL\\Normail3D.vert" },
		{ GL_FRAGMENT_SHADER, "GLSL\\Normail3D.frag" },
		{ GL_NONE, NULL } };

	GLuint shader = _loadShader(s1);

	glUseProgram(shader);

	GLint f = glGetUniformLocation(shader, "Frustum");
	GLint ttt = glGetUniformLocation(shader, "Translate");
	GLint rrr = glGetUniformLocation(shader, "rot");

	glm::mat4 GobalProjection = glm::perspective(45.0f, (GLfloat)854 / (GLfloat)480, 0.1f, 5000.0f);
	glm::mat4 Ts = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, -3.0));
	glm::mat4 rt = glm::rotate_slow(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(f, 1, GL_TRUE, glm::value_ptr(GobalProjection));
	glUniformMatrix4fv(ttt, 1, GL_TRUE, glm::value_ptr(Ts));
	glUniformMatrix4fv(rrr, 1, GL_TRUE, glm::value_ptr(rt));

	glViewport(0, 0, 854, 480);

	//循环
	while (!glfwWindowShouldClose(Window))
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 12, 14);

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