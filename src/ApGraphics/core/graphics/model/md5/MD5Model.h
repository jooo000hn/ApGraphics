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

	// ogl顶点
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

	// 顶点数据
	struct md5_vertex_t
	{
		Vector2 texCoord; // 纹理坐标
		int startWeight;  // 权重索引起始
		int numWeights;    // 权重数量
	};

	// 三角形信息
	struct md5_triangle_t
	{
		int indices[3];   // 三角形顶点索引
	};

	// 权重信息
	struct md5_weight_t
	{
		int jointID;      // 关节索引
		float bias;
		Vector3 position; 
		Vector4 orientation;
	};

	// 骨骼关节信息
	struct md5_joint_t
	{
		std::string name;
		int parentID;
		Vector3 position;
		Quaternion orientation;
	};

	// mesh信息
	struct md5_mesh_t
	{
		std::string shader;			// 纹理全路径
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

		// 加载MD5 mesh
		bool loadMesh(const char* filename);
		void shutDownMesh();
		
		// 加载MD5 动画
		bool loadAnimation(const char* filename);
		void shutDownAnimation();

		// 解析 inverse bind pose
		void buildInvBindPose();
		
		// 计算mesh的顶点数据
		void computeVertexPositionFromWeight(md5_mesh_t* md5mesh, ogl_mesh_t* finalmesh);
		bool PrepareMeshes();
		
	private:
		bool initBuffers();
		void shutDownBuffers();

		bool initTextures();
		void shutDownTextures();

	private:
		int m_MD5Version;				 // MD5版本号 
		int m_NumJionts;				 // 关节数量
		int m_NumMeshes;				 // mesh数量

		md5_joint_t* m_JointArray;       // 读取的关节数据
		md5_mesh_t*  m_MeshArray;        // 读取的MD5 mesh数据
		ogl_mesh_t*  m_FinalMeshArray;   // 最终opengl mesh数组

		Matrix4* m_InvBindPose;
		Matrix4* m_SkinnedMatrices;
		MD5Animation* m_Anim;

		unsigned int* m_VertexArrayIds;   // 顶点数组
		unsigned int* m_VertexBufferIds;  // 顶点缓存
		unsigned int* m_IndexBufferIds;   // 索引缓存
		unsigned int* m_NumIndices;       // 索引数量

		Texture** m_Textures;			  // 纹理数组
	};
}