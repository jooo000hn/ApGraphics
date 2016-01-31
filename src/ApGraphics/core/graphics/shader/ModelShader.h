#pragma once

#include "Shader.h"

namespace apanoo {
	class ModelShader : public Shader
	{
	public:
		ModelShader();

		void updateUniforms(Matrix4 worldMatrix, Matrix4 projectedMatrix);
	};
}