#pragma once
#include<string>
#include "BaseShaderCompiler.h"
#include "BaseShaderLinker.h"
#include <memory>
namespace SHB {
	class BaseShaderHandler
	{
		bool _isActive;
		bool _isCrashed;
		std::unique_ptr<BaseShaderCompiler> v_compiler;
		std::unique_ptr<BaseShaderCompiler> g_compiler;
		std::unique_ptr<BaseShaderCompiler> f_compiler;
		std::unique_ptr < BaseShaderLinker> linker;
	public:
		BaseShaderHandler(std::string v_shader_source, std::string f_shader_source, std::string g_shader_source = "");
		const uint32_t GetShaderProgramId() const;
		const bool ReInit(std::string v_shader_source, std::string f_shader_source, std::string g_shader_source = "");
		const bool Reload()const;
		const bool IsActive()const;
		const bool IsCrashed()const;
		void SetActive(bool isActive);
	};
}

