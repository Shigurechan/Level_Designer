#include "Scene.hpp"


//コンストラクタ
Scene::Scene(std::shared_ptr<FrameWork::Window> w,Sequence e)
{
	moveScene = e;		//自分のシーン
	windowContext = w;	//ウインドウコンテキスト
}
	

//デストラクタ
Scene::~Scene()
{

}

