#include "krpch.h"


#include "Platform/OpenGL/OpenGLShader.h"

#include "Kure/Core/Log.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace Kure {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}
		KR_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}


	OpenGLShader::OpenGLShader(const std::string& filepath) {
		KR_PROFILE_FUNCTION();
		std::string source = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
		Compile(shaderSources);

		//extract name from file path
		size_t lastSlash = filepath.find_last_of("/\\"); //finds last forward or back slash
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1; //accounts for no slashes
		size_t lastDot = filepath.rfind('.'); //finds dot
		lastDot = lastDot == std::string::npos ? filepath.size() : lastDot;
		m_Name = filepath.substr(lastSlash, lastDot - lastSlash);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name) {

		KR_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}


	std::string OpenGLShader::ReadFile(const std::string& filepath) {
		KR_PROFILE_FUNCTION();
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end); //go to end of file
			result.resize(in.tellg()); //get size of file
			in.seekg(0, std::ios::beg); //go back to beginning of file
			in.read(result.data(), result.size()); //read file into result
			in.close();
		}
		else {
			KR_CORE_ERROR("Could not open file '{0}'", filepath);
		}
		return result;
	}


	//split source file into different shaders
	std::unordered_map< GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		KR_PROFILE_FUNCTION();
		std::unordered_map < GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		const size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) { //while there are matches for pos
			size_t eol = source.find_first_of("\r\n", pos); //look from pos
			KR_CORE_ASSERT(eol != std::string::npos, "Syntax error"); //???
			size_t begin = pos + typeTokenLength + 1; //only allow 1 white space between token and shader type
			std::string type = source.substr(begin, eol - begin);  //get substring from position 'begin', and length 'eol - begin'
			KR_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //skip lines until we get to the actual glsl shader code
			pos = source.find(typeToken, nextLinePos);  //pos is now location of next token
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos)); //length of substring is from nextLinePos to next token, or end of file
		}

		return shaderSources;
	}


	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {

		KR_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();

		KR_CORE_ASSERT(shaderSources.size() <= 2, "Only two shaders are supported");
		std::array<GLenum, 2> ShaderIDs;
		int ShaderIDIndex = 0;
		for (const std::pair<GLenum, std::string>& kv : shaderSources) {
			GLenum type = kv.first;
			const std::string& sourceString = kv.second;

			unsigned int shader = glCreateShader(type);

			const char* source = sourceString.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				KR_CORE_ERROR("{0}", infoLog.data());
				KR_CORE_ASSERT(false, "Vertex shader compilation failed!");

				// stop compiling shaders if one fails to compile
				break;
			}

			glAttachShader(program, shader);
			ShaderIDs[ShaderIDIndex++] = shader;
		}




		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (GLuint id : ShaderIDs) {
				glDeleteShader(id);
			}

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return;

		}


		// Always detach shaders after a successful link.
		for (GLuint id : ShaderIDs) {
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}


	void OpenGLShader::Bind() const {
		KR_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		KR_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::SetIntArray(int* value, uint32_t count, const std::string& name) {
		KR_PROFILE_FUNCTION();
		UploadUniformIntArray(value, count, name);
	}


	void OpenGLShader::SetInt(int value, const std::string& name) {
		KR_PROFILE_FUNCTION();
		UploadUniformInt(value, name);
	}


	void OpenGLShader::SetFloat(float value, const std::string& name) {
		KR_PROFILE_FUNCTION();
		UploadUniformFloat(value, name);
	}


	void OpenGLShader::SetFloat3(const glm::vec3& value, const std::string& name) {
		KR_PROFILE_FUNCTION();
		UploadUniformFloat3(value, name);
	}
	void OpenGLShader::SetFloat4(const glm::vec4& value, const std::string& name) {
		KR_PROFILE_FUNCTION();
		UploadUniformFloat4(value, name);
	}
	void OpenGLShader::SetMat4(const glm::mat4& value, const std::string& name) {
		KR_PROFILE_FUNCTION();
		UploadUniformMat4(value, name);
	}


	void OpenGLShader::UploadUniformIntArray(int* value, uint32_t count, const std::string& name) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, value);
	}


	void OpenGLShader::UploadUniformInt(int value, const std::string& name) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(float value, const std::string& name) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::UploadUniformFloat2(glm::vec2 vec, const std::string& name) const {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}
	void OpenGLShader::UploadUniformFloat3(glm::vec3 vec, const std::string& name) const {

		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniformFloat4(glm::vec4 vec, const std::string& name) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::UploadUniformMat3(glm::mat3 matrix, const std::string& name) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(glm::mat4 matrix, const std::string& name) const {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
