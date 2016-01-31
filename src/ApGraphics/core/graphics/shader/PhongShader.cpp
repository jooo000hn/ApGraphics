#include "PhongShader.h"

apanoo::PhongShader::PhongShader()
	: Shader()
{
	addVertexShader("../media/shaders/phong.vert");
	addFragmentShader("../media/shaders/phong.frag");
	compileShader();
}

void apanoo::PhongShader::updateUniforms(Matrix4 worldMatrix, Matrix4 projectedMatrix)
{
	setUniformMat4("transform", projectedMatrix);
	setUniform3f("baseColor", m_BaseColor);
	setUniform3f("ambientLight", m_AmbientLight);
}

