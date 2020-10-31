// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_BASE_SHADER
#define REAL_BASE_SHADER

#include <unordered_map>
#include <string>

#include "real/core.hpp"

#define GL_SYNTAX_ERROR_MESSAGE "Syntax error"
#define SHADERS_MAX_COUNT 4
#define SHADERS_AVG_COUNT 2

namespace real {
	// TODO: Iterate over shader API again
	class REAL_API shader {
	public:
		virtual ~shader();

		// region Uniforms
		// Floats
		virtual void uniform_float(const std::string &name, glm::f32 value) = 0;
		virtual void uniform_float(const std::string &name, const glm::fvec2 &value) = 0;
		virtual void uniform_float(const std::string &name, const glm::fvec3 &value) = 0;
		virtual void uniform_float(const std::string &name, const glm::fvec4 &value) = 0;
		virtual void uniform_matrix(const std::string &name, const glm::fmat3 &matrix) = 0;
		virtual void uniform_matrix(const std::string &name, const glm::fmat4 &matrix) = 0;

		// Ints
		virtual void uniform_int(const std::string &name, glm::int32 value) = 0;
		virtual void uniform_int(const std::string &name, const glm::ivec2 &value) = 0;
		virtual void uniform_int(const std::string &name, const glm::ivec3 &value) = 0;
		virtual void uniform_int(const std::string &name, const glm::ivec4 &value) = 0;
		// endregion

		virtual const std::string& name() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	public:
		static shader *make(std::string name);
	};

	class REAL_API shader_lib {
	public:
		void add(const real::reference<shader> &shader);
		real::reference<shader> load(const std::string &filepath);
		real::reference<shader> load(const std::string &filepath, const std::string& name);

		real::reference<shader> get(const std::string &name);
	private:
		std::unordered_map<std::string , real::reference<shader>> shaders_;
	};
}

#endif //REAL_BASE_SHADER
