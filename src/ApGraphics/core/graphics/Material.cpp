#include "Material.h"

apanoo::Material::Material(Texture* texture, Vector3 color)
	: m_Texture(texture), m_Color(color)
{

}

apanoo::Material::~Material()
{
	delete m_Texture;
}

