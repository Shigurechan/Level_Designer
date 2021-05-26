#include "Editor.hpp"
#include "Scene.hpp"
#include "FrameWork.hpp"
#include <fstream>


//コンストラクタ
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
{
	stageData = std::make_shared<std::vector<byte>>(STAGE_SIZE);
	tileData = std::make_shared<std::vector<SpriteData>>();

	//ファイル操作を指定
	if (path == "")
	{
		//新規ファイル作成
		isNewFile = true;
	}
	else {

		// ファイル編集


		isNewFile = false;

		std::ofstream file;
		file.open(path);

	}



	line = std::make_shared<FrameWork::Line>(windowContext);
	rectCursor = std::make_shared<FrameWork::Rectangle>(windowContext);

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

	
}


//更新
void Editor::Update()
{
	//マウスカーソル座標
	mousePosition = windowContext->getMousePos();
	mousePosition.x = (int)mousePosition.x / CELL;
	mousePosition.y = (int)mousePosition.y / CELL;

	//クリックで描画
	if (windowContext->getMouseButton(0) == true)
	{
		if ((((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) < STAGE_SIZE)
		{
			stageData->at(((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) = selectTile + 1;
		}
	}



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
	
	std::cout << keyRight << std::endl;





	//配列の範囲内に修正
	if (selectTile > (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 1)
	{
		selectTile = (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 1;
	}
	else if (selectTile < 0)
	{
		selectTile = 0;
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
	
	//タイル描画
	for (int y = 0; y < STAGE_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_SIZE_WIDTH; x++)
		{
			if (stageData->at(y * STAGE_SIZE_WIDTH + x) != 0)
			{

				sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), 0, 0, glm::vec2(0, 0), tileData->at(selectTile).startSize, tileData->at(selectTile).endSize);
			}
			/*	
			switch (stageData->at(y * STAGE_SIZE_WIDTH + x))
			{
			 	case 1: { sprite->DrawGraph(glm::vec2(x * CELL, y * CELL), 0, 0, glm::vec2(0, 0), tileData->at(selectTile).startSize, tileData->at(selectTile).endSize); } break;
			}

			*/
		}
	}
	
	//選択しているタイルを描画
	sprite->DrawGraph(glm::vec2(CELL, CELL * STAGE_SIZE_HEIGHT), 0, 0, glm::vec2(0, 0), tileData->at(selectTile).startSize, tileData->at(selectTile).endSize);

	if (selectTile > 0) 
	{
		sprite->DrawGraph(glm::vec2(0, CELL * STAGE_SIZE_HEIGHT + 10), 0, 0, glm::vec2(0, 0), tileData->at(selectTile - 1).startSize, tileData->at(selectTile - 1).endSize);
	}

	if (selectTile < (SPRITE_SIZE_WIDTH * SPRITE_SIZE_HEIGHT) - 1)
	{
		sprite->DrawGraph(glm::vec2(CELL*2, CELL * STAGE_SIZE_HEIGHT + 10), 0, 0, glm::vec2(0, 0), tileData->at(selectTile + 1).startSize, tileData->at(selectTile + 1).endSize);

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

//デストラクタ
Editor::~Editor()
{

}
