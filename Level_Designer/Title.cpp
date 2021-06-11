#include "Title.hpp"
#include "Scene.hpp"
#include "Entry.hpp"

// ##################################### �R���X�g���N�^ ##################################### 
Title::Title(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Title)	
{
	text = std::make_shared<FrameWork::Text>(windowContext);	//�����`��	
}

// ##################################### �X�V ##################################### 
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

// ##################################### �`�� ##################################### 
void Title::Renderer()const
{
	//��ʕ\��
	text->Draw(glm::vec2(100, 100), 1.0f, glm::vec3(0, 255, 0), "New File: EnterKey ");
	text->Draw(glm::vec2(150, 150),1.0f, glm::vec3(0, 255, 0),"Edit File: D&D ");
}

// ##################################### ���[�v ##################################### 
void Title::Loop(Entry *e)
{
	Update();
	Renderer();

	e->MoveTo(moveScene);
	e->drapPath = str;	//D&D�p�X����
}

// ##################################### �f�X�g���N�^ ##################################### 
Title::~Title()
{

}
