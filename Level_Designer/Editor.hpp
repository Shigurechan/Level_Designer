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
	void Renderer()const;	//�����_�����O
	void Loop(Entry* e);	//���[�v


private:
	
	//�^�C���̎��
	enum class TileType
	{
		None = 0xFF,
	};

	
	bool isNewFile;	//�V�����t�@�C���Ȃ̂��t�@�C���ҏW�Ȃ̂��𔻒�

	//�`��ϐ�
	std::shared_ptr<FrameWork::Line> line;				//�g�g�݂�`��
	std::shared_ptr<FrameWork::Rectangle> rectCursor;	//�J�[�\����`��
	std::shared_ptr<FrameWork::Rectangle> rectMenu;	//���j���[�͈͂�`��

	std::shared_ptr<FrameWork::Sprite> sprite;			//�X�v���C�g��`��


	typedef struct sprite_data
	{
		glm::vec2 startSize;
		glm::vec2 endSize;
	}SpriteData;

	std::shared_ptr<std::vector<SpriteData>> tileData;	//�^�C�����X�g
	std::shared_ptr<std::vector<byte>> stageData;		//�G�f�B�b�g����X�e�[�W

	glm::vec2 mousePosition;				//�}�E�X���W

	
	int selectTile = 0;	//�I������^�C��

	bool holdRight = false;	//����������
	bool holdLeft = false;	//����������
	int keyRight = 0;	//���͎���
	int keyLeft = 0;	//���͎���



};


#endif
