#include "Scene.hpp"


//�R���X�g���N�^
Scene::Scene(std::shared_ptr<FrameWork::Window> w,Sequence e)
{
	moveScene = e;		//�����̃V�[��
	windowContext = w;	//�E�C���h�E�R���e�L�X�g
}
	

//�f�X�g���N�^
Scene::~Scene()
{

}

