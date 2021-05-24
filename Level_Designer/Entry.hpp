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
	void Renderer();			//�����_�����O
	void Loop();				//���[�v


	void MoveTo(Sequence e);	//�V�[���؂�ւ�
	


	std::string drapPath;

private:

	
	//Sequence moveScene;	//�V�[���؂�ւ�

	//�e��V�[��
	Title* title;
	Editor* editor;
	GameOver* gameOver;




};


#endif

