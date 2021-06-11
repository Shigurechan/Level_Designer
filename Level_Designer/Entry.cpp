#include "Entry.hpp"
#include "Title.hpp"
#include "Editor.hpp"

//�R���X�g���N�^
Entry::Entry(std::shared_ptr<FrameWork::Window> w) : Scene(w,Sequence::Invalid)
{
	moveScene = Sequence::Title;	//�����V�[��
	title = nullptr;
	editor = nullptr;
}

//�X�V
void Entry::Update()
{

}

//�����_�����O
void Entry::Renderer()const
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
	
	//�V�[������
	switch (moveScene)
	{
		//�^�C�g��
		case Sequence::Title:
		{			
			if (title == nullptr)
			{
				editor = nullptr;
				title = std::make_unique<Title>(windowContext);
			}
		}
		break;

		//�G�f�B�^�[
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


//�f�X�g���N�^
Entry::~Entry()
{

}
