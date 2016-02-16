#include "MD5Model.h"
#include "helper.h"

namespace apanoo {

	MD5Modle::MD5Modle()
	{
		m_JointArray = NULL;
		m_MeshArray = NULL;
		m_FinalMeshArray = NULL;

		m_InvBindPose = NULL;
		m_SkinnedMatrices = NULL;

		m_VertexArrayIds = NULL;
		m_VertexBufferIds = NULL;
		m_IndexBufferIds = NULL;
		m_NumIndices = NULL;
	}

	MD5Modle::~MD5Modle()
	{

	}

	bool MD5Modle::init(const char* filename1, const char* filename2)
	{
		if (!loadMesh(filename1))
		{
			return false;
		}
		if (!PrepareMeshes())
		{
			return false;
		}

		if (!loadAnimation(filename2))
		{
		}
		if (!initBuffers())
		{
			return false;
		}
		if (!initTextures())
		{
			return false;
		}
		return true;
	}

	void MD5Modle::shutDown()
	{
		shutDownBuffers();
		shutDownTextures();
		shutDownAnimation();
	}

	void MD5Modle::update(float dt)
	{
		m_Anim->update(dt);
		Matrix4* pAnimationMatrix = m_Anim->getAnimationMatrix();
		for (int i = 0;i < m_NumJionts;i++)
		{
			m_SkinnedMatrices[i] = pAnimationMatrix[i] * m_InvBindPose[i];
		}
	}

	void MD5Modle::render()
	{
		for (int i = 0;i < m_NumMeshes;i++)
		{
			glBindVertexArray(m_VertexArrayIds[i]);

			m_Textures[i]->bind(GL_TEXTURE_2D);
			glDrawElements(GL_TRIANGLES, m_NumIndices[i], GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
	}

	bool MD5Modle::loadMesh(const char* filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			// to : log to file
			std::cout << "failed to load md5 mesh" << std::endl;
			return false;
		}

		// 计算文件长度
		int initpos = (int)file.tellg();
		file.seekg(0, std::ios::end);
		int filelength = (int)file.tellg();   
		file.seekg(initpos);

		int imesh = 0;
		std::string param, junk;
		file >> param;

		while (!file.eof())
		{
			if (param == "MD5Version")
			{
				file >> m_MD5Version;
				if (m_MD5Version != 10)   // 只处理version = 10 的MD5文件
				{
					return false;
				}
				std::cout << "MD5Version: " << m_MD5Version << std::endl;
			} else if (param == "commandline")
			{
				file.ignore(filelength, '\n');
			} else if (param == "numJoints")  // 关节数量
			{
				file >> m_NumJionts;
				m_JointArray = new md5_joint_t[m_NumJionts]; 
				if (!m_JointArray)
				{
					return false;
				}
				m_InvBindPose = new Matrix4[m_NumJionts];
				if (!m_InvBindPose)
				{
					return false;
				}

				m_SkinnedMatrices = new Matrix4[m_NumJionts];
				if (!m_SkinnedMatrices)
				{
					return false;
				}
			} else if (param == "numMeshes")   // mesh数量
			{
				file >> m_NumMeshes;
				m_MeshArray = new md5_mesh_t[m_NumMeshes];
				if (!m_MeshArray)
				{
					return false;
				}

				m_FinalMeshArray = new ogl_mesh_t[m_NumMeshes];
				if (!m_FinalMeshArray)
				{
					return false;
				}
			} else if (param == "joints")   // 读取关节信息
			{
				file >> junk; // {
				for (int i = 0;i < m_NumJionts; i++)
				{
					md5_joint_t joint;
					Vector3 tmp_orientation;
					file >> joint.name >> joint.parentID >> junk; // (
					file >> joint.position[0] >> joint.position[1] >> joint.position[2];
					file >> junk >> junk; // )(
					file >> tmp_orientation[0] >> tmp_orientation[1] >> tmp_orientation[2];
					file >> junk; // )
					file.ignore(filelength, '\n');

					removeQuotes(joint.name);  // 去除name中的双引号

					// 计算完整的四元数
					joint.orientation = Quaternion(tmp_orientation[0], tmp_orientation[1], tmp_orientation[2], computeQuaternionW(tmp_orientation));

					m_JointArray[i] = joint;
				}
				file >> junk; // }
				buildInvBindPose();

			} else if (param == "mesh")
			{
				file >> junk;  // {
				md5_mesh_t mesh;

				file >> param;
				while (param != "}")
				{
					if (param == "shader") // 纹理全路径
					{
						file >> mesh.shader;
						removeQuotes(mesh.shader);
					} else if (param == "numverts") 
					{
						file >> mesh.numverts;
						mesh.vertexArray = new md5_vertex_t[mesh.numverts];
						if (!mesh.vertexArray)
						{
							return false;
						}
						for (int i = 0;i < mesh.numverts; i++) // 解析顶点
						{
							md5_vertex_t vert;
							file >> junk >> junk >> junk; // vert vertIdx (
							file >> vert.texCoord[0] >> vert.texCoord[1] >> junk; // )
							file >> vert.startWeight >> vert.numWeights;

							mesh.vertexArray[i] = vert;
						}
					} else if (param == "numtris") 
					{
						file >> mesh.numtris;
						mesh.triangleArray = new md5_triangle_t[mesh.numtris];
						if (!mesh.triangleArray)
						{
							return false;
						}

						for (int i = 0;i < mesh.numtris; i++) // 解析三角形数据
						{
							md5_triangle_t tri;
							file >> junk >> junk; // tri triIdx
							file >> tri.indices[0] >> tri.indices[1] >> tri.indices[2];

							mesh.triangleArray[i] = tri;
						}
					} else if (param == "numweights")
					{
						file >> mesh.numweights;
						mesh.weightArray = new md5_weight_t[mesh.numweights];
						if (!mesh.weightArray)
						{
							return false;
						}
						for (int i = 0; i < mesh.numweights; i++)  // 解析权重数组
						{
							md5_weight_t weight;
							file >> junk >> junk; // weight weightIdx
							file >> weight.jointID >> weight.bias >> junk; // (
							file >> weight.position[0] >> weight.position[1] >> weight.position[2];
							file >> junk; // )

							mesh.weightArray[i] = weight;
						}
					}
					else
					{
						file.ignore(filelength, '\n');
					}
					file >> param;
				}

				m_MeshArray[imesh] = mesh;  // 第imesh张mesh
				imesh++;
			}

			file >> param;
		}

		// 解析成功
		return true;
	}

	void MD5Modle::shutDownMesh()
	{
		if (m_JointArray)
		{
			delete[] m_JointArray;
			m_JointArray = NULL;
		}
		if (m_MeshArray)
		{
			for (int i = 0;i < m_NumMeshes; i++)
			{
				delete[] m_MeshArray[i].vertexArray;
				delete[] m_MeshArray[i].triangleArray;
				delete[] m_MeshArray[i].weightArray;

				m_MeshArray[i].vertexArray = NULL;
				m_MeshArray[i].triangleArray = NULL;
				m_MeshArray[i].weightArray = NULL;
			}
			delete[] m_MeshArray;
			m_MeshArray = NULL;
		}
		if (m_FinalMeshArray)
		{
			for (int i = 0;i < m_NumMeshes; i++)
			{
				delete[] m_FinalMeshArray[i].vertexArray;
				delete[] m_FinalMeshArray[i].indexArray;

				m_FinalMeshArray[i].vertexArray = NULL;
				m_FinalMeshArray[i].indexArray = NULL;
			}
			delete[] m_FinalMeshArray;
			m_FinalMeshArray = NULL;
		}
	}

	bool MD5Modle::loadAnimation(const char* filename)
	{
		m_Anim = new MD5Animation();
		if (!m_Anim)
		{
			return false;
		}

		if (!m_Anim->init(filename))
		{
			return false;
		}

		return true;
	}

	void MD5Modle::shutDownAnimation()
	{
		if (m_Anim)
		{
			m_Anim->shutDown();
			delete m_Anim;
			m_Anim = NULL;
		}
		if (m_SkinnedMatrices)
		{
			delete[] m_SkinnedMatrices;
			m_SkinnedMatrices = NULL;
		}
		if (m_InvBindPose)
		{
			delete[] m_InvBindPose;
			m_InvBindPose = NULL;
		}
	}

	void MD5Modle::buildInvBindPose()
	{
		Matrix4 rotation, rotationInv, translationInv, finalmatrix;
		for (int i = 0;i < m_NumJionts;i++)
		{
			md5_joint_t& joint = m_JointArray[i];
			rotation = Matrix4(joint.orientation);
			rotationInv = rotation.transpose();
			translationInv = Matrix4().translationMatrix(Vector3(-joint.position[0], -joint.position[0], -joint.position[0]));
			finalmatrix = rotationInv * translationInv;

			memcpy(&m_InvBindPose[i], &finalmatrix, sizeof(Matrix4));
		}
	}

	void MD5Modle::computeVertexPositionFromWeight(md5_mesh_t* md5mesh, ogl_mesh_t* finalmesh)
	{
		for (int i = 0;i < md5mesh->numverts;i++)
		{
			md5_vertex_t& vert = md5mesh->vertexArray[i];
			ogl_vertex_t& finalvert = finalmesh->vertexArray[i];
			memset(&finalvert.position, 0, sizeof(Vector3));
			memset(&finalvert.texCoord, 0, sizeof(Vector2));
			memset(&finalvert.weight, 0, sizeof(Vector4));
			memset(&finalvert.indices, 0, sizeof(Vector4));

			for (int j = 0;j < vert.numWeights;j++)
			{
				if (j == 4)
				{
					break;
				}
				md5_weight_t& weight = md5mesh->weightArray[vert.startWeight + j];
				md5_joint_t& joint = m_JointArray[weight.jointID];

				Vector3 rotpos = weight.position.rotate(joint.orientation);
				finalvert.position[0] += (joint.position[0] + rotpos[0]) * weight.bias;
				finalvert.position[1] += (joint.position[1] + rotpos[1]) * weight.bias;
				finalvert.position[2] += (joint.position[2] + rotpos[2]) * weight.bias;

				finalvert.indices[j] = (float)weight.jointID;
				finalvert.weight[j] = weight.bias;
			}
		}
	}

	bool MD5Modle::PrepareMeshes()
	{
		for (int i = 0;i < m_NumMeshes;i++)
		{
			md5_mesh_t& mesh = m_MeshArray[i];
			ogl_mesh_t& finalmesh = m_FinalMeshArray[i];

			finalmesh.texture = mesh.shader;
			finalmesh.numVertices = mesh.numverts;
			finalmesh.numIndices = mesh.numtris * 3;

			finalmesh.vertexArray = new ogl_vertex_t[finalmesh.numVertices];
			if (!finalmesh.vertexArray)
			{
				return false;
			}

			finalmesh.indexArray = new unsigned int[finalmesh.numIndices];
			if (!finalmesh.indexArray)
			{
				return false;
			}

			computeVertexPositionFromWeight(&mesh, &finalmesh);

			for (int j = 0;j < mesh.numtris;j++)
			{
				finalmesh.indexArray[j * 3 + 0] = mesh.triangleArray[j].indices[0];
				finalmesh.indexArray[j * 3 + 1] = mesh.triangleArray[j].indices[1];
				finalmesh.indexArray[j * 3 + 2] = mesh.triangleArray[j].indices[2];
			}
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool MD5Modle::initBuffers()
	{
		m_VertexArrayIds = new unsigned int[m_NumMeshes];
		if (!m_VertexArrayIds)
		{
			return false;
		}

		m_VertexBufferIds = new unsigned int[m_NumMeshes];
		if (!m_VertexBufferIds)
		{
			return false;
		}

		m_IndexBufferIds = new unsigned int[m_NumMeshes];
		if (!m_IndexBufferIds)
		{
			return false;
		}

		m_NumIndices = new unsigned int[m_NumMeshes];
		if (!m_NumIndices)
		{
			return false;
		}

		glGenVertexArrays(m_NumMeshes, m_VertexArrayIds);
		glGenBuffers(m_NumMeshes, m_VertexBufferIds);
		glGenBuffers(m_NumMeshes, m_IndexBufferIds);

		for (int i = 0;i < m_NumMeshes;i++)
		{
			m_NumIndices[i] = m_FinalMeshArray[i].numIndices;
			glBindVertexArray(m_VertexArrayIds[i]);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferIds[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(ogl_vertex_t) * m_FinalMeshArray[i].numVertices,
				m_FinalMeshArray[i].vertexArray, GL_STATIC_DRAW);
			
			// 偏移
			size_t textureOffset = sizeof(Vector3);
			size_t indicesOffset = sizeof(Vector2) + textureOffset;
			size_t weightOffset = sizeof(Vector4) + indicesOffset;

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(ogl_vertex_t), (void*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(ogl_vertex_t), (void*)textureOffset);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(ogl_vertex_t), (void*)indicesOffset);
			glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(ogl_vertex_t), (void*)weightOffset);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferIds[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_FinalMeshArray[i].numIndices,
				m_FinalMeshArray[i].indexArray, GL_STATIC_DRAW);

			glBindVertexArray(0);
		}
		return true;
	}

	void MD5Modle::shutDownBuffers()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(m_NumMeshes, m_IndexBufferIds);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(m_NumMeshes, m_VertexBufferIds);

		glBindVertexArray(0);
		glDeleteVertexArrays(m_NumMeshes, m_VertexArrayIds);

		if (m_VertexArrayIds)
		{
			delete[] m_VertexArrayIds;
			m_VertexArrayIds = NULL;
		}
		if (m_VertexBufferIds)
		{
			delete[] m_VertexBufferIds;
			m_VertexBufferIds = NULL;
		}
		if (m_IndexBufferIds)
		{
			delete[] m_IndexBufferIds;
			m_IndexBufferIds = NULL;
		}
	}

	bool MD5Modle::initTextures()
	{
		m_Textures = new Texture*[m_NumMeshes];
		if (!m_Textures)
		{
			return false;
		}

		for (int i = 0;i < m_NumMeshes;i++)
		{
			m_Textures[i] = new Texture(GL_TEXTURE_2D, m_FinalMeshArray[i].texture);
			if (m_Textures[i])
			{
				return false;
			}
		}
		return true;
	}

	void MD5Modle::shutDownTextures()
	{
		if (m_Textures)
		{
			for (int i = 0;i < m_NumMeshes;i++)
			{
				delete[] m_Textures[i];
				m_Textures[i] = NULL;
			}
			delete[] m_Textures;
			m_Textures = NULL;
		}
	}
}