#include "Title.hpp"
#include "Scene.hpp"
#include "Entry.hpp"

//コンストラクタ
Title::Title(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Title)	
{
	newFileText = std::make_shared<FrameWork::Text>(windowContext);
	editFileText = std::make_shared<FrameWork::Text>(windowContext);
	


	select = 0;
	position = glm::vec2(0,0);
}



std::vector<char> chr(0);

//更新
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

//レンダリング
void Title::Renderer()const
{
	//画面表示
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
