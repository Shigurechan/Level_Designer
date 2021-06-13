#ifndef ___EDITOR_HPP_
#define ___EDITOR_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

#define byte unsigned char //1byte

//�X�e�[�W�T�C�Y
#define STAGE_SIZE_WIDTH 26
#define STAGE_SIZE_HEIGHT 17
#define STAGE_SIZE (STAGE_SIZE_WIDTH * STAGE_SIZE_HEIGHT)

//�X�v���C�g�ԍ�
#define BACKGROUND_TEX_NUM 0
#define ITEM_TEX_NUM 1
#define ENEMY_TEX_NUM 2

#define KEY_HOLD 30	//�������t���[����

class Entry;

class Editor : public Scene
{
public:

	Editor(std::shared_ptr<FrameWork::Window> w, std::string path);		//�R���X�g���N�^
	~Editor();															//�f�X�g���N�^

	void Update();			//�X�V
	void Renderer()const;	//�����_�����O
	void Loop(Entry* e);	//���[�v

private:
	
	void KeyControl();	//����
	void SaveFile();	//�Z�[�u

	//�^�C���̎��
	enum class TileType
	{
		None = 0xFF,
	};
	
	bool isNewFile;	//�V�����t�@�C���Ȃ̂��t�@�C���ҏW�Ȃ̂��𔻒�

	//�`��ϐ�
	std::shared_ptr<FrameWork::Line> line;				//�g�g�݂�`��
	std::shared_ptr<FrameWork::Rectangle> rectCursor;	//�J�[�\����`��
	std::shared_ptr<FrameWork::Rectangle> rectMenu;		//���j���[�͈͂�`��
	std::shared_ptr<FrameWork::Sprite> sprite;			//�X�v���C�g��`��

	//�X�v���C�g�`��͈͍\����
	typedef struct sprite_data
	{
		glm::vec2 startSize;
		glm::vec2 endSize;
		int texNum;
	}SpriteData;

	std::shared_ptr<std::vector<SpriteData>> tileData;	//�^�C�����X�g

	//�G�f�B�b�g����X�e�[�W
	std::shared_ptr< std::vector<byte> > stageData;			//�X�e�[�W
	std::shared_ptr< std::vector<byte> > stageDataObject;	//�}�b�v�I�u�W�F�N�g

	glm::vec2 mousePosition;	//�}�E�X���W
	char fileName[1000];		//�t�@�C����

	int selectTile = 0;			//�I������^�C��
	int backGroundTextureNum;	//�o�b�N�O�����h�̃X�v���C�g

	bool holdRight = false;	//����������
	bool holdLeft = false;	//����������
	int keyRight = 0;		//���͎���
	int keyLeft = 0;		//���͎���

	FrameWork::Animation anim;					//�ۑ��A�j���[�V����
	bool isSave;								//�ۑ��L�[�����������ǂ����H
	std::shared_ptr<FrameWork::Text> saveText;	//�Z�[�u������\��
};
#endif