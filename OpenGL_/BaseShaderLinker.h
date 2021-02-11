#pragma once
#include<string>
#include"LogComponent.h"
namespace SHB {
	class BaseShaderLinker :public Components::LogComponent {
	private:
		uint32_t _shaderProgramID;
		bool _isLastProgramCorrectlyLinked;
	public:
		BaseShaderLinker();
		void DeleteShaderProgram();
		const bool LinkShader(const uint32_t v_Shader, const uint32_t f_Shader, std::string& out, const uint32_t g_Shader = std::numeric_limits<uint32_t>::max());
		const uint32_t GetLastShaderProgramID()const;
	};
}

