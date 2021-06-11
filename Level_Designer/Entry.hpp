#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_
#include <iostream>
#include "Scene.hpp"

#include <FrameWork.hpp>

class Title;
class Editor;
class GameOver;



class Entry : public Scene
{
	
public:

	Entry(std::shared_ptr<FrameWork::Window> w);		//�R���X�g���N�^
	~Entry();											//�f�X�g���N�^
	
	void Update();				//�X�V
	void Renderer()const;		//�����_�����O
	void Loop();				//���[�v

	void MoveTo(Sequence e);	//�V�[���؂�ւ�
	
	std::string drapPath;	//D��D�p�X

private:

	//�e��V�[��
	std::unique_ptr<Title> title;		//�^�C�g��
	std::unique_ptr<Editor> editor;		//�G�f�B�^�[
};


#endif

