#pragma once
#include "Texture.h"
#include "../../maths/Maths.h"

namespace apanoo {
	class Material
	{
	public:
		Material(Texture* texture, Vector3 color);
		~Material();

		inline Texture* getTexture() const { return m_Texture; }
		inline Vector3 getColor() const { return m_Color; }
		void setTexture(Texture* texture) { m_Texture = texture; }
		void setColor(Vector3 color) { m_Color = color; }

	private:
		Texture* m_Texture;
		Vector3 m_Color;
	};
}