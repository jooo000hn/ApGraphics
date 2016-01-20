#include "../ApGraphics/apgraphics.h"

using namespace apanoo;
class Game : public ApGraphics
{
public:
	Game()
	{
		tme = 0;
		obj = nullptr;
		shader = nullptr;
	}

	~Game()
	{

	}

	void init() override
	{
		m_Window = createWindow("ApGraphics", 960, 540);
		shader = new Shader();
		shader->addVertexShader("basic.vert");
		shader->addFragmentShader("basic.frag");
		shader->enable();

		Camera camera;
		trans = new Transform();
		trans->setProjection(60.0f, (float)m_Window->getWidth(), (float)m_Window->getHeight(), 0.001f, 10000.0f);
		trans->setCamera(camera);

		trans->setTranslation(0, 0, 1.0);
		trans->setScale(0.5, 0.5, 0.5);

		obj = new OBJ("box.obj");
	}

	void render() override
	{
		tme += 0.05f;
		trans->setRotation(0, tme, 0);
		shader->setUniformMat4("transform", trans->getProjectionTransformation());
		obj->draw();
	}

	void tick() override
	{
		std::cout << this->getUPS() << std::endl;
	}

	void update() override
	{
		auto camera2 = trans->getCamera();
		if (m_Window->isKeyPressed(GLFW_KEY_W))
		{
			camera2->move(camera2->getForward(), 0.02);
			std::cout << camera2->getPosition() << std::endl;
		}
		if (m_Window->isKeyPressed(GLFW_KEY_S))
		{
			camera2->move(camera2->getForward(), -0.02);
			std::cout << camera2->getPosition() << std::endl;
		}
		if (m_Window->isKeyPressed(GLFW_KEY_A))
		{
			camera2->move(camera2->getLeft(), 0.02);
			std::cout << camera2->getPosition() << std::endl;
		}
		if (m_Window->isKeyPressed(GLFW_KEY_D))
		{
			camera2->move(camera2->getRight(), 0.02);
			std::cout << camera2->getPosition() << std::endl;
		}

		//////////////////////////////////////////////////////////////////////////
		if (m_Window->isKeyPressed(GLFW_KEY_UP))
		{
			camera2->rotateX(-0.2);
			std::cout << camera2->getForward() << std::endl;
		}
		if (m_Window->isKeyPressed(GLFW_KEY_DOWN))
		{
			camera2->rotateX(0.2);
			std::cout << camera2->getForward() << std::endl;
		}
		if (m_Window->isKeyPressed(GLFW_KEY_LEFT))
		{
			camera2->rotateY(-0.2);
			std::cout << camera2->getForward() << std::endl;
		}
		if (m_Window->isKeyPressed(GLFW_KEY_RIGHT))
		{
			camera2->rotateY(0.2);
			std::cout << camera2->getForward() << std::endl;
		}
	}
private:
	Window* m_Window;
	OBJ* obj;
	float tme;
	Shader* shader;
	Transform * trans;
};

int main() 
{
	Game game;
	game.start();
	return 0;
}