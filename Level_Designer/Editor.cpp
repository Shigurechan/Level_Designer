#include "Editor.hpp"
#include "Scene.hpp"
#include "FrameWork.hpp"
#include <fstream>


//コンストラクタ
Editor::Editor(std::shared_ptr<FrameWork::Window> w, std::string path) : Scene(w, Sequence::Editor)
{
	stageData = std::make_shared<std::vector<byte>>(STAGE_SIZE);

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
	



	
}


//更新
void Editor::Update()
{
	//マウスカーソル座標
	mousePosition = windowContext->getMousePos();
	mousePosition.x = (int)mousePosition.x / CELL;
	mousePosition.y = (int)mousePosition.y / CELL;



	if (windowContext->getMouseButton(0) == true)
	{
		if ( (((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x) < STAGE_SIZE ) 
		{
			stageData->at( ((int)mousePosition.y * STAGE_SIZE_WIDTH) + (int)mousePosition.x ) = 0x01;
		}
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
	

	
	for (int y = 0; y < STAGE_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_SIZE_WIDTH; x++)
		{


			switch (stageData->at(y * STAGE_SIZE_WIDTH + x))
			{
			case 1: { sprite->DrawGraph(glm::vec2(x * CELL,y * CELL), 0, 0, glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(CELL, CELL)); } break;

			
			};

		}
	}









	
	

	
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
