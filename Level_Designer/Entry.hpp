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
	void Renderer();			//レンダリング
	void Loop();				//ループ


	void MoveTo(Sequence e);	//シーン切り替え
	


	std::string drapPath;

private:

	
	//Sequence moveScene;	//シーン切り替え

	//各種シーン
	Title* title;
	Editor* editor;
	GameOver* gameOver;




};


#endif

