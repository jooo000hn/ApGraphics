// 提供透视投影以及物体平移、旋转、放缩等变换
#pragma once
#include "../../maths/maths.h"
#include "Camera.h"

namespace apanoo {
	class Transform
	{
	public:
		Transform();
		~Transform();

		// 视图变换 TODO : 封装 setProjection 为静态
		Mat4 getProjectionTransformation();
		void setProjection(float fov, float width, float height, float near, float far)
		{
			m_Far    = fov;
			m_Width  = width;
			m_Height = height;
			m_Near   = near;
			m_Far    = far;
		}

		// 摄像机 TODO : 封装 setCamera 为静态
		void setCamera(Camera camera){ m_Camera = camera; }
		inline Camera* getCamera() { return &m_Camera; }

		// 模型变换
		Mat4 getTransformation();

		// 平移 x, y, z为平移量
		inline const Vec3 getTranslation() const { return m_Translation; }
		void setTranslation(Vec3& translation) { m_Translation = translation; }
		void setTranslation(float x, float y, float z) { m_Translation = Vec3(x, y, z); }

		// 旋转 x, y, z为绕旋转轴旋转的角度
		inline const Vec3 getRotation() const { return m_Rotation; }
		void setRotation(Vec3& rotation) { m_Rotation = rotation; }
		void setRotation(float x, float y, float z) { m_Rotation = Vec3(x, y, z); }

		// 放缩 x, y, z为放缩比例
		inline const Vec3 getScale() const { return m_Scale; }
		void setScale(Vec3& scale) { m_Scale = scale; }
		void setScale(float x, float y, float z) { m_Scale = Vec3(x, y, z); }

	private:

		// 模型变换矩阵
		Vec3 m_Translation;
		Vec3 m_Rotation;
		Vec3 m_Scale;

		// 透视投影参数
		float m_Near;
		float m_Far;
		float m_Width;
		float m_Height;
		float m_Fov;

		// 摄像机
		Camera m_Camera;
	};
}
