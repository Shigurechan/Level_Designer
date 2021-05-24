#include "Editor.hpp"
#include "Scene.hpp"
#include <FrameWork.hpp>


//コンストラクタ
Editor::Editor(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Editor)
{
	

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
