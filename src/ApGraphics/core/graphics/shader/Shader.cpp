#include "Shader.h"
#include <string>
#include <vector>
#include <iostream>
<<<<<<< HEAD:src/ApGraphics/core/graphics/shader/Shader.cpp
#include "../../../log/Log.h"
#include "../../../utils/FileUtils.h"
=======
#include "../../log/Log.h"
#include "../../utils/ResourcesLoader.h"
>>>>>>> origin/master:ApGraphics/ApGraphics/core/graphics/Shader.cpp

namespace apanoo {
	Shader::Shader()
	{
		m_Program = glCreateProgram();
		if (0 == m_Program)
		{
			std::cout << "shader creation : could not find valid memory location in constructor" << std::endl;
			Log::Instance()->OutputError("shader creation : could not find valid memory location in constructor");
			return;
		}
	}

	Shader::~Shader()
	{
	}

	void Shader::addVertexShader(const char* filename)
	{
		addProgram(filename, GL_VERTEX_SHADER);
	}

	void Shader::addGeometryShader(const char* filename)
	{
		addProgram(filename, GL_GEOMETRY_SHADER);
	}

	void Shader::addFragmentShader(const char* filename)
	{
		addProgram(filename, GL_FRAGMENT_SHADER);
	}

	void Shader::addProgram(const char* filename, int type)
	{
		GLuint shader = glCreateShader(type);
		if (0 == shader)
		{
			Log::Instance()->OutputError("shader creation : could not find valid memory location when adding shader");
			return;
		}

		// 读取shader
<<<<<<< HEAD:src/ApGraphics/core/graphics/shader/Shader.cpp
		std::string SourceString = FileUtils::readShader(filename);
=======
		std::string SourceString = ResourcesLoader::load_shader(filename);
>>>>>>> origin/master:ApGraphics/ApGraphics/core/graphics/Shader.cpp
		const char* source = SourceString.c_str();

		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		GLint result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)    // 捕获编译错误信息
		{
			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shader, length, &length, &error[0]);
			std::cout << "error compile shader : " << &error[0] << std::endl;
			Log::Instance()->OutputError("shader compile error！msg：%s", &error[0]);
			glDeleteShader(shader);
			return;
		}

		// attach
		glAttachShader(m_Program, shader);

		compileShader();

		glDeleteShader(shader);
	}

	void Shader::compileShader()
	{
		// link
		glLinkProgram(m_Program);

		// validate
		glValidateProgram(m_Program);
	}

	void Shader::enable()
	{
		glUseProgram(m_Program);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	///////////////////////////////set uniform///////////////////////////////////////////
	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar* name, int count, float* value)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1iv(const GLchar* name, int count, int* value)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const Vector2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.getX(), vector.getY());
	}

	void Shader::setUniform3f(const GLchar* name, const Vector3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ());
	}

	void Shader::setUniform4f(const GLchar* name, const Vector4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.getX(), vector.getY(), vector.getZ(), vector.getW());
	}

	/*
	 * 注意 glUniformMatrix4fv 第三个参数含义：
	 *		GL_TRUE  表示传送的矩阵按行主序制定，与C语言数组类似
	 *		GL_FALSE 表示传送的矩阵按列主序制定，与glLoadMatrix()使用顺序相同
	 */
	void Shader::setUniformMat4(const GLchar* name, const Matrix4 &matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix[0]);
	}

	// get uniform location
	GLuint Shader::getUniformLocation(const GLchar* name)
	{
		GLuint location = glGetUniformLocation(m_Program, name);
		if (location == 0xFFFFFFFF)
		{
			std::cout << "Error : Could not find uniform :" + std::string(name) << std::endl;
			Log::Instance()->OutputError("Error : Could not find uniform : %s", name);
			return -1;
		}
		return location;
	}
}