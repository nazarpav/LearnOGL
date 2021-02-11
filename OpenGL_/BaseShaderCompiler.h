#pragma once
#include<string>
#include"LogComponent.h"
namespace SHB {
	class BaseShaderCompiler :public Components::LogComponent {
	private:
		char* _shaderSource;
		int _shaderSourceLength;
		std::string _sourceShaderPath;
		uint32_t _resShaderID;
		int _shaderType;
		bool _isLoaded;
	public:
		BaseShaderCompiler(std::string sourcePath, int shaderType);
		~BaseShaderCompiler();
		void SetSource(std::string sourcePath);
		const bool ReloadShader(std::string& out);
		const bool Reload_ShaderSource(std::string& out);
		const uint32_t GetShaderID(std::string& out)const;
	private:
		bool CheckIsInputShaderTypeCorrect(int shaderType) const;
		const std::string GetShaderNameByType(int type)const;
	};
}