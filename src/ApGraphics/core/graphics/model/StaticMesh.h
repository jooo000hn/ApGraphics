/*
* ASMesh : assimp mesh, 使用开源库 assimp 加载模型文件
* 支持格式 : obj, 3ds, ms3d, fbx, md2, md3, md5...等40多种模型格式
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
		bool	m_FlipUVs;					    // 翻转纹理 y 坐标 
		int     m_NumMaterials;					// 纹理数量
		std::vector<MeshEntry> m_MeshEntries;   // 所有子 mesh
		std::vector<Texture*>  m_Textures;      // 所有纹理图
		unsigned int m_NumMeshEntries;
		std::string m_FilePath;
	};
}