#include "SkeltonMesh.h"

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

namespace apanoo {
	void SkeltonMesh::VertexBoneData::AddBoneData(unsigned int BoneID, float Weight)
	{
		for (unsigned int i = 0; i < sizeof(IDs) / sizeof(IDs[0]); i++) 
		{
			if (Weights[i] == 0.0) 
			{
				IDs[i] = BoneID;
				Weights[i] = Weight;
				return;
			}
		}

		// should never get here - more bones than we have space for
		assert(0);
	}

	SkeltonMesh::SkeltonMesh()
	{
		m_VAO = 0;
		memset(m_Buffers, 0, sizeof(m_Buffers));
		m_NumBones = 0;
		m_pScene = NULL;
	}


	SkeltonMesh::~SkeltonMesh()
	{
		Clear();
	}


	void SkeltonMesh::Clear()
	{
		for (unsigned int i = 0; i < m_Textures.size(); i++) 
		{
			if (m_Textures[i]) 
			{
				delete m_Textures[i];
				m_Textures[i] = NULL;
			}
		}

		if (m_Buffers[0] != 0) 
		{
			glDeleteBuffers(sizeof(m_Buffers) / sizeof(m_Buffers[0]), m_Buffers);
		}

		if (m_VAO != 0) 
		{
			glDeleteVertexArrays(1, &m_VAO);
			m_VAO = 0;
		}
	}


	bool SkeltonMesh::LoadMesh(const std::string& Filename)
	{
		// Release the previously loaded mesh (if it exists)
		Clear();

		// Create the VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// Create the buffers for the vertices attributes
		glGenBuffers(sizeof(m_Buffers) / sizeof(m_Buffers[0]), m_Buffers);

		bool Ret = false;

		m_pScene = m_Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals);

		if (m_pScene) 
		{
			auto trans = m_pScene->mRootNode->mTransformation;
			m_GlobalInverseTransform = Matrix4(
					trans.a1, trans.b1, trans.c1, trans.d1,
					trans.a2, trans.b2, trans.c2, trans.d2,
					trans.a3, trans.b3, trans.c3, trans.d3,
					trans.a4, trans.b4, trans.c4, trans.d4
				);
			// m_GlobalInverseTransform = m_pScene->mRootNode->mTransformation;
			m_GlobalInverseTransform.inverse();
			Ret = InitFromScene(m_pScene, Filename);
		}
		else 
		{
			printf("Error parsing '%s': '%s'\n", Filename.c_str(), m_Importer.GetErrorString());
		}

		// Make sure the VAO is not changed from the outside
		glBindVertexArray(0);

		return Ret;
	}


	bool SkeltonMesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
	{
		m_Entries.resize(pScene->mNumMeshes);
		m_Textures.resize(pScene->mNumMaterials);

		std::vector<Vector3> Positions;
		std::vector<Vector3> Normals;
		std::vector<Vector2> TexCoords;
		std::vector<VertexBoneData> Bones;
		std::vector<unsigned int> Indices;

		unsigned int NumVertices = 0;
		unsigned int NumIndices = 0;

		// Count the number of vertices and indices
		for (unsigned int i = 0; i < m_Entries.size(); i++) 
		{
			m_Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
			m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
			m_Entries[i].BaseVertex = NumVertices;
			m_Entries[i].BaseIndex = NumIndices;

			NumVertices += pScene->mMeshes[i]->mNumVertices;
			NumIndices += m_Entries[i].NumIndices;
		}

		// Reserve space in the vectors for the vertex attributes and indices
		Positions.reserve(NumVertices);
		Normals.reserve(NumVertices);
		TexCoords.reserve(NumVertices);
		Bones.resize(NumVertices);
		Indices.reserve(NumIndices);

		// Initialize the meshes in the scene one by one
		for (unsigned int i = 0; i < m_Entries.size(); i++) 
		{
			const aiMesh* paiMesh = pScene->mMeshes[i];
			InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
		}

		if (!InitMaterials(pScene, Filename)) 
		{
			return false;
		}

		// Generate and populate the buffers with vertex attributes and the indices
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(POSITION_LOCATION);
		glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(TEX_COORD_LOCATION);
		glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(NORMAL_LOCATION);
		glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BONE_VB]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(BONE_ID_LOCATION);
		glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
		glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
		glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

		return (glGetError() == GL_NO_ERROR);
	}


	void SkeltonMesh::InitMesh(unsigned int MeshIndex,
		const aiMesh* paiMesh,
		std::vector<Vector3>& Positions,
		std::vector<Vector3>& Normals,
		std::vector<Vector2>& TexCoords,
		std::vector<VertexBoneData>& Bones,
		std::vector<unsigned int>& Indices)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		// Populate the vertex attribute vectors
		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) 
		{
			const aiVector3D* pPos = &(paiMesh->mVertices[i]);
			const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
			const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

			Positions.push_back(Vector3(pPos->x, pPos->y, pPos->z));
			Normals.push_back(Vector3(pNormal->x, pNormal->y, pNormal->z));
			TexCoords.push_back(Vector2(pTexCoord->x, pTexCoord->y));
		}

		LoadBones(MeshIndex, paiMesh, Bones);

		// Populate the index buffer
		for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) 
		{
			const aiFace& Face = paiMesh->mFaces[i];
			assert(Face.mNumIndices == 3);
			Indices.push_back(Face.mIndices[0]);
			Indices.push_back(Face.mIndices[1]);
			Indices.push_back(Face.mIndices[2]);
		}
	}


	void SkeltonMesh::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBoneData>& Bones)
	{
		for (unsigned int i = 0; i < pMesh->mNumBones; i++) 
		{
			unsigned int BoneIndex = 0;
			std::string BoneName(pMesh->mBones[i]->mName.data);

			if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) 
			{
				// Allocate an index for a new bone
				BoneIndex = m_NumBones;
				m_NumBones++;
				BoneInfo bi;
				m_BoneInfo.push_back(bi);

				auto offset = pMesh->mBones[i]->mOffsetMatrix;
				m_BoneInfo[BoneIndex].BoneOffset = Matrix4(
						offset.a1, offset.b1, offset.c1, offset.d1,
						offset.a2, offset.b2, offset.c2, offset.d2,
						offset.a3, offset.b3, offset.c3, offset.d3,
						offset.a4, offset.b4, offset.c4, offset.d4
					);
				//m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
				m_BoneMapping[BoneName] = BoneIndex;
			}
			else 
			{
				BoneIndex = m_BoneMapping[BoneName];
			}

			for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) 
			{
				unsigned int VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
				float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
				Bones[VertexID].AddBoneData(BoneIndex, Weight);
			}
		}
	}


	bool SkeltonMesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
	{
		// Extract the directory part from the file name
		std::string::size_type SlashIndex = Filename.find_last_of("/");
		std::string Dir;

		if (SlashIndex == std::string::npos) 
		{
			Dir = ".";
		}
		else if (SlashIndex == 0) 
		{
			Dir = "/";
		}
		else 
		{
			Dir = Filename.substr(0, SlashIndex);
		}

		bool Ret = true;

		// Initialize the materials
		for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
			const aiMaterial* pMaterial = pScene->mMaterials[i];

			m_Textures[i] = NULL;

			if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
			{
				aiString Path;

				if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
				{
					std::string p(Path.data);

					if (p.substr(0, 2) == ".\\") 
					{
						p = p.substr(2, p.size() - 2);
					}

					std::string FullPath = Dir + "/" + p;

					m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

					if (!m_Textures[i]) 
					{
						printf("Error loading texture '%s'\n", FullPath.c_str());
						delete m_Textures[i];
						m_Textures[i] = NULL;
						Ret = false;
					}
					else 
					{
						printf("%d - loaded texture '%s'\n", i, FullPath.c_str());
					}
				}
			}
		}

		return Ret;
	}


	void SkeltonMesh::Render()
	{
		glBindVertexArray(m_VAO);

		for (unsigned int i = 0; i < m_Entries.size(); i++) 
		{
			const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

			assert(MaterialIndex < m_Textures.size());

			if (m_Textures[MaterialIndex]) 
			{
				m_Textures[MaterialIndex]->bind(GL_TEXTURE0);
			}

			glDrawElementsBaseVertex(GL_TRIANGLES,
				m_Entries[i].NumIndices,
				GL_UNSIGNED_INT,
				(void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex),
				m_Entries[i].BaseVertex);
		}

		// Make sure the VAO is not changed from the outside    
		glBindVertexArray(0);
	}


	unsigned int SkeltonMesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) 
		{
			if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) 
			{
				return i;
			}
		}

		assert(0);

		return 0;
	}


	unsigned int SkeltonMesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumRotationKeys > 0);

		for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) 
		{
			if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) 
			{
				return i;
			}
		}

		assert(0);

		return 0;
	}


	unsigned int SkeltonMesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumScalingKeys > 0);

		for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) 
		{
			if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) 
			{
				return i;
			}
		}

		assert(0);

		return 0;
	}


	void SkeltonMesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumPositionKeys == 1) 
		{
			Out = pNodeAnim->mPositionKeys[0].mValue;
			return;
		}

		unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
		unsigned int NextPositionIndex = (PositionIndex + 1);
		assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
		float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
		const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}


	void SkeltonMesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		// we need at least two values to interpolate...
		if (pNodeAnim->mNumRotationKeys == 1) 
		{
			Out = pNodeAnim->mRotationKeys[0].mValue;
			return;
		}

		unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
		unsigned int NextRotationIndex = (RotationIndex + 1);
		assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
		float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
		const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
		aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
		Out = Out.Normalize();
	}


	void SkeltonMesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumScalingKeys == 1) 
		{
			Out = pNodeAnim->mScalingKeys[0].mValue;
			return;
		}

		unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
		unsigned int NextScalingIndex = (ScalingIndex + 1);
		assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
		float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
		const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}

	void SkeltonMesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4& ParentTransform)
	{
		std::string NodeName(pNode->mName.data);

		const aiAnimation* pAnimation = m_pScene->mAnimations[0];

		auto nodeTrans = pNode->mTransformation;
		Matrix4 NodeTransformation = Matrix4(
			nodeTrans.a1, nodeTrans.b1, nodeTrans.c1, nodeTrans.d1,
			nodeTrans.a2, nodeTrans.b2, nodeTrans.c2, nodeTrans.d2,
			nodeTrans.a3, nodeTrans.b3, nodeTrans.c3, nodeTrans.d3,
			nodeTrans.a4, nodeTrans.b4, nodeTrans.c4, nodeTrans.d4
			);
		// Matrix4 NodeTransformation(pNode->mTransformation);

		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

		if (pNodeAnim) 
		{
			// Interpolate scaling and generate scaling transformation matrix
			aiVector3D Scaling;
			CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
			Matrix4 ScalingM = Matrix4().scaleMatrix(Vector3(Scaling.x, Scaling.y, Scaling.z));
			// ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);

			// Interpolate rotation and generate rotation transformation matrix
			aiQuaternion RotationQ;
			CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);

			auto rot = RotationQ.GetMatrix();
			Matrix4 RotationM = Matrix4(
					rot.a1, rot.b1, rot.c1, 0,
					rot.a2, rot.b2, rot.c2, 0,
					rot.a3, rot.b3, rot.c3, 0,
					0     , 0     , 0     , 1
				);
			// Matrix4 RotationM = Matrix4(RotationQ.GetMatrix());

			// Interpolate translation and generate translation transformation matrix
			aiVector3D Translation;
			CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
			Matrix4 TranslationM = Matrix4().translationMatrix(Vector3(Translation.x, Translation.y, Translation.z));
			// TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);

			// Combine the above transformations
			NodeTransformation = TranslationM * RotationM * ScalingM;
		}

		Matrix4 GlobalTransformation = ParentTransform * NodeTransformation;

		if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) 
		{
			unsigned int BoneIndex = m_BoneMapping[NodeName];
			m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
		}

		for (unsigned int i = 0; i < pNode->mNumChildren; i++) 
		{
			ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
		}
	}

	void SkeltonMesh::BoneTransform(float TimeInSeconds, std::vector<Matrix4>& Transforms)
	{
		Matrix4 Identity = Matrix4().identityMatrix();
		// Identity.InitIdentity();

		float TicksPerSecond = (float)(m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f);
		float TimeInTicks = TimeInSeconds * TicksPerSecond;
		float AnimationTime = fmod(TimeInTicks, (float)m_pScene->mAnimations[0]->mDuration);

		ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, Identity);

		Transforms.resize(m_NumBones);

		for (unsigned int i = 0; i < m_NumBones; i++) {
			Transforms[i] = m_BoneInfo[i].FinalTransformation;
		}
	}

	const aiNodeAnim* SkeltonMesh::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
	{
		for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) 
		{
			const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
			if (std::string(pNodeAnim->mNodeName.data) == NodeName) 
			{
				return pNodeAnim;
			}
		}

		return NULL;
	}
}