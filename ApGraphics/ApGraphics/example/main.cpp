#include <iostream>
#include "../core/window/Window.h"
#include "../core/graphics/Shader.h"
#include "../core/graphics/Mesh.h"
#include "../core/graphics/Vertex.h"
#include "../core/graphics/model/Obj.h"

int main()
{
	using namespace apanoo;

	Window window("ApGrapics3D", 960, 540);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//////////////////////////////////////////////////////////////////////////

	Shader* shader = new Shader();
	shader->addVertexShader("basic.vert");
	shader->addFragmentShader("basic.frag");
	shader->enable();
	shader->setUniformMat4("pr_matrix", Mat4::perspective(60.0, (float)window.getWidth() / (float)window.getHeight(), 0.1, 1000.0));

	int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	Mesh* mesh = new Mesh();
	Vertex data[] = {
		Vertex( -0.5f, -0.5f, -0.0f),
		Vertex(  0.5f, -0.5f, -0.0f),
		Vertex(  0.5f,  0.5f, -0.0f),
		Vertex( -0.5f,  0.5f, -0.0f),
	};

	OBJ* obj = new OBJ("box.obj");
	mesh->addVertices(data, 4, indices, 6);

	//////////////////////////////////////////////////////////////////////////
	float tme = 0.0;
	while (!window.closed())
	{
		window.clear();

		//mesh->draw();

		shader->enable();
		shader->setUniformMat4("ml_matrix", Mat4::translation(Vec3(0, 0, -5)) * Mat4::rotation(tme, Vec3(0, 1, 0)) * Mat4::rotation(tme * 0.2f, Vec3(1, 0, 0)));
		obj->draw();

		tme += 0.05f;
		
		window.update();
	}
	delete shader;
	delete mesh;
	return 0;
}