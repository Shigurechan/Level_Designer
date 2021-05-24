#include "Editor.hpp"
#include "Scene.hpp"
#include <FrameWork.hpp>
#include <fstream>


//コンストラクタ
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
{
	//ファイル操作を指定
	if (path == "")
	{
		//新規ファイル作成

		isNewFile = true;

	}
	else {

		// ファイル編集


		isNewFile = false;

		std::ofstream file;
		file.open(path);

	}

	line = std::make_shared<FrameWork::Line>(windowContext);






}


//更新
void Editor::Update()
{
	






}

//レンダリング
void Editor::Renderer()
{






	//枠組み
	for (int x = 0; x < windowContext->getSize().x / CELL; x++)
	{
		line->Draw(glm::vec2(x * CELL,0), glm::vec2(x * CELL, windowContext->getSize().y),glm::vec4(0,255,0,255));
	}

	for (int y = 0; y < windowContext->getSize().y / CELL; y++)
	{
		line->Draw(glm::vec2(0, y * CELL), glm::vec2(windowContext->getSize().x, y * CELL ), glm::vec4(0, 255, 0, 255));
	}

}

//ループ
void Editor::Loop(Entry* e)
{
	Update();
	Renderer();
}

//デストラクタ
Editor::~Editor()
{

}
