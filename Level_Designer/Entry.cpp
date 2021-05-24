#include "Entry.hpp"
#include "Title.hpp"
#include "Editor.hpp"

//コンストラクタ
Entry::Entry(std::shared_ptr<FrameWork::Window> w) : Scene(w,Sequence::Invalid)
{
	moveScene = Sequence::Title;
	title = nullptr;
	editor = nullptr;
	

}

//更新
void Entry::Update()
{

}

//レンダリング
void Entry::Renderer()
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
	


	//シーン推移判定
	switch (moveScene)
	{

	case Sequence::Title:
		{
			
			if (title == nullptr)
			{
				title = new Title(windowContext);
			}
		}
		break;

	case Sequence::Editor:
		{
			delete title;
			title = nullptr;
			if (editor == nullptr) 
			{
				editor = new Editor(windowContext,drapPath);
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
