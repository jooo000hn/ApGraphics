#include "BasicShader.h"

apanoo::BasicShader::BasicShader() 
	: Shader()
{
	addVertexShader("../media/shaders/basic.vert");
	addFragmentShader("../media/shaders/basic.frag");
	compileShader();
}

void apanoo::BasicShader::updateUniforms(Matrix4 worldMatrix, Matrix4 projectedMatrix)
{
	setUniformMat4("transform", projectedMatrix);
}
