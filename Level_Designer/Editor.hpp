#ifndef ___GAME_HPP_
#define ___GAME_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class Editor : public Scene
{
public:
	Editor(std::shared_ptr<FrameWork::Window> w);		//�R���X�g���N�^
	~Editor();	//�f�X�g���N�^

	void Update();			//�X�V
	void Renderer();		//�����_�����O
	void Loop(Entry* e);	//���[�v


private:

	
	





};


#endif
