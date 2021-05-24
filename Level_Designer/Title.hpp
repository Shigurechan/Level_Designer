#ifndef TITLE_HPP_
#define TITLE_HPP_
#include <iostream>
#include "Scene.hpp"
#include <FrameWork.hpp>
class Entry;

class Title : public Scene
{
public:
	Title(std::shared_ptr<FrameWork::Window> w);	//�R���X�g���N�^
	~Title();	//�f�X�g���N�^

	void Update();				//�X�V
	void Renderer();			//�����_�����O
	void Loop(Entry* e);		//���[�v

private:

	//�^�C�g���\��
	FrameWork::Text newFileText;
	FrameWork::Text editFileText;

	int select;
	glm::vec2 position;
};



#endif
