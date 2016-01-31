#pragma once

#include "Shader.h"

namespace apanoo {
	class BasicShader : public Shader
	{
	public:
		BasicShader();

		void updateUniforms(Matrix4 worldMatrix, Matrix4 projectedMatrix);
	};
}