#ifndef ___GAMEOVER_HPP_
#define ___GAMEOVER_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class GameOver : public Scene
{
public:
	GameOver(std::shared_ptr<FrameWork::Window> w);		//�R���X�g���N�^
	~GameOver();										//�f�X�g���N�^

	void Update();			//�X�V
	void Renderer();		//�����_�����O
	void Loop(Entry* e);	//���[�v

};


#endif
