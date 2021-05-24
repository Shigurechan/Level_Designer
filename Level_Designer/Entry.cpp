#include "Entry.hpp"
#include "Title.hpp"
#include "Editor.hpp"

//�R���X�g���N�^
Entry::Entry(std::shared_ptr<FrameWork::Window> w) : Scene(w,Sequence::Invalid)
{
	moveScene = Sequence::Title;
	title = nullptr;
	editor = nullptr;
	

}

//�X�V
void Entry::Update()
{

}

//�����_�����O
void Entry::Renderer()
{


}

//���[�v
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
	


	//�V�[�����ڔ���
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


//�f�X�g���N�^
Entry::~Entry()
{

}
