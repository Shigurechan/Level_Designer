#ifndef ___SCENE_HPP_
#define ___SCENE_HPP_
#include <iostream>
#include "Sequence.hpp"
#include "FrameWork.hpp"

#define CELL (48)

class Scene
{
public:

	Scene(std::shared_ptr<FrameWork::Window> w,Sequence e);	//�R���X�g���N�^
	~Scene();												//�f�X�g���N�^

	virtual void Update() = 0;			//�X�V
	virtual void Renderer()const = 0;	//�`��

protected:

	std::shared_ptr<FrameWork::Window> windowContext;	//�E�C���h�E�R���e�L�X�g
	Sequence moveScene;	//�V�[������
};
#endif