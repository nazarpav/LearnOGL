#include "BaseShaderCompiler.h"
#include <glad.h>
#include <glfw3.h>
#include <fstream>
namespace SHB {
	BaseShaderCompiler::BaseShaderCompiler(std::string sourcePath, int shaderType) :
		_sourceShaderPath(sourcePath),
		_resShaderID(0u),
		_shaderType(shaderType),
		_shaderSource(nullptr),
		_isLoaded(false)
	{
	}
	BaseShaderCompiler::~BaseShaderCompiler() {
		if (_shaderSource) {
			delete[] _shaderSource;
		}
	}
	void BaseShaderCompiler::SetSource(std::string sourcePath) {
		_sourceShaderPath = sourcePath;
	}
	const bool BaseShaderCompiler::ReloadShader(std::string& out) {
		if (!CheckIsInputShaderTypeCorrect(_shaderType)) {
			out += "INCORRECT::SHADER::TYPE";
			return false;
		}
		_resShaderID = glCreateShader(_shaderType);
		if (!_shaderSource || _shaderSource == "") {
			out += GetShaderNameByType(_shaderType) + "::SHADER::PROGRAM::IS::EMPTY";
			return false;
		}
		glShaderSource(_resShaderID, 1, &_shaderSource, &_shaderSourceLength);
		glCompileShader(_resShaderID);
		int success;
		glGetShaderiv(_resShaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			_outLogSize = 512;
			_outLog = new char[_outLogSize];
			glGetShaderInfoLog(_resShaderID, _outLogSize, NULL, _outLog);
			out += "ERROR::" + GetShaderNameByType(_shaderType) + "::SHADER::" + GetShaderNameByType(_shaderType) + "::COMPILATION_FAILED" + std::string(_outLog);
			delete[]_outLog;
			return false;
		}
		_isLoaded = true;
		return true;
	}
	const bool BaseShaderCompiler::Reload_ShaderSource(std::string& out) {
		std::string line;
		std::string outData;
		std::ifstream in(_sourceShaderPath);
		if (in.is_open()) {
			while (std::getline(in, line)) {
				outData += line + '\n';
			}
		}
		else {
			out += GetShaderNameByType(_shaderType) + " Shader file not found is path: " + _sourceShaderPath;
			return false;
		}
		in.close();
		outData += '\0';
		_shaderSourceLength = outData.length();
		_shaderSource = new char[_shaderSourceLength];
		for (size_t i = 0; i < outData.length(); ++i) {
			_shaderSource[i] = outData.c_str()[i];
		}
		return true;
	}
	const uint32_t BaseShaderCompiler::GetShaderID(std::string& out) const
	{
		if (!_isLoaded) {
			out += GetShaderNameByType(_shaderType) + "::SHADER::IS::NOT::LOADED";
			return std::numeric_limits<uint32_t>::max();
		}
		return _resShaderID;
	}
	bool BaseShaderCompiler::CheckIsInputShaderTypeCorrect(int shaderType) const {
		return GL_VERTEX_SHADER == shaderType || GL_GEOMETRY_SHADER == shaderType || GL_FRAGMENT_SHADER == shaderType;
	}
	const std::string BaseShaderCompiler::GetShaderNameByType(int type) const {
		switch (type) {
		case GL_VERTEX_SHADER:return "VERTEX";
		case GL_GEOMETRY_SHADER:return "GEOMETRY";
		case GL_FRAGMENT_SHADER:return "FRAGMENT";
		default:return "ERROR::TYPE";
		}
	}
}