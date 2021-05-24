#ifndef ___GAME_HPP_
#define ___GAME_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class Editor : public Scene
{
public:
	Editor(std::shared_ptr<FrameWork::Window> w, std::string path);		//コンストラクタ
	~Editor();	//デストラクタ

	void Update();			//更新
	void Renderer();	//レンダリング
	void Loop(Entry* e);	//ループ


private:
	
	bool isNewFile;	//新しいファイルなのかファイル編集なのかを判定

	std::shared_ptr<FrameWork::Line> line;



};


#endif
