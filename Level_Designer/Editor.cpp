#include "Editor.hpp"
#include "Scene.hpp"
#include "FrameWork.hpp"
#include <fstream>


//�R���X�g���N�^
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
,anim(w,5)	//�A�j���[�V����

{
	//�Z�[�u
	saveText = std::make_shared<FrameWork::Text>(w);
	isSave = false;	//�ۑ��L�[�����������ǂ����H


	stageData = std::make_shared<std::vector<byte>>(STAGE_SIZE, (int)TileType::None);
	stageDataObject = std::make_shared<std::vector<byte>>(STAGE_SIZE, (int)TileType::None);
	tileData = std::make_shared<std::vector<SpriteData>>();

	//�g�g��
	line = std::make_shared<FrameWork::Line>(windowContext);
	rectCursor = std::make_shared<FrameWork::Rectangle>(windowContext);
	rectMenu = std::make_shared<FrameWork::Rectangle>(windowContext);

	//�X�v���C�g
	sprite = std::make_shared<FrameWork::Sprite>(windowContext);
	sprite->setTexture(FrameWork::LoadTexture("Assets/backGround.png"));	//�w�i
	sprite->setTexture(FrameWork::LoadTexture("Assets/item.png"));			//�A�C�e��
	sprite->setTexture(FrameWork::LoadTexture("Assets/enemy.png"));			//�G�l�~�[



	//�t�@�C��������w��
	if (path == "")
	{
		//�V�K�t�@�C���쐬
		isNewFile = true;

		std::ofstream file;
		file.open("Stage/test.bin");
		file.close();


	}
	else {

		// �t�@�C���ҏW
		isNewFile = false;





		std::ofstream file;
		file.open(path);

	}

	

	// ================ �^�C������ݒ� ================ 

	//�w�i
	for (int y = 0; y < sprite->getTextureSize(BACKGROUND_TEX_NUM).y / CELL; y++)
	{
		for (int x = 0; x < sprite->getTextureSize(BACKGROUND_TEX_NUM).x / CELL; x++)
		{
			SpriteData s;	
			s.startSize = glm::vec2(x * CELL, y * CELL);
			s.endSize = glm::vec2((x + 1) * CELL, (y + 1) * CELL);
			s.texNum = BACKGROUND_TEX_NUM;
			tileData->push_back(s);	
		}
	}

	//�A�C�e��
	for (int y = 0; y < sprite->getTextureSize(ITEM_TEX_NUM).y / CELL; y++)
	{
		for (int x = 0; x < sprite->getTextureSize(ITEM_TEX_NUM).x / CELL; x++)
		{
			SpriteData s;
			s.startSize = glm::vec2(x * CELL, y * CELL);
			s.endSize = glm::vec2((x + 1) * CELL, (y + 1) * CELL);
			s.texNum = ITEM_TEX_NUM;
			tileData->push_back(s);
		}
	}

	//�G�l�~�[
	for (int y = 0; y < sprite->getTextureSize(ENEMY_TEX_NUM).y / CELL; y++)
	{
		for (int x = 0; x < sprite->getTextureSize(ENEMY_TEX_NUM).x / CELL; x++)
		{
			SpriteData s;
			s.startSize = glm::vec2(x * CELL, y * CELL);
			s.endSize = glm::vec2((x + 1) * CELL, (y + 1) * CELL);
			s.texNum = ENEMY_TEX_NUM;
			tileData->push_back(s);
		}
	}	
}

// ################################################### �X�V ################################################### 
void Editor::Update()
{
	//�}�E�X�J�[�\�����W
	mousePosition = windowContext->getMousePos();
	mousePosition.x = (int)mousePosition.x / (int)CELL;
	mousePosition.y = (int)mousePosition.y / (int)CELL;

	//�N���b�N�ŕ`��
	if (windowContext->getMouseButton(0) == true)
	{
		if (  (((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) < STAGE_SIZE )
		{

			if (selectTile < tileData->size())
			{
				if (tileData->at(selectTile).texNum == BACKGROUND_TEX_NUM)
				{
					//std::cout << "�X�e�[�W�`��" << std::endl;
					stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = selectTile;
				}
				else {
					stageDataObject->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = selectTile;
					//std::cout << "�I�u�W�F�N�g�`��" << std::endl;
				}



			}
			else 
			{
				
			}

			printf("binary: %x\n",selectTile);
			//std::cout << "binary: " << selectTile << std::endl;

		}
	}
	else if (windowContext->getMouseButton(1) == true)
	{
		//�E�N���b�N�ō폜

		//std::cout << "aaa" << std::endl;
		//�^�C���폜
		if(stageDataObject->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) != (int)TileType::None)
		{
			stageDataObject->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = (int)TileType::None;
		}
		else 
		{
			stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = (int)TileType::None;
		}
	}


	//�^�C���I�𑀍�
	keyRight = windowContext->getKeyInput(GLFW_KEY_RIGHT);
	keyLeft = windowContext->getKeyInput(GLFW_KEY_LEFT);
	
	if (keyRight > 0)
	{
		if (keyRight == 1)
		{
			selectTile++;
		}
		else if (keyRight > 30)
		{
			selectTile++;
		}
	}
	else if (keyLeft > 0)
	{
		if (keyLeft == 1)
		{
			selectTile--;
		}
		else if (keyLeft > 30)
		{
			selectTile--;
		}
	}

	if (selectTile < 0)
	{
		selectTile = 0;
	}
	else if (selectTile > tileData->size())
	{
		selectTile = tileData->max_size();
	}
	

	//�t�@�C���ɏ�������
	if (windowContext->getKeyInput(GLFW_KEY_S) == 1)
	{
		isSave = true;
		std::ofstream file;
		file.open("Stage/test.bin", std::ios::binary | std::ios::out);
		if (file.is_open() == true)
		{
			//�^�C��
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				const char c = stageData->at(i);
				file.write(&c, sizeof(unsigned char));
			}

			//�I�u�W�F�N�g
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				const char c = stageDataObject->at(i);
				file.write(&c, sizeof(unsigned char));
			}
		}
		




		file.close();
	}



	// ================ �Z�[�u ================ 
	if (isSave == true)
	{
		int n = 0;
		if (anim.getOnceClip(10, n) == false)
		{
			std::cout << "�ۑ�" << std::endl;
		}
		else {
			isSave = false;
			anim.ResetOnceClip();
		}
	}
}

//�����_�����O
void Editor::Renderer() const
{
	
	//�}�E�X�J�[�\���`��
	rectCursor->Draw(glm::vec2(mousePosition.x * CELL,mousePosition.y * CELL), 
		glm::vec2((mousePosition.x * CELL)  + CELL, (mousePosition.y * CELL) +  CELL),
		0,glm::vec2(0,0), glm::vec4(0, 255, 0, 255));
		
	//�g�g��
	for (int x = 0; x < windowContext->getSize().x / CELL; x++)
	{
		line->Draw(glm::vec2(x * CELL,0), glm::vec2(x * CELL, windowContext->getSize().y),glm::vec4(0,255,0,255));
	}

	for (int y = 0; y < windowContext->getSize().y / CELL; y++)
	{
		line->Draw(glm::vec2(0, y * CELL), glm::vec2(windowContext->getSize().x, y * CELL ), glm::vec4(0, 255, 0, 255));
	}
	
	//�J�[�\��
	rectMenu->Draw(glm::vec2(0,CELL * (STAGE_SIZE_HEIGHT)), glm::vec2(CELL * STAGE_SIZE_WIDTH, CELL * (STAGE_SIZE_HEIGHT + 1)),0.0f,glm::vec2(0,0),glm::vec4(0,100,0,255));


	//�^�C���`��
	for (int y = 0; y < STAGE_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_SIZE_WIDTH; x++)
		{
			//�^�C���̏ꍇ
			int s = stageData->at(y * STAGE_SIZE_WIDTH + x);
			if (s != (int)TileType::None)
			{
				sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), tileData->at(s).texNum, 0, glm::vec2(0, 0), tileData->at(s).startSize, tileData->at(s).endSize);
			}

			//�I�u�W�F�N�g�̏ꍇ
			s = stageDataObject->at(y * STAGE_SIZE_WIDTH + x);
			if (s != (int)TileType::None)
			{
				sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), tileData->at(s).texNum, 0, glm::vec2(0, 0), tileData->at(s).startSize, tileData->at(s).endSize);
			}			
		}
	}
	
	//�Z�[�u��\��
	if (isSave == true)
	{
		//saveText->Draw(glm::vec2(STAGE_SIZE_WIDTH - CELL, STAGE_SIZE_HEIGHT - CELL), "SAVED", 1.0f, glm::vec3(0, 255, 0));
		saveText->Draw(glm::vec2(100,100),1.0f, glm::vec3(0, 255, 0), "SAVED");
	}

	if (selectTile < tileData->size())
	{
		sprite->DrawGraph(glm::vec2(CELL, CELL), tileData->at(selectTile).texNum, 0, glm::vec2(0, 0), tileData->at(selectTile).startSize, tileData->at(selectTile).endSize);
	}



	//sprite->DrawGraph(glm::vec2(CELL, CELL), 0, 0, glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(CELL, CELL));

	/*
	std::cout << "start X: " << tileData->at(mouseScroll).startSize.x << std::endl;
	std::cout << "start y: " << tileData->at(mouseScroll).startSize.y << std::endl;
	std::cout << "end X: " << tileData->at(mouseScroll).endSize.x << std::endl;
	std::cout << "end y: " << tileData->at(mouseScroll).endSize.y << std::endl;
	std::cout << "" << std::endl;
	std::cout << "mouseScroll : " << mouseScroll << std::endl;
	std::cout << "tileData,size() : " << tileData->size() << std::endl;
	std::cout << "" << std::endl;
	*/

	//std::cout << "tileData,size() : " << windowContext->getKeyInput(GLFW_KEY_RIGHT) << std::endl;

	
	

	
}

//���[�v
void Editor::Loop(Entry* e)
{
	Update();
	Renderer();
}

// ##################################### �����o�֐� #####################################











//�f�X�g���N�^
Editor::~Editor()
{

}
