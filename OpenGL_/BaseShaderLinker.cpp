#include "BaseShaderLinker.h"
#include <glad.h>
#include <glfw3.h>
#include <vector>
namespace SHB {
	BaseShaderLinker::BaseShaderLinker() :
		_shaderProgramID(std::numeric_limits<uint32_t>::max())
	{
	}
	void BaseShaderLinker::DeleteShaderProgram() {
		if (_shaderProgramID != std::numeric_limits<uint32_t>::max()) {
			glDeleteProgram(_shaderProgramID);
			_shaderProgramID = std::numeric_limits<uint32_t>::max();
		}
	}
	const bool BaseShaderLinker::LinkShader(const uint32_t v_Shader, const uint32_t f_Shader, std::string& out, const uint32_t g_Shader) {

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, v_Shader);
		if (g_Shader != std::numeric_limits<uint32_t>::max()) {
			glAttachShader(shaderProgram, g_Shader);
		}
		glAttachShader(shaderProgram, f_Shader);
		glLinkProgram(shaderProgram);
		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &_outLogSize);
			_outLog = new char[_outLogSize];
			glGetProgramInfoLog(shaderProgram, _outLogSize, &_outLogSize, _outLog);
			out += "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(_outLog);
			delete[]_outLog;
			glDeleteProgram(shaderProgram);
			glDeleteShader(v_Shader);
			if (g_Shader != std::numeric_limits<uint32_t>::max()) {
				glDeleteShader(g_Shader);
			}
			glDeleteShader(f_Shader);
			return false;
		}
		glDetachShader(shaderProgram,v_Shader);
		if (g_Shader != std::numeric_limits<uint32_t>::max()) {
			glDetachShader(shaderProgram, g_Shader);
		}
		glDetachShader(shaderProgram, f_Shader);
		_shaderProgramID = shaderProgram;
		_isLastProgramCorrectlyLinked = true;
		return true;
	}
	const uint32_t BaseShaderLinker::GetLastShaderProgramID()const
	{
		_ASSERT(_isLastProgramCorrectlyLinked);
		return _shaderProgramID;
	}
}
