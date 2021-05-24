#include "Title.hpp"
#include "Scene.hpp"
#include "Entry.hpp"

//�R���X�g���N�^
Title::Title(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Title)
	,newFileText(windowContext),
	editFileText(windowContext)
{
	select = 0;
	position = glm::vec2(0,0);
}

//�X�V
void Title::Update()
{
	str = windowContext->getDropPath();
	if (str != "")
	{
		moveScene = Sequence::Editor;
	}



	if (windowContext->getKeyInput(GLFW_KEY_ENTER) == 1)
	{
		moveScene = Sequence::Editor;
	}



}

//�����_�����O
void Title::Renderer()
{
	//��ʕ\��
	newFileText.Draw(glm::vec2(100, 100), "New File: EnterKey ", 1.0f, glm::vec3(0, 255, 0));
	//editFileText.Draw(glm::vec2(150, 150), "Edit File: D&D ", 1.0f, glm::vec3(0, 255, 0));



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
