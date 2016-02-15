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
		testSkelton = nullptr;
	}

	~Game()
	{
		delete obj;
		delete testSkelton;
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
		shader = new Shader();
		shader->addVertexShader("../media/shaders/model.vert");
		shader->addFragmentShader("../media/shaders/model.frag");
		shader->enable();

		trans = new Transform();
		trans->setProjection(70.0f, (float)getWindow()->getWidth(), (float)getWindow()->getHeight(), 0.1f, 10000.0f);
		trans->setCamera(Vector3(53.9406f, 59.289f, -21.057f), Vector3(-0.814f, -0.38389f, 0.435217f), Vector3(-0.338936f, 0.923378f, 0.180262f));

		// test texture
		//texture = new Texture(GL_TEXTURE_2D, "../media/textures/test.png");
		
		//trans->setTranslation(0, 0, 0);
		//trans->setScale(0.3f, 0.3f, 0.3f);
		//trans->setRotation(-90, -90, 0);

		//obj = new OBJMesh("../media/models/box.obj");
		//asmesh = new ASMesh("../media/models/tank/tank.obj");
		testSkelton = new SkeltonMesh();
		testSkelton->LoadMesh("../media/models/bob/boblampclean.md5mesh");
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
		//trans->setRotation(0, tme, 0);
		shader->setUniformMat4("Transform", trans->getProjectionTransformation());

		//obj->render();
		//testMesh->render();
		//asmesh->render();

		std::vector<Matrix4> Transforms;
		float RunningTime = getTimer()->elapsed();
		testSkelton->BoneTransform(RunningTime, Transforms);
		for (unsigned int i = 0; i < Transforms.size(); i++) 
		{
			char Name[128];
			memset(Name, 0, sizeof(Name));
			sprintf_s(Name, sizeof(Name), "gBones[%d]", i);
			shader->setUniformMat4(Name, Transforms[i]);
		}
		testSkelton->Render();

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
		std::cout << this->getFPS() << std::endl;
	}
	
	void update() override
	{
		tme += 0.01f;
		if (m_RoundCamera)
		{
			trans->getCamera()->update(getWindow(), 0.002f, 0.8f);
		}
	}
private:
	OBJMesh* obj;
	//Mesh* testMesh;
	float tme;
	Shader* shader;
	Transform* trans;
	//Texture* texture;
	StaticMesh* asmesh;
	SkeltonMesh* testSkelton;

	bool m_BtnClicked;
	bool m_RoundCamera;

};

int main() 
{
	Game game;
	game.start();
	return 0;
}

