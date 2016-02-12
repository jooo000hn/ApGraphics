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
		//texture = nullptr;
		m_BtnClicked = false;
		m_RoundCamera = false;
	}

	~Game()
	{
		delete obj;
		//delete testMesh;
		//delete shader;
		delete trans;
		//delete texture;
		delete asmesh;
	}
	
	void init() override
	{
		createWindow("ApGraphics", 960, 540);

		//shader = PhongShader::Instance();
		//PhongShader::Instance()->setBaseColor(Vector3(0, 1, 1));
		//PhongShader::Instance()->setAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
		shader = new ModelShader();
		shader->enable();

		trans = new Transform();
		trans->setProjection(70.0f, (float)getWindow()->getWidth(), (float)getWindow()->getHeight(), 0.1f, 10000.0f);
		trans->setCamera();

		// test texture
		//texture = new Texture(GL_TEXTURE_2D, "../media/textures/test.png");

		trans->setTranslation(0, 0, 50);
		//trans->setScale(0.3f, 0.3f, 0.3f);
		//trans->setRotation(0, 0, 90);

		//obj = new OBJMesh("../media/models/box.obj");
		asmesh = new ASMesh("../media/models/tank/tank.obj");
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
	}

	void render() override
	{
		
		tme += 0.01f;
		trans->setRotation(0, tme, 0);
		shader->updateUniforms(trans->getTransformation(), trans->getProjectionTransformation());
		//texture->bind(GL_TEXTURE0);
		//obj->render();
		//testMesh->render();
		asmesh->render();

		if (!m_BtnClicked && getWindow()->isMouseButtonClicked(GLFW_MOUSE_BUTTON_LEFT))
		{
			m_BtnClicked = true;
			// 隐藏光标
			getWindow()->setCursorVisible(false);

			// 光标居中
			getWindow()->setCenterCursor();
			m_RoundCamera = true;
		}
		if (getWindow()->isKeyTyped(GLFW_KEY_ESCAPE))
		{
			m_RoundCamera = false;
			// 显示光标
			getWindow()->setCursorVisible(true);
			m_BtnClicked = false;
		}
	}

	void tick() override
	{
		//std::cout << this->getFPS() << std::endl;
	}
	
	void update() override
	{
		if (m_RoundCamera)
		{
			trans->getCamera()->update(getWindow(), 0.002f, 0.08f);
		}
	}
private:
	OBJMesh* obj;
	//Mesh* testMesh;
	float tme;
	Shader* shader;
	Transform* trans;
	//Texture* texture;
	ASMesh* asmesh;

	bool m_BtnClicked;
	bool m_RoundCamera;

};

int main() 
{
	Game game;
	game.start();
	return 0;
}