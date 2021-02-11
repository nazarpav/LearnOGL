#include "Application.h"
#include<iostream>
#include<chrono>
namespace app {
	void Application::Start()
	{
		const size_t SCREEN_HEIGHT = 600;
		const size_t SCREEN_WIDTH = 800;
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
		if (!win) {
			std::cout << "Failed create window\n";
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(win);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to GLAD init\n";
			glfwTerminate();
			return;
		}
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
		handler = new SHB::BaseShaderHandler("shader.vert", "shader.frag");
		/*if (!S_Compiler.IsShaderLoaded()) {
			glfwTerminate();
			return;
		}*/
		float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};
		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		while (!glfwWindowShouldClose(win))
		{
			ProcessInput(win);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			if (handler->IsCrashed() == false) {
				glUseProgram(handler->GetShaderProgramId());
				/*double xpos, ypos;
				glfwGetCursorPos(win, &xpos, &ypos);
				GLint time = glGetUniformLocation(handler->GetShaderProgramId(), "time");
				GLint mousePos = glGetUniformLocation(handler->GetShaderProgramId(), "mousePos");
				glUniform1d(time, glfwGetTime());*/
				//glUniform2d(mousePos, xpos, ypos);
			}
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(win);
			glfwPollEvents();
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		delete handler;
		glfwTerminate();
	}
	void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Application::ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS) {
		}
		handler->Reload();
	}
}
