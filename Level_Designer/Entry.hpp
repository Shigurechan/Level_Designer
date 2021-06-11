#ifndef ___ENTRY_HPP_
#define ___ENTRY_HPP_
#include <iostream>
#include "Scene.hpp"

#include <FrameWork.hpp>

class Title;
class Editor;
class GameOver;



class Entry : public Scene
{
	
public:

	Entry(std::shared_ptr<FrameWork::Window> w);		//コンストラクタ
	~Entry();											//デストラクタ
	
	void Update();				//更新
	void Renderer()const;		//レンダリング
	void Loop();				//ループ

	void MoveTo(Sequence e);	//シーン切り替え
	
	std::string drapPath;	//D＆Dパス

private:

	//各種シーン
	std::unique_ptr<Title> title;		//タイトル
	std::unique_ptr<Editor> editor;		//エディター
};


#endif

