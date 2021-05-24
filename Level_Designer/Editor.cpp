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






	//�g�g��
	for (int x = 0; x < windowContext->getSize().x / CELL; x++)
	{
		line->Draw(glm::vec2(x * CELL,0), glm::vec2(x * CELL, windowContext->getSize().y),glm::vec4(0,255,0,255));
	}

	for (int y = 0; y < windowContext->getSize().y / CELL; y++)
	{
		line->Draw(glm::vec2(0, y * CELL), glm::vec2(windowContext->getSize().x, y * CELL ), glm::vec4(0, 255, 0, 255));
	}

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
