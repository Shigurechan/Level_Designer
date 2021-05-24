#ifndef ___GAME_HPP_
#define ___GAME_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class Editor : public Scene
{
public:
	Editor(std::shared_ptr<FrameWork::Window> w);		//コンストラクタ
	~Editor();	//デストラクタ

	void Update();			//更新
	void Renderer();		//レンダリング
	void Loop(Entry* e);	//ループ


private:

	
	





};


#endif
