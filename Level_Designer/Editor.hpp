#ifndef ___EDITOR_HPP_
#define ___EDITOR_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class Editor : public Scene
{
public:
	Editor(std::shared_ptr<FrameWork::Window> w, std::string path);		//�R���X�g���N�^
	~Editor();	//�f�X�g���N�^

	void Update();			//�X�V
	void Renderer();	//�����_�����O
	void Loop(Entry* e);	//���[�v


private:
	
	bool isNewFile;	//�V�����t�@�C���Ȃ̂��t�@�C���ҏW�Ȃ̂��𔻒�

	std::shared_ptr<FrameWork::Line> line;	//�g�g�݂�`��
	glm::vec2 mousePosition;				//�}�E�X���W

	

};


#endif
