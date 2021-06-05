#include "Title.hpp"
#include "Scene.hpp"
#include "Entry.hpp"

//�R���X�g���N�^
Title::Title(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Title)	
{
	newFileText = std::make_shared<FrameWork::Text>(windowContext);
	editFileText = std::make_shared<FrameWork::Text>(windowContext);
	


	select = 0;
	position = glm::vec2(0,0);
}



std::vector<char> chr(0);

//�X�V
void Title::Update()
{
	

	//�ҏW
	str = windowContext->getDropPath();
	if (str != "")
	{

		moveScene = Sequence::Editor;
	}


	//�V�K�쐬
	if (windowContext->getKeyInput(GLFW_KEY_ENTER) == 1)
	{
		moveScene = Sequence::Editor;
	}



}

//�����_�����O
void Title::Renderer()const
{
	//��ʕ\��
	newFileText->Draw(glm::vec2(100, 100), 1.0f, glm::vec3(0, 255, 0), "New File: EnterKey ");
	editFileText->Draw(glm::vec2(150, 150),1.0f, glm::vec3(0, 255, 0),"Edit File: D&D ");



}


void Title::Loop(Entry *e)
{
	Update();
	Renderer();

	e->MoveTo(moveScene);
	e->drapPath = str;
}




Title::~Title()
{

}
