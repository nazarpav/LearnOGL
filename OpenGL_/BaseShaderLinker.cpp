#include "BaseShaderLinker.h"
#include <glad.h>
#include <glfw3.h>
#include <vector>
namespace SHB {
	BaseShaderLinker::BaseShaderLinker() :
		_shaderProgramID(std::numeric_limits<uint32_t>::max())
	{
	}
	BaseShaderLinker::~BaseShaderLinker()
	{
		DeleteShaderProgram();
	}
	void BaseShaderLinker::DeleteShaderProgram() {
		if (_shaderProgramID != std::numeric_limits<uint32_t>::max()) {
			glDeleteProgram(_shaderProgramID);
			_shaderProgramID = std::numeric_limits<uint32_t>::max();
		}
	}
	const bool BaseShaderLinker::LinkShader(const uint32_t v_Shader, const uint32_t f_Shader, std::string& out, const uint32_t g_Shader) {
		if (_shaderProgramID == std::numeric_limits<uint32_t>::max()) {
			_shaderProgramID = glCreateProgram();
		}
		glAttachShader(_shaderProgramID, v_Shader);
		if (g_Shader != std::numeric_limits<uint32_t>::max()) {
			glAttachShader(_shaderProgramID, g_Shader);
		}
		glAttachShader(_shaderProgramID, f_Shader);
		glLinkProgram(_shaderProgramID);
		int success;
		glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramiv(_shaderProgramID, GL_INFO_LOG_LENGTH, &_outLogSize);
			_outLog = new char[_outLogSize];
			glGetProgramInfoLog(_shaderProgramID, _outLogSize, &_outLogSize, _outLog);
			out += "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(_outLog);
			delete[]_outLog;
			glDeleteProgram(_shaderProgramID);
			glDeleteShader(v_Shader);
			if (g_Shader != std::numeric_limits<uint32_t>::max()) {
				glDeleteShader(g_Shader);
			}
			glDeleteShader(f_Shader);
			return false;
		}/*
		glDetachShader(_shaderProgramID,v_Shader);
		if (g_Shader != std::numeric_limits<uint32_t>::max()) {
			glDetachShader(_shaderProgramID, g_Shader);
		}
		glDetachShader(_shaderProgramID, f_Shader);*/
		_shaderProgramID = _shaderProgramID;
		_isLastProgramCorrectlyLinked = true;
		return true;
	}
	const uint32_t BaseShaderLinker::GetLastShaderProgramID()const
	{
		_ASSERT(_isLastProgramCorrectlyLinked);
		return _shaderProgramID;
	}
}
