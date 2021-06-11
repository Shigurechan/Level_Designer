#include "Editor.hpp"
#include "Scene.hpp"
#include "FrameWork.hpp"
#include <fstream>

// ##################################### コンストラクタ ##################################### 
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
,anim(w,5)	//アニメーション
{
	//セーブ
	saveText = std::make_shared<FrameWork::Text>(w);	//セーブ文字描画
	isSave = false;										//保存キーをおしたかどうか？

	stageData = std::make_shared<std::vector<byte>>(STAGE_SIZE,(int)TileType::None);			//ステージ
	stageDataObject = std::make_shared<std::vector<byte>>(STAGE_SIZE, (int)TileType::None);		//ステージオブジェクト
	tileData = std::make_shared<std::vector<SpriteData>>();										//タイルデータ

	//枠組み
	line = std::make_shared<FrameWork::Line>(windowContext);				//枠組み
	rectCursor = std::make_shared<FrameWork::Rectangle>(windowContext);		//カーソル
	rectMenu = std::make_shared<FrameWork::Rectangle>(windowContext);		//メニューバー

	//スプライト
	sprite = std::make_shared<FrameWork::Sprite>(windowContext);			//スプライトクラス
	sprite->setTexture(FrameWork::LoadTexture("Assets/backGround.png"));	//背景
	sprite->setTexture(FrameWork::LoadTexture("Assets/item.png"));			//アイテム
	sprite->setTexture(FrameWork::LoadTexture("Assets/enemy.png"));			//エネミー

	// ================ タイル情報を設定 ================ 

	//背景
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

	//アイテム
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

	//エネミー
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


	//ファイル操作を指定
	if (path == "")
	{
		//新規ファイル作成

		isNewFile = true;

		stageData->resize(STAGE_SIZE);
		stageDataObject->resize(STAGE_SIZE);
	}
	else 
	{
		// ファイル編集

		isNewFile = false;
		stageData->clear();
		stageDataObject->clear();

		std::cout << path.size() << std::endl;
		strcpy_s(fileName,sizeof(fileName) / sizeof(char),path.c_str());	//ファイル名をコピー

		std::ifstream file;
		file.open(fileName, std::ios::binary | std::ios::in);
		if (file.is_open() == true)
		{
			//タイル
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				char c;
				file.read(&c, sizeof(byte));
				stageData->push_back((byte)c);
				printf("0x%x\n",(byte)c);
			}

			//オブジェクト
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				char c;
				file.read(&c, sizeof(byte));
				stageDataObject->push_back((byte)c);
			}
			file.close();	//ファイルを閉じる
		}	
	}
}

// #####################################　タイル操作 ##################################### 
void Editor::KeyControl()
{
	// ================ マウスで描画 ================ 

	//マウスカーソル座標
	mousePosition = windowContext->getMousePos();
	mousePosition.x = (int)mousePosition.x / (int)CELL;
	mousePosition.y = (int)mousePosition.y / (int)CELL;

	//クリックで描画
	if (windowContext->getMouseButton(0) > 1)
	{
		if ((((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) < STAGE_SIZE)
		{
			if (selectTile < tileData->size())
			{
				if (tileData->at(selectTile).texNum == BACKGROUND_TEX_NUM)
				{
					stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = selectTile;
				}
				else
				{
					stageDataObject->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = selectTile;
				}
			}
		}
	}
	else if (windowContext->getMouseButton(1) == 1)
	{
		//タイル削除
		if (stageDataObject->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) != (int)TileType::None)
		{
			stageDataObject->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = (int)TileType::None;
		}
		else
		{
			stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = (int)TileType::None;
		}
	}

	// ================ タイル選択 ================ 
	keyRight = windowContext->getKeyInput(GLFW_KEY_RIGHT);	//Right key
	keyLeft = windowContext->getKeyInput(GLFW_KEY_LEFT);	//Left key

	if (keyRight > 0)
	{
		if (keyRight == 1)
		{
			selectTile++;
		}
		else if (keyRight > KEY_HOLD)
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
		else if (keyLeft > KEY_HOLD)
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
		selectTile = (int)tileData->max_size();
	}
}

// #####################################　ファイルを上書き保存 ##################################### 
void Editor::SaveFile()
{
	if (windowContext->getKeyInput(GLFW_KEY_S) == 1)
	{
		isSave = true;
		std::ofstream file;

		if (isNewFile == false)
		{
			file.open(fileName, std::ios::binary | std::ios::out);
		}
		else 
		{
			file.open("Stage/test.bin", std::ios::binary | std::ios::out);
		}

		if (file.is_open() == true)
		{
			//タイル
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				const char c = stageData->at(i);
				file.write(&c, sizeof(unsigned char));
			}

			//オブジェクト
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				const char c = stageDataObject->at(i);
				file.write(&c, sizeof(unsigned char));
			}
		}
	}

	if (isSave == true)
	{
		int n = 0;
		if (anim.getOnceClip(10, n) == true)
		{
			isSave = false;
			anim.ResetOnceClip();
		}
	}
}


// ################################################### 更新 ################################################### 
void Editor::Update()
{
	KeyControl();	//操作
	SaveFile();		//ファイルを保存	
}

// ##################################### 描画 ##################################### 
void Editor::Renderer() const
{
	
	//マウスカーソル描画
	rectCursor->Draw(glm::vec2(mousePosition.x * CELL,mousePosition.y * CELL), 
		glm::vec2((mousePosition.x * CELL) + CELL, (mousePosition.y * CELL) +  CELL),
		0,glm::vec2(0,0), glm::vec4(0, 255, 0, 255));
		
	//枠組み
	for (int x = 0; x < windowContext->getSize().x / CELL; x++)
	{
		line->Draw(glm::vec2(x * CELL,0), glm::vec2(x * CELL, windowContext->getSize().y),glm::vec4(0,255,0,255));
	}
	for (int y = 0; y < windowContext->getSize().y / CELL; y++)
	{
		line->Draw(glm::vec2(0, y * CELL), glm::vec2(windowContext->getSize().x, y * CELL ), glm::vec4(0, 255, 0, 255));
	}
	
	//カーソル
	rectMenu->Draw(glm::vec2(0,CELL * (STAGE_SIZE_HEIGHT)), glm::vec2(CELL * STAGE_SIZE_WIDTH, CELL * (STAGE_SIZE_HEIGHT + 1)),0.0f,glm::vec2(0,0),glm::vec4(0,100,0,255));

	//タイル描画
	for (int y = 0; y < STAGE_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_SIZE_WIDTH; x++)
		{
			//タイルの場合
			int s = stageData->at(y * STAGE_SIZE_WIDTH + x);
			if (s != (int)TileType::None)
			{
				sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), tileData->at(s).texNum, 0, glm::vec2(0, 0), tileData->at(s).startSize, tileData->at(s).endSize);
			}

			//オブジェクトの場合
			s = stageDataObject->at(y * STAGE_SIZE_WIDTH + x);
			if (s != (int)TileType::None)
			{
				sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), tileData->at(s).texNum, 0, glm::vec2(0, 0), tileData->at(s).startSize, tileData->at(s).endSize);
			}			
		}
	}
	
	//セーブを表示
	if (isSave == true)
	{
		saveText->Draw(glm::vec2(100,100),1.0f, glm::vec3(0, 255, 0), "SAVED");
	}

	//選択しているタイルを描画
	if (selectTile < tileData->size())
	{
		sprite->DrawGraph(glm::vec2(0, (STAGE_SIZE_HEIGHT * CELL)), tileData->at(selectTile).texNum, 0, glm::vec2(0, 0), tileData->at(selectTile).startSize, tileData->at(selectTile).endSize);
	}	
}

// ##################################### ループ ##################################### 
void Editor::Loop(Entry* e)
{
	Update();
	Renderer();
}

// ##################################### デストラクタ ##################################### 
Editor::~Editor()
{

}
