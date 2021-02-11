#pragma once
#include "glad.h"
#include "glfw3.h"
#include"BaseShaderHandler.h"
namespace app {
	class Application
	{
	public:
		void Start();
	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void ProcessInput(GLFWwindow* window);
	};
}

