#pragma once

#include "Shader.h"

namespace apanoo {
	class PhongShader : public Shader
	{
	public:
		PhongShader();

		static PhongShader * Instance()
		{
			static PhongShader instance;
			return &instance;
		}

		void updateUniforms(Matrix4 worldMatrix, Matrix4 projectedMatrix);

		inline Vector3 getBaseColor()  const { return m_BaseColor; }
		inline void setBaseColor(Vector3& BaseColor) { m_BaseColor = BaseColor; }

		inline Vector3 getAmbientLight()  const { return m_AmbientLight; }
		inline void setAmbientLight(Vector3& AmbientLight) { m_AmbientLight = AmbientLight; }
	private:
		Vector3 m_BaseColor;
		Vector3 m_AmbientLight;
	};
}