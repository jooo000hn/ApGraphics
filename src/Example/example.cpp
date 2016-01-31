#include "../ApGraphics/apgraphics.h"
#include "../ApGraphics/core/graphics/Texture.h"

using namespace apanoo;
class Game : public ApGraphics
{
public:
	Game()
	{
		tme = 0;
		obj = nullptr;
		shader = nullptr;
		trans = nullptr;
		texture = nullptr;
	}

	~Game()
	{
		delete obj;
		//delete testMesh;
		delete shader;
		delete trans;
		delete texture;
	}
	
	void init() override
	{
		createWindow("ApGraphics", 960, 540);
		shader = new Shader();
		shader->addVertexShader("../media/shaders/basic.vert");
		shader->addFragmentShader("../media/shaders/basic.frag");
		shader->enable();

		trans = new Transform();
		trans->setProjection(70.0f, (float)getWindow()->getWidth(), (float)getWindow()->getHeight(), 0.1f, 10000.0f);
		trans->setCamera();

		// test texture
		texture = new Texture(GL_TEXTURE_2D, "../media/textures/test.png");

		trans->setTranslation(0, 0, 5);
		//trans->setScale(0.3f, 0.3f, 0.3f);
		//trans->setRotation(0, 0, 90);

		obj = new OBJMesh("../media/models/box.obj");
		/*testMesh = new Mesh();
		Vertex vert[] = {
			Vertex(0.0, 0.0, 0.0, 0.0, 0.0),
			Vertex(0.0, 1.0, 0.0, 0.0, 1.0),
			Vertex(1.0, 1.0, 0.0, 1.0, 1.0),
			Vertex(1.0, 0.0, 0.0, 1.0, 0.0)
		};
		int inde[] = {
			0, 1, 2,
			2, 3, 0
		};
		testMesh->addVertices(vert, 4, inde, 6);*/

		// 隐藏光标
		getWindow()->setCursorVisible(false);

		// 光标居中
		getWindow()->setCenterCursor();
	}

	void render() override
	{
		
		tme += 0.01f;
		trans->setRotation(0, tme, 0);
		shader->setUniformMat4("transform", trans->getProjectionTransformation());
		texture->bind(GL_TEXTURE0);
		obj->render();
		//testMesh->render();
	}

	void tick() override
	{
		std::cout << this->getFPS() << std::endl;
	}
	
	void update() override
	{
		trans->getCamera()->update(getWindow(), 0.002f, 0.08f);
	}
private:
	OBJMesh* obj;
	//Mesh* testMesh;
	float tme;
	Shader* shader;
	Transform* trans;
	Texture* texture;
};

int main() 
{
	Game game;
	game.start();
	return 0;
}