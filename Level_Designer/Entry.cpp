#include "Entry.hpp"
#include "Title.hpp"
#include "Editor.hpp"

//コンストラクタ
Entry::Entry(std::shared_ptr<FrameWork::Window> w) : Scene(w,Sequence::Invalid)
{
	moveScene = Sequence::Title;	//初期シーン
	title = nullptr;
	editor = nullptr;
}

//更新
void Entry::Update()
{

}

//レンダリング
void Entry::Renderer()const
{

}

//ループ
void Entry::Loop()
{
	if (title)
	{
		title->Loop(this);
	}
	else if (editor)
	{		
		editor->Loop(this);
	}
	
	//シーン推移
	switch (moveScene)
	{
		//タイトル
		case Sequence::Title:
		{			
			if (title == nullptr)
			{
				editor = nullptr;
				title = std::make_unique<Title>(windowContext);
			}
		}
		break;

		//エディター
		case Sequence::Editor:
		{
			if (editor == nullptr) 
			{
				title = nullptr;
				editor = std::make_unique<Editor>(windowContext,drapPath);
			}
		}
		break;
	}
}



void Entry::MoveTo(Sequence e)
{
	moveScene = e;
}


//デストラクタ
Entry::~Entry()
{

}
