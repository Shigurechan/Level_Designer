#include "Editor.hpp"
#include "Scene.hpp"
#include <FrameWork.hpp>
#include <fstream>


//�R���X�g���N�^
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
{
	//�t�@�C��������w��
	if (path == "")
	{
		//�V�K�t�@�C���쐬

		isNewFile = true;

	}
	else {

		// �t�@�C���ҏW


		isNewFile = false;

		std::ofstream file;
		file.open(path);

	}

	line = std::make_shared<FrameWork::Line>(windowContext);






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
