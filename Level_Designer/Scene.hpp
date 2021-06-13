#ifndef ___SCENE_HPP_
#define ___SCENE_HPP_
#include <iostream>
#include "Sequence.hpp"
#include "FrameWork.hpp"

#define CELL (48)

class Scene
{
public:

	Scene(std::shared_ptr<FrameWork::Window> w,Sequence e);	//コンストラクタ
	~Scene();												//デストラクタ

	virtual void Update() = 0;			//更新
	virtual void Renderer()const = 0;	//描画

protected:

	std::shared_ptr<FrameWork::Window> windowContext;	//ウインドウコンテキスト
	Sequence moveScene;	//シーン推移
};
#endif