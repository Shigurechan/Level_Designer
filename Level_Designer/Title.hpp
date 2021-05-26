#ifndef TITLE_HPP_
#define TITLE_HPP_
#include <iostream>
#include "Scene.hpp"
#include <FrameWork.hpp>
class Entry;

class Title : public Scene
{
public:
	Title(std::shared_ptr<FrameWork::Window> w);	//コンストラクタ
	~Title();	//デストラクタ

	void Update();				//更新
	void Renderer()const;			//レンダリング
	void Loop(Entry* e);		//ループ

private:

	//タイトル表示
	std::shared_ptr<FrameWork::Text> newFileText;
	std::shared_ptr<FrameWork::Text> editFileText;




	int select;
	glm::vec2 position;
	std::string str;	//ドラック＆ドロップパス
};



#endif
