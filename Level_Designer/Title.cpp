#include "Title.hpp"
#include "Scene.hpp"
#include "Entry.hpp"

// ##################################### コンストラクタ ##################################### 
Title::Title(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Title)	
{
	text = std::make_shared<FrameWork::Text>(windowContext);	//文字描画	
}

// ##################################### 更新 ##################################### 
void Title::Update()
{
	//編集
	str = windowContext->getDropPath();
	if (str != "")
	{
		moveScene = Sequence::Editor;
	}

	//新規作成
	if (windowContext->getKeyInput(GLFW_KEY_ENTER) == 1)
	{
		moveScene = Sequence::Editor;
	}
}

// ##################################### 描画 ##################################### 
void Title::Renderer()const
{
	//画面表示
	text->Draw(glm::vec2(100, 100), 1.0f, glm::vec3(0, 255, 0), "New File: EnterKey ");
	text->Draw(glm::vec2(150, 150),1.0f, glm::vec3(0, 255, 0),"Edit File: D&D ");
}

// ##################################### ループ ##################################### 
void Title::Loop(Entry *e)
{
	Update();
	Renderer();

	e->MoveTo(moveScene);
	e->drapPath = str;	//D&Dパスを代入
}

// ##################################### デストラクタ ##################################### 
Title::~Title()
{

}
