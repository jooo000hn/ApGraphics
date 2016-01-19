// 只支持3角面
#include "Obj.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "../../../utils/StringUtils.h"
#include "../../../log/Log.h"

namespace apanoo {

	OBJ::OBJ(const char* filename)
		: Mesh()
	{
		if ("obj" == split_string(filename, '.').back())
		{
			loadOBJ(filename);
		}
		else {
			std::cout << "Modele read error : this fileformat is not support" << std::endl;
		}
	}

	OBJ::~OBJ()
	{

	}

	void OBJ::loadOBJ(const char* filename)
	{
		std::ifstream in;
		std::string line, word, goname, mtlname;
		int row, col;

		std::vector<Vertex> vector_vertexs;
		std::vector<int> vector_indices;

		std::string filepath = std::string("./Resources/objs/") + filename;
		in.open(filepath);
		if (!in)
		{
			std::cout << "Read obj error !" << std::endl;
			Log::Instance()->OutputError("Read obj error !");
			exit(0);
		}
		while (getline(in, line))
		{
			if (line.size() == 0 || line[0] == '#') continue;
			std::istringstream is(line);
			is >> word;
			if (word == "v")
			{
				float tmpx, tmpy, tmpz;
				is >> tmpx >> tmpy >> tmpz;
				Vertex p(tmpx, tmpy,tmpz);
				vector_vertexs.push_back(p);
			}
			else if (word == "f")
			{
				int r = 0, c = 0;
				while (is >> word)
				{
					c = count(word.begin(), word.end(), '/');
					if (c == 0)
					{
						vector_indices.push_back(atoi(word.c_str()));
					}
					else if (c == 1)
					{
						vector_indices.push_back(atoi(std::string(word.begin(), word.begin() + word.find("/")).c_str()));
						vector_indices.push_back(atoi(std::string(word.begin() + word.find("/") + 1, word.end()).c_str()));
					}
					else if (c == 2)
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

		int vertCount = vector_vertexs.size();
		Vertex** vertives = new Vertex*[vertCount];
		for (unsigned int i = 0;i < vector_vertexs.size();i++)
		{
			vertives[i] = &vector_vertexs.at(i);
		}

		int indexCount = vector_indices.size();
		int* indices = new int[indexCount];
		for (int i = 0;i < indexCount / 3;i++)
		{
			indices[  3*i  ] = vector_indices.at(3 * i) - 1;
			indices[3*i + 1] = vector_indices.at(3*i + 1) - 1;
			indices[3*i + 2] = vector_indices.at(3*i + 2) - 1;
			
			// std::cout << indices[3 * i] << " " << indices[3 * i + 1] << " " << indices[3 * i + 2] << std::endl;
		}
		
		addVertices(*vertives, vertCount, indices, indexCount);

		delete[] vertives;
		delete indices;
	}
}