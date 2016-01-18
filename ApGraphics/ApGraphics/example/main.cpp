#include <iostream>
#include "../core/window/Window.h"
#include "../core/graphics/Shader.h"
#include "../core/graphics/Mesh.h"
#include "../core/graphics/Vertex.h"

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
	// shader->setUniformMat4("pr_matrix", Mat4::orthographic(-16.0, 16.0, -9.0, 9.0, -1.0, 1.0));

	GLfloat vertices[] = 
	{
		-0.5, -0.5, 0.0,
		-0.5,  0.5, 0.0,
		 0.5,  0.5, 0.0,
		 0.5,  0.5, 0.0,
		 0.5, -0.5, 0.0,
		-0.5, -0.5, 0.0
	};

	Mesh* mesh = new Mesh();
	Vertex data[6] = {  Vertex(-0.5,  -0.5, 0.0),
						Vertex(-0.5,   0.5, 0.0),
						Vertex( 0.5,   0.5, 0.0),
						Vertex( 0.5,   0.5, 0.0),
						Vertex( 0.5,  -0.5, 0.0),
						Vertex(-0.5,  -0.5, 0.0) };
	auto a = sizeof(data);
	mesh->addVertices(data, 6);

	//////////////////////////////////////////////////////////////////////////

	while (!window.closed())
	{
		window.clear();

		mesh->draw();

		window.update();
	}
	delete shader;
	delete mesh;
	return 0;
}