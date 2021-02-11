#include"BaseShaderHandler.h"
#include<glad.h>
#include"Logger.h"
namespace SHB {
	BaseShaderHandler::BaseShaderHandler(std::string v_shader_source, std::string f_shader_source, std::string g_shader_source) :
		v_compiler(nullptr),
		g_compiler(nullptr),
		f_compiler(nullptr),
		linker(nullptr)
	{
		std::string out;
		v_compiler = std::make_unique<BaseShaderCompiler>(v_shader_source, GL_VERTEX_SHADER);
		f_compiler = std::make_unique<BaseShaderCompiler>(f_shader_source, GL_FRAGMENT_SHADER);
		if (!v_compiler->Reload_ShaderSource(out) ||
			!v_compiler->ReloadShader(out) ||
			!f_compiler->Reload_ShaderSource(out) ||
			!f_compiler->ReloadShader(out)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return;
		}
		if (g_shader_source != "") {
			g_compiler = std::make_unique<BaseShaderCompiler>(g_shader_source, GL_GEOMETRY_SHADER);
			if (!g_compiler->Reload_ShaderSource(out) ||
				!g_compiler->ReloadShader(out)) {
				LOG::Logger::LOG(out);
				_isCrashed = true;
				return;
			}
		}
		linker = std::make_unique <BaseShaderLinker>();
		uint32_t v_ID = v_compiler->GetShaderID(out);
		uint32_t g_ID = std::numeric_limits<uint32_t>::max();
		if (g_compiler) {
			g_ID = g_compiler->GetShaderID(out);
		}
		uint32_t f_ID = f_compiler->GetShaderID(out);
		if (v_ID == std::numeric_limits<uint32_t>::max() ||
			f_ID == std::numeric_limits<uint32_t>::max() || (g_ID == std::numeric_limits<uint32_t>::max() && g_compiler)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return;
		}
		if (!linker->LinkShader(v_ID, f_ID, out, g_ID)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return;
		}
		_isCrashed = false;
	}
	const uint32_t BaseShaderHandler::GetShaderProgramId()const {
		if (!linker) {
			LOG::Logger::LOG("SHADER::IS::EMPTY");
			throw(0);
		}
		return linker->GetLastShaderProgramID();
	}
	const bool BaseShaderHandler::ReInit(std::string v_shader_source, std::string f_shader_source, std::string g_shader_source)
	{
		std::string out;
		v_compiler = std::make_unique<BaseShaderCompiler>(v_shader_source, GL_VERTEX_SHADER);
		f_compiler = std::make_unique<BaseShaderCompiler>(f_shader_source, GL_FRAGMENT_SHADER);
		if (!v_compiler->Reload_ShaderSource(out) ||
			!v_compiler->ReloadShader(out) ||
			!f_compiler->Reload_ShaderSource(out) ||
			!f_compiler->ReloadShader(out)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return false;
		}
		if (g_shader_source != "") {
			g_compiler = std::make_unique<BaseShaderCompiler>(g_shader_source, GL_GEOMETRY_SHADER);
			if (!g_compiler->Reload_ShaderSource(out) ||
				!g_compiler->ReloadShader(out)) {
				LOG::Logger::LOG(out);
				_isCrashed = true;
				return false;
			}
		}
		linker = std::make_unique <BaseShaderLinker>();
		uint32_t v_ID = v_compiler->GetShaderID(out);
		uint32_t g_ID;
		if (g_compiler) {
			g_ID = g_compiler->GetShaderID(out);
		}
		uint32_t f_ID = f_compiler->GetShaderID(out);
		if (v_ID == std::numeric_limits<uint32_t>::max() ||
			f_ID == std::numeric_limits<uint32_t>::max() || (g_ID == std::numeric_limits<uint32_t>::max() && !g_compiler)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return false;
		}
		if (!linker->LinkShader(v_ID, f_ID, out, g_ID)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return false;
		}
		_isCrashed = false;
		return true;
	}
	const bool BaseShaderHandler::Reload()
	{
		if (!linker || !f_compiler || !v_compiler) {
			return false;
		}
		std::string out;
		if (!v_compiler->Reload_ShaderSource(out) ||
			!v_compiler->ReloadShader(out) ||
			!f_compiler->Reload_ShaderSource(out) ||
			!f_compiler->ReloadShader(out)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return false;
		}
		if (g_compiler) {
			if (!g_compiler->Reload_ShaderSource(out) ||
				!g_compiler->ReloadShader(out)) {
				LOG::Logger::LOG(out);
				_isCrashed = true;
				return false;
			}
		}
		uint32_t v_ID = v_compiler->GetShaderID(out);
		uint32_t g_ID = 0u;
		if (g_compiler) {
			g_ID = g_compiler->GetShaderID(out);
		}
		uint32_t f_ID = f_compiler->GetShaderID(out);
		if (v_ID == std::numeric_limits<uint32_t>::max() ||
			f_ID == std::numeric_limits<uint32_t>::max() || (g_ID == std::numeric_limits<uint32_t>::max() && !g_compiler)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return false;
		}
		if (!linker->LinkShader(v_ID, f_ID, out, g_ID)) {
			LOG::Logger::LOG(out);
			_isCrashed = true;
			return false;
		}
		_isCrashed = false;
		return true;
	}
	const bool BaseShaderHandler::IsActive() const
	{
		return _isActive;
	}
	const bool BaseShaderHandler::IsCrashed() const
	{
		return _isCrashed;
	}
	void BaseShaderHandler::SetActive(bool isActive)
	{
		if (isActive) {
			std::string out;
			uint32_t v_ID = v_compiler->GetShaderID(out);
			uint32_t g_ID;
			if (g_compiler) {
				g_ID = g_compiler->GetShaderID(out);
			}
			uint32_t f_ID = f_compiler->GetShaderID(out);
			if (v_ID == std::numeric_limits<uint32_t>::max() ||
				f_ID == std::numeric_limits<uint32_t>::max() || (g_ID == std::numeric_limits<uint32_t>::max() && !g_compiler)) {
				LOG::Logger::LOG(out);
				_isCrashed = true;
				return;
			}
			if (!linker->LinkShader(v_ID, f_ID, out, g_ID)) {
				LOG::Logger::LOG(out);
				_isCrashed = true;
				return;
			}
			_isCrashed = false;
		}
		else {
			linker->DeleteShaderProgram();
		}
	}
}