#pragma once

#ifndef __GLEW_H__
	#include <GL/glew.h>
#endif // !__GLEW_H__

#ifndef _STRING_
	#include <string>
#endif // !_STRING_

#ifndef _FSTREAM_
	#include <fstream>
#endif // !_FSTREAM_

#include "../../../../maths/Maths.h"
#include "../../Texture.h"
#include "MD5Anim.h"

namespace apanoo {

	// ogl����
	struct ogl_vertex_t
	{
		Vector3 position;
		Vector2 texCoord;
		Vector4 indices;
		Vector4 weight;
	};

	// ogl mesh
	struct ogl_mesh_t
	{
		std::string texture;
		ogl_vertex_t* vertexArray;
		unsigned int* indexArray;
		unsigned int  numVertices;
		unsigned int  numIndices;
	};

	// ��������
	struct md5_vertex_t
	{
		Vector2 texCoord; // ��������
		int startWeight;  // Ȩ��������ʼ
		int numWeights;    // Ȩ������
	};

	// ��������Ϣ
	struct md5_triangle_t
	{
		int indices[3];   // �����ζ�������
	};

	// Ȩ����Ϣ
	struct md5_weight_t
	{
		int jointID;      // �ؽ�����
		float bias;
		Vector3 position; 
		Vector4 orientation;
	};

	// �����ؽ���Ϣ
	struct md5_joint_t
	{
		std::string name;
		int parentID;
		Vector3 position;
		Quaternion orientation;
	};

	// mesh��Ϣ
	struct md5_mesh_t
	{
		std::string shader;			// ����ȫ·��
		md5_vertex_t* vertexArray;
		md5_triangle_t* triangleArray;
		md5_weight_t* weightArray;
		int numverts;
		int numtris;
		int numweights;
	};

	class MD5Modle
	{
	public:
		MD5Modle();
		~MD5Modle();

		bool init(const char* filename1, const char* filename2);
		void shutDown();
		void update(float dt);
		void render();

		inline Matrix4* getSkinnedMatrices() { return m_SkinnedMatrices; }
	private:

		// ����MD5 mesh
		bool loadMesh(const char* filename);
		void shutDownMesh();
		
		// ����MD5 ����
		bool loadAnimation(const char* filename);
		void shutDownAnimation();

		// ���� inverse bind pose
		void buildInvBindPose();
		
		// ����mesh�Ķ�������
		void computeVertexPositionFromWeight(md5_mesh_t* md5mesh, ogl_mesh_t* finalmesh);
		bool PrepareMeshes();
		
	private:
		bool initBuffers();
		void shutDownBuffers();

		bool initTextures();
		void shutDownTextures();

	private:
		int m_MD5Version;				 // MD5�汾�� 
		int m_NumJionts;				 // �ؽ�����
		int m_NumMeshes;				 // mesh����

		md5_joint_t* m_JointArray;       // ��ȡ�Ĺؽ�����
		md5_mesh_t*  m_MeshArray;        // ��ȡ��MD5 mesh����
		ogl_mesh_t*  m_FinalMeshArray;   // ����opengl mesh����

		Matrix4* m_InvBindPose;
		Matrix4* m_SkinnedMatrices;
		MD5Animation* m_Anim;

		unsigned int* m_VertexArrayIds;   // ��������
		unsigned int* m_VertexBufferIds;  // ���㻺��
		unsigned int* m_IndexBufferIds;   // ��������
		unsigned int* m_NumIndices;       // ��������

		Texture** m_Textures;			  // ��������
	};
}