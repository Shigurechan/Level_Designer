#ifndef ___GAMEOVER_HPP_
#define ___GAMEOVER_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class GameOver : public Scene
{
public:
	GameOver(std::shared_ptr<FrameWork::Window> w);		//コンストラクタ
	~GameOver();										//デストラクタ

	void Update();			//更新
	void Renderer();		//レンダリング
	void Loop(Entry* e);	//ループ

};


#endif
