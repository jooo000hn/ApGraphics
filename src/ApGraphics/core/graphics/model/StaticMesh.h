/*
* ASMesh : assimp mesh, ʹ�ÿ�Դ�� assimp ����ģ���ļ�
* ֧�ָ�ʽ : obj, 3ds, ms3d, fbx, md2, md3, md5...��40����ģ�͸�ʽ
*/
#pragma once
#define INVALID_OGL_VALUE 0xFFFFFFFF

#ifndef _VECTOR_
	#include <vector>
#endif // !_VECTOR_

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#ifndef _STRING_
	#include <string>
#endif // !_STRING_

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// maths
#include "../../../maths/Maths.h"

#include "../shader/Shader.h"

// texture
#include "../Texture.h"

// Vertex
#include "../Vertex.h"

namespace apanoo {
	/*
	 * assimp mesh : load model files by assimp lib
	 */
	class StaticMesh
	{
	public:
		~StaticMesh();
		StaticMesh(const std::string& filename, bool flipUVs = false);
		void render();

	private:
		bool loadModelFromFile(const std::string& filename);
		void initMesh(const aiScene* pScene, const aiNode* pNode);
		bool initMaterial(const aiScene* pScene, const std::string& filePath);

	private:
		/*
		 * mesh entry : һ��ģ����һ�Ż���� mesh ���
		 */
		struct MeshEntry {
			MeshEntry();

			~MeshEntry();

			void init(const std::vector<Vertex>& vertices,
				const std::vector<unsigned int>& indices);

			// For vertex buffer
			GLuint m_VBO;
			// For index buffer
			GLuint m_IBO;
			unsigned int m_NumIndices;     // ��������
			unsigned int m_MaterialIndex;  // ��Ӧ������ͼ����
		};

	private:
		bool    m_IsLoaded;
		bool	m_FlipUVs;					    // ��ת���� y ���� 
		int     m_NumMaterials;					// ��������
		std::vector<MeshEntry> m_MeshEntries;   // ������ mesh
		std::vector<Texture*>  m_Textures;      // ��������ͼ
		unsigned int m_NumMeshEntries;
		std::string m_FilePath;
	};
}