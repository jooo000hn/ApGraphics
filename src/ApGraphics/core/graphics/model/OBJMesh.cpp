#include "OBJMesh.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "../../../utils/StringUtils.h"
#include "../../../log/Log.h"

namespace apanoo {
	OBJMesh::OBJMesh(const char* filename)
		: Mesh()
	{
		if ("obj" == splitString(filename, '.').back())
		{
			loadOBJ(filename);
		}
		else {
			std::cout << "Modele read error : this fileformat is not support" << std::endl;
		}
	}

	OBJMesh::~OBJMesh()
	{

	}

	void OBJMesh::loadOBJ(const char* filename)
	{
		std::ifstream in;
		std::string line, word, goname, mtlname;
		int row, col;

		std::vector<Vertex> vector_vertexs;
		std::vector<int> vector_indices;

		in.open(filename);
		if (!in)
		{
			std::cout << "Read obj error !" << std::endl;
			Log::Instance()->OutputError("Read obj error !");
			return;
		}
		while (getline(in, line))
		{
			if (line.size() == 0 || line[0] == '#') continue;
			std::istringstream is(line);
			is >> word;
			if (word == "v") // 读取顶点
			{
				float tmpx, tmpy, tmpz;
				is >> tmpx >> tmpy >> tmpz;
				Vertex p(tmpx, tmpy,tmpz);
				vector_vertexs.push_back(p);
			}
			else if (word == "f") // 读取面
			{
				int r = 0, c = 0;
				while (is >> word)
				{
					c = count(word.begin(), word.end(), '/');
					if (c == 2)
					{
						int a = word.find("/");
						int b = word.find("/", a + 1);
						vector_indices.push_back(atoi(std::string(word.begin(), word.begin() + a).c_str()));
					}
					++ r;
				}
				row = r;
				col = c + 1;
			}
		}
		in.close();

		// 储存点
		int vertCount = vector_vertexs.size();
		Vertex** vertives = new Vertex*[vertCount];
		for (unsigned int i = 0;i < vector_vertexs.size();i++)
		{
			vertives[i] = &vector_vertexs.at(i);
		}

		// 储存面的顶点索引
		int indexCount = vector_indices.size();
		int* indices = new int[indexCount];
		for (int i = 0;i < indexCount;i++)
		{
			indices[i] = vector_indices.at(i) - 1;
		}
		
		addVertices(*vertives, vertCount, indices, indexCount);

		delete[] vertives;
		delete[] indices;
	}
}