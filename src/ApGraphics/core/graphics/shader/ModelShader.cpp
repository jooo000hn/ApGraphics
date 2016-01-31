#include "ModelShader.h"

apanoo::ModelShader::ModelShader() 
	: Shader()
{
	addVertexShader("../media/shaders/model.vert");
	addFragmentShader("../media/shaders/model.frag");
	compileShader();
}

void apanoo::ModelShader::updateUniforms(Matrix4 worldMatrix, Matrix4 projectedMatrix)
{
	setUniformMat4("transform", projectedMatrix);
}
