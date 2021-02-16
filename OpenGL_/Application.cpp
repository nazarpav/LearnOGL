#include "Application.h"
#include<iostream>
#include<thread>
#include"Utils.h"
namespace app {
	void Application::Start()
	{
		const size_t SCREEN_HEIGHT = 600;
		const size_t SCREEN_WIDTH = 800;
		const double FPS = 60;
		const double FRAME_TIME = 1000. / FPS;
		std::chrono::duration<double, std::milli> elapsed;
		std::chrono::steady_clock::time_point end;
		std::chrono::steady_clock::time_point start;
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
		float vertices[] = {
		 1.f, 1.f, 0.0f,//0
		 1.f, -1.f, 0.0f,//1
		-1.f, -1.f, 0.0f,//2
		-1., 1.f, 0.0f,//3

		-.1f,1.f,0.f,//4
		-.1f,-1.f,0.f,//5

		.1f,1.f,0.f,//6
		.1f,-1.f,0.f//7
		};
		/*uint32_t indices[] = {
			0, 6, 7,
			7, 1, 0,
			3, 2, 5,
			5, 3, 4
		};*/
		uint32_t indices[] = {
			0,1,2,
			2,0,3
		};
		int indexesCount = sizeof(indices) / sizeof(uint32_t);
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glPolygonMode(GL_FRONT_AND_BACK, /*GL_LINE*/GL_FILL);
		uint8_t counter = 0;
		while (!glfwWindowShouldClose(win))
		{
			start = std::chrono::steady_clock::now();
			++counter;
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
			glDrawElements(GL_TRIANGLES, indexesCount, GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(win);
			glfwPollEvents();
			end = std::chrono::steady_clock::now();
			elapsed = end - start;
			if (elapsed.count() < FRAME_TIME) {
				std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(elapsed.count() < FRAME_TIME));
				if (counter % 120 == 0) {
					utils::Utils::SetConsoleCursorePosition(0, 0);
					std::cout << "fps: " << 1000. / (elapsed.count() + FRAME_TIME) << "\n";
				}
			}
			else if (counter % 120 == 0) {
				utils::Utils::SetConsoleCursorePosition(0, 0);
				std::cout << "fps: " << 1000. / elapsed.count() << "\n";
			}
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
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
			handler->Reload();
		}
	}
}
