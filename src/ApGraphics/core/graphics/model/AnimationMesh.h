#pragma once
#include "../../../maths/Maths.h"
#include "../Texture.h"

#ifndef _VECTOR_
	#include <vector>
#endif // !_VECTOR_

#ifndef _STRING_
	#include <string>
#endif // !_STRING_

#ifndef _MAP_
	#include <map>
#endif // !_MAP_

// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace apanoo {
	class AnimationMesh
	{
	public:
		AnimationMesh();

		~AnimationMesh();

		bool LoadMesh(const std::string& Filename);

		void Render();

		unsigned int NumBones() const
		{
			return m_NumBones;
		}

		void BoneTransform(float TimeInSeconds, std::vector<Matrix4>& Transforms);

	private:
#define NUM_BONES_PER_VEREX 4

		struct BoneInfo
		{
			Matrix4 BoneOffset;
			Matrix4 FinalTransformation;

			BoneInfo()
			{
	
			}
		};

		struct VertexBoneData
		{
			unsigned int IDs[NUM_BONES_PER_VEREX];
			float Weights[NUM_BONES_PER_VEREX];

			VertexBoneData()
			{
				Reset();
			};

			void Reset()
			{
				memset(IDs, 0, sizeof(IDs));
				memset(Weights, 0, sizeof(Weights));
			}

			void AddBoneData(unsigned int BoneID, float Weight);
		};

		void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
		unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
		const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);
		void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4& ParentTransform);
		bool InitFromScene(const aiScene* pScene, const std::string& Filename);
		void InitMesh(unsigned int MeshIndex,
			const aiMesh* paiMesh,
			std::vector<Vector3>& Positions,
			std::vector<Vector3>& Normals,
			std::vector<Vector2>& TexCoords,
			std::vector<VertexBoneData>& Bones,
			std::vector<unsigned int>& Indices);
		void LoadBones(unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<VertexBoneData>& Bones);
		bool InitMaterials(const aiScene* pScene, const std::string& Filename);
		void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

		enum VB_TYPES {
			INDEX_BUFFER,
			POS_VB,
			NORMAL_VB,
			TEXCOORD_VB,
			BONE_VB,
			NUM_VBs
		};

		GLuint m_VAO;
		GLuint m_Buffers[NUM_VBs];

		struct MeshEntry {
			MeshEntry()
			{
				NumIndices = 0;
				BaseVertex = 0;
				BaseIndex = 0;
				MaterialIndex = INVALID_MATERIAL;
			}

			unsigned int NumIndices;
			unsigned int BaseVertex;
			unsigned int BaseIndex;
			unsigned int MaterialIndex;
		};

		std::vector<MeshEntry> m_Entries;
		std::vector<Texture*> m_Textures;

		std::map<std::string, unsigned int> m_BoneMapping; // maps a bone name to its index
		unsigned int m_NumBones;
		std::vector<BoneInfo> m_BoneInfo;
		Matrix4 m_GlobalInverseTransform;

		const aiScene* m_pScene;
		Assimp::Importer m_Importer;
	};
}