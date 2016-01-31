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

// shader
#include "../Shader.h"

// texture
#include "../Texture.h"

// Vertex
#include "../Vertex.h"

namespace apanoo {
	// 顶点
	//struct Vertex
	//{
	//	Vector3 m_Pos;    // 顶点位置
	//	Vector2 m_TexCoord; // 文理坐标
	//	Vector3 m_Normal; // 法向
	//
	//	Vertex() {}
	//
	//	Vertex(const Vector3& pos, const Vector2& tex, const Vector3& normal)
	//		: m_Pos(pos), m_TexCoord(tex), m_Normal(normal)
	//	{
	//		
	//	}
	//};

	/*
	 * assimp mesh : load model files by assimp lib
	 */
	class ASMesh
	{
	public:
		~ASMesh();
		ASMesh(Shader& shader, const std::string& filename);
		void render();

	private:
		bool loadModelFromFile(const std::string& filename);
		void initMesh(unsigned int Index, const aiMesh* paiMesh);
		bool initMaterial(const aiScene* pScene, const std::string& filePath);

	private:
		/*
		 * mesh entry : 一个模型由一张或多张 mesh 组成
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
			unsigned int m_NumIndices;     // 索引数量
			unsigned int m_MaterialIndex;  // 对应的文理图索引
		};

	private:
		bool    m_IsLoaded;
		int     m_NumMaterials;
		Shader* m_Shader;
		std::vector<MeshEntry> m_MeshEntries;   // 所有子 mesh
		std::vector<Texture*>  m_Textures;      // 所有文理图
	};
}