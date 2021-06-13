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
	~Title();										//�f�X�g���N�^

	void Update();				//�X�V
	void Renderer()const;		//�����_�����O
	void Loop(Entry* e);		//���[�v

private:

	std::shared_ptr<FrameWork::Text> text;	//�����`��	
	std::string str;						//�h���b�N���h���b�v�p�X
};
#endif
