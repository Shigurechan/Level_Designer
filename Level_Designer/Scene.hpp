#ifndef ___SCENE_HPP_
#define ___SCENE_HPP_


#define CELL ((int)48)


#include <iostream>
#include "Sequence.hpp"
#include <FrameWork.hpp>

class Scene
{
public:

	Scene(std::shared_ptr<FrameWork::Window> w,Sequence e);	//コンストラクタ
	~Scene();												//デストラクタ

	virtual void Update() = 0;
	virtual void Renderer() = 0;
	


protected:

	std::shared_ptr<FrameWork::Window> windowContext;	//ウインドウコンテキスト

	Sequence moveScene;	//シーン推移
};

#endif


