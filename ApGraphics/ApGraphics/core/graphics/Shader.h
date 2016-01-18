#pragma once
#include "gl/glew.h"
#include "../../maths/maths.h"

namespace apanoo {
	class Shader
	{
	public:
		Shader();
		~Shader();

		void enable();
		void disable();

		// add vertex shader 
		void addVertexShader(const char* filename);

		// add geometry shader
		void addGeometryShader(const char* filename);

		// add fragment shader
		void addFragmentShader(const char* filename);

		// set uniform
		void setUniform1f(const GLchar* name, float value);
		void setUniform1fv(const GLchar* name, int count, float* value);
		void setUniform1iv(const GLchar* name, int count, int* value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const Vec2& vector);
		void setUniform3f(const GLchar* name, const Vec3& vector);
		void setUniform4f(const GLchar* name, const Vec4& vector);
		void setUniformMat4(const GLchar* name, const Mat4 &matrix);

	private:
		void addProgram(const char* filename, int type);
		void compileShader();
		GLuint getUniformLocation(const GLchar* name);
	private:
		GLuint m_Program;
		const char* m_VertPath;
		const char* m_GeomPath;
		const char* m_FragPath;
	};
}