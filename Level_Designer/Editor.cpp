#include "Editor.hpp"
#include "Scene.hpp"
#include "FrameWork.hpp"
#include <fstream>


//コンストラクタ
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
{
	stageData = std::make_shared<std::vector<byte>>(STAGE_SIZE, (int)TileType::None);
	tileData = std::make_shared<std::vector<SpriteData>>();

	//ファイル操作を指定
	if (path == "")
	{
		//新規ファイル作成
		isNewFile = true;

		std::ofstream file;
		file.open("Stage/test.bin");
		file.close();


	}
	else {

		// ファイル編集
		isNewFile = false;





		std::ofstream file;
		file.open(path);

	}

	line = std::make_shared<FrameWork::Line>(windowContext);
	rectCursor = std::make_shared<FrameWork::Rectangle>(windowContext);
	rectMenu = std::make_shared<FrameWork::Rectangle>(windowContext);

	sprite = std::make_shared<FrameWork::Sprite>(windowContext);
	sprite->setTexture(FrameWork::LoadTexture("Assets/Tileset.png"));

	//タイル情報を格納
	for (int y = 0; y < SPRITE_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < SPRITE_SIZE_WIDTH; x++)
		{
			SpriteData s;
			
			s.startSize = glm::vec2(x * CELL, y * CELL);
			s.endSize = glm::vec2((x + 1) * CELL, (y + 1) * CELL);

			tileData->push_back(s);
			
		}
	}


	//std::cout << tileData->size() << std::endl;

	
}

//更新
void Editor::Update()
{
	//マウスカーソル座標
	mousePosition = windowContext->getMousePos();
	mousePosition.x = (int)mousePosition.x / (int)CELL;
	mousePosition.y = (int)mousePosition.y / (int)CELL;

	//クリックで描画
	if (windowContext->getMouseButton(0) == true)
	{
		if ((((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) < STAGE_SIZE)
		{
			stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = selectTile;
		}
	}
	else if (windowContext->getMouseButton(1) == true)
	{
		//タイル削除
		stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = (int)TileType::None;
	}


	//タイル選択操作
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
	//配列の範囲内に修正
	if (selectTile > (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 1)
	{
		selectTile = (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 1;
	}
	else if (selectTile < 0)
	{
		selectTile = 0;
	}

	//ファイルに書き込み
	if (windowContext->getKeyInput(GLFW_KEY_S) == 1)
	{
		
		std::ofstream file;
		file.open("Stage/test.bin", std::ios::binary | std::ios::out);
		if (file.is_open() == true)
		{
			for (int i = 0; i < STAGE_SIZE; i++)
			{
				const char c = stageData->at(i);
				file.write(&c, sizeof(unsigned char));
			}
		}
		
		file.close();
	}




	

}

//レンダリング
void Editor::Renderer() const
{
	
	//マウスカーソル描画
	rectCursor->Draw(glm::vec2(mousePosition.x * CELL,mousePosition.y * CELL), 
		glm::vec2((mousePosition.x * CELL)  + CELL, (mousePosition.y * CELL) +  CELL),
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
	
	rectMenu->Draw(glm::vec2(0,CELL * (STAGE_SIZE_HEIGHT)), glm::vec2(CELL * STAGE_SIZE_WIDTH, CELL * (STAGE_SIZE_HEIGHT + 1)),0.0f,glm::vec2(0,0),glm::vec4(0,100,0,255));


	//タイル描画
	for (int y = 0; y < STAGE_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_SIZE_WIDTH; x++)
		{
			int s = stageData->at(y * STAGE_SIZE_WIDTH + x);
			if (s != (int)TileType::None)
			{
				sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), 0, 0, glm::vec2(0, 0), tileData->at(s).startSize, tileData->at(s).endSize);
			}
		}
	}
	
	//選択しているタイルを描画	
	if (selectTile > 1)
	{
		sprite->DrawGraph(glm::vec2(10, CELL * STAGE_SIZE_HEIGHT), 0, 0, glm::vec2(-20, -20), tileData->at(selectTile - 2).startSize, tileData->at(selectTile - 2).endSize);
	}
	if (selectTile > 0)
	{
		sprite->DrawGraph(glm::vec2(CELL + 3, CELL * STAGE_SIZE_HEIGHT), 0, 0, glm::vec2(-10, -10), tileData->at(selectTile - 1).startSize, tileData->at(selectTile - 1).endSize);
	}


	sprite->DrawGraph(glm::vec2(CELL * 2, CELL * STAGE_SIZE_HEIGHT), 0, 0, glm::vec2(0, 0), tileData->at(selectTile).startSize, tileData->at(selectTile).endSize);

	if (selectTile < (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 1)
	{
		sprite->DrawGraph(glm::vec2((CELL*3) - 2, CELL * STAGE_SIZE_HEIGHT), 0, 0, glm::vec2(-10, -10), tileData->at(selectTile + 1).startSize, tileData->at(selectTile + 1).endSize);
	}

	if (selectTile < (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 2)
	{
		sprite->DrawGraph(glm::vec2((CELL * 4) - 10, CELL * STAGE_SIZE_HEIGHT), 0, 0, glm::vec2(-20, -20), tileData->at(selectTile + 2).startSize, tileData->at(selectTile + 2).endSize);
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

//ループ
void Editor::Loop(Entry* e)
{
	Update();
	Renderer();
}

// ##################################### メンバ関数 #####################################











//デストラクタ
Editor::~Editor()
{

}
