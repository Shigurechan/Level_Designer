#include "Title.hpp"
#include "Scene.hpp"
#include "Entry.hpp"

//�R���X�g���N�^
Title::Title(std::shared_ptr<FrameWork::Window> w) : Scene(w, Sequence::Title)
	,newFileText(windowContext),
	editFileText(windowContext)
{
	select = 0;
}

//�X�V
void Title::Update()
{
	if (windowContext->getKeyInput(GLFW_KEY_SPACE) > 0)
	{
		moveScene = Sequence::Editor;
	}


	//std::cout<< windowContext->getKeyInput(GLFW_KEY_DOWN) << std::endl;

	if (windowContext->getKeyInput(GLFW_KEY_DOWN) == 1)
	{
	//	printf("������\n");
		select++;
		if (select > 1)
		{
			select = 1;
		}
	}
	else if (windowContext->getKeyInput(GLFW_KEY_UP) == 1)
	{
		select--;
		if (select < 0)
		{
			select = 0;
		}
	}
		
	switch (select)
	{
	case 0:
	{
		position = glm::vec2(100,100);
	}
	break;

	case 1:
	{
		position = glm::vec2(150, 150);

	}
	break;


	};




}

//�����_�����O
void Title::Renderer()
{
	//��ʕ\��
	newFileText.Draw(glm::vec2(100, 100), "New File", 1.0f, glm::vec3(0, 255, 0));
	editFileText.Draw(glm::vec2(150, 150), "Edit File", 1.0f, glm::vec3(0, 255, 0));

	FrameWork::Sprite sprite(windowContext);
	sprite.setTexture(FrameWork::LoadTexture("Assets/arrow.png"));
	sprite.DrawGraph(position,0,0,glm::vec2(0,0),glm::vec2(0,0),glm::vec2(48,48));



}


void Title::Loop(Entry *e)
{
	Update();
	Renderer();

	e->MoveTo(moveScene);
}




Title::~Title()
{

}
