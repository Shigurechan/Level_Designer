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
