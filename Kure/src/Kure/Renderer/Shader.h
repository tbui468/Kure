#pragma once

#include "glm/glm.hpp"
#include "Kure/Core.h"
#include <unordered_map>

namespace Kure {

	//interface for different rendering API shaders
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary {
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader); //add shader to library
		Ref<Shader> Load(const std::string& filepath); //create and add shader
		Ref<Shader> Load(const std::string& name, const std::string& filepath); //create and add with custom name
		Ref<Shader> Get(const std::string& name); //get shader from library
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}

