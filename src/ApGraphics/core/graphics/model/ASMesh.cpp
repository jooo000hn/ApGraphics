#include "ASMesh.h"
#include "../../../log/Log.h"

namespace apanoo {
	///////////////////////////////////mesh entry///////////////////////////////////////
	ASMesh::MeshEntry::MeshEntry()
		: m_VBO(INVALID_OGL_VALUE), m_IBO(INVALID_OGL_VALUE), m_NumIndices(0), m_MaterialIndex(INVALID_OGL_VALUE)
	{

	}

	ASMesh::MeshEntry::~MeshEntry()
	{
		if (m_VBO != INVALID_OGL_VALUE)
		{
			glDeleteBuffers(1, &m_VBO);
		}

		if (m_IBO != INVALID_OGL_VALUE)
		{
			glDeleteBuffers(1, &m_IBO);
		}
	}

	void ASMesh::MeshEntry::init(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices)
	{
		m_NumIndices = indices.size();

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);
	}

	////////////////////////////////////assimp mesh//////////////////////////////////////
	ASMesh::~ASMesh()
	{
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			delete m_Textures[i];
		}

		// disable shader
		m_Shader->disable();
		delete m_Shader;
	}

	ASMesh::ASMesh(const std::string& filename, bool flipUVs)
		: m_IsLoaded(false), m_NumMeshEntries(0), m_FilePath(filename)
	{
		// ���� shader
		m_Shader = new ModelShader();
		m_Shader->enable();

		m_FlipUVs = flipUVs;

		if (!loadModelFromFile(filename))
		{
			std::cout << "failed to load assimp mesh: " << filename << std::endl;
			Log::Instance()->OutputError("failed to load assimp mesh: %s", filename.c_str());
			return;
		}
	}

	ASMesh::ASMesh(const std::string& filename)
		: ASMesh(filename, false)
	{
		
	}

	// ���� model
	bool ASMesh::loadModelFromFile(const std::string& filepath)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filepath, m_FlipUVs ? (aiProcessPreset_TargetRealtime_Quality | aiProcess_FlipUVs)
			: aiProcessPreset_TargetRealtime_Quality);

		if (!scene)
		{
			std::cout << "Couldn't load model, Error Importing Asset :" << filepath << std::endl;
			Log::Instance()->OutputError("Couldn't load model, Error Importing Asset : %s", filepath.c_str());
			return false;
		}

		m_MeshEntries.resize(scene->mNumMeshes);
		m_Textures.resize(scene->mNumMaterials);

		initMesh(scene, scene->mRootNode); // init mesh

		// �������� texture
		if (scene->mNumMaterials > 0)
		{
			if (!initMaterial(scene, filepath))
			{
				std::cout << "Material ���ز�����" << std::endl;
				m_IsLoaded = false;
				return false;
			}
		}
		m_IsLoaded = true;
		return true;
	}

	void ASMesh::initMesh(const aiScene* pScene, const aiNode* pNode)
	{
		for (unsigned int n = 0; n < pNode->mNumMeshes; ++n)
		{
			const struct aiMesh* paiMesh = pScene->mMeshes[pNode->mMeshes[n]];
			
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
			vertices.reserve(paiMesh->mNumVertices);
			indices.reserve(paiMesh->mNumFaces);
			std::cout << "mesh : " << paiMesh->mName.C_Str() << m_NumMeshEntries << " init! " << std::endl;
			// ���� mesh ����������
			m_MeshEntries[m_NumMeshEntries].m_MaterialIndex = paiMesh->mMaterialIndex;

			for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
				const aiVector3D* pPos = &(paiMesh->mVertices[i]);
				const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
				const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ?
					&(paiMesh->mTextureCoords[0][i]) : &Zero3D;

				Vertex v(Vector3(pPos->x, pPos->y, pPos->z),
					Vector2(pTexCoord->x, pTexCoord->y),   
					Vector3(pNormal->x, pNormal->y, pNormal->z)
					);
				vertices.push_back(v);
			}
			// ��ʼ����������
			for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
			{
				const aiFace& Face = paiMesh->mFaces[i];
				assert(Face.mNumIndices == 3);
				indices.push_back(Face.mIndices[0]);
				indices.push_back(Face.mIndices[1]);
				indices.push_back(Face.mIndices[2]);
			}

			// ��ʼ�� mesh
			m_MeshEntries[m_NumMeshEntries++].init(vertices, indices);
		}

		for (unsigned int i = 0; i < pNode->mNumChildren; i++)
		{
			initMesh(pScene, pNode->mChildren[i]);
		}
	}

	void ASMesh::render()
	{

		if (!m_IsLoaded) 
		{
			return;
		}
		glEnableVertexAttribArray(0); // lcoation 0 ����
		glEnableVertexAttribArray(1); // location 1 ��������
		glEnableVertexAttribArray(2); // location 2 ����

		for (unsigned int i = 0; i < m_MeshEntries.size(); i++) {
			glBindBuffer(GL_ARRAY_BUFFER, m_MeshEntries[i].m_VBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3)));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector2) + sizeof(Vector3)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_MeshEntries[i].m_IBO);

			const unsigned int materialIndex = m_MeshEntries[i].m_MaterialIndex;

			if (materialIndex < m_Textures.size() && m_Textures[materialIndex]) 
			{
				m_Textures[materialIndex]->bind(GL_TEXTURE0);
			}

			glDrawElements(GL_TRIANGLES, m_MeshEntries[i].m_NumIndices, GL_UNSIGNED_INT, 0);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	bool ASMesh::initMaterial(const aiScene* pScene, const std::string& filePath)
	{
		std::string::size_type slashIndex = filePath.find_last_of("\\/");
		std::string dir;

		if (slashIndex == std::string::npos) {
			dir = ".";
		}
		else if (slashIndex == 0) {
			dir = "/";
		}
		else {
			dir = filePath.substr(0, slashIndex);
		}

		bool Ret = true;
		// ��������
		for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
		{
			const aiMaterial* pMaterial = pScene->mMaterials[i];
			m_Textures[i] = NULL;
			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString path;

				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
					std::string fullPath = dir + "/" + path.data;
					m_Textures[i] = new Texture(GL_TEXTURE_2D, fullPath.c_str());

					if (!m_Textures[i]) {
						std::cout << "Error loading texture : " << fullPath << std::endl;
						delete m_Textures[i];
						m_Textures[i] = NULL;
						Ret = false;
					}
				}
			}
		}
		return Ret;
	}
}