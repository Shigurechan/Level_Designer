#include "Editor.hpp"
#include "Scene.hpp"
#include <FrameWork.hpp>


//�R���X�g���N�^
Editor::Editor(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Editor)
{
	

}


//�X�V
void Editor::Update()
{







}

//�����_�����O
void Editor::Renderer()
{

}

//���[�v
void Editor::Loop(Entry* e)
{
	Update();
	Renderer();
}

//�f�X�g���N�^
Editor::~Editor()
{

}
