#ifndef ___SCENE_HPP_
#define ___SCENE_HPP_


#define CELL (48)
#define byte unsigned char 
#define STAGE_SIZE_WIDTH 26
#define STAGE_SIZE_HEIGHT 17
#define STAGE_SIZE (STAGE_SIZE_WIDTH * STAGE_SIZE_HEIGHT)



#include <iostream>
#include "Sequence.hpp"
#include <FrameWork.hpp>

class Scene
{
public:

	Scene(std::shared_ptr<FrameWork::Window> w,Sequence e);	//コンストラクタ
	~Scene();												//デストラクタ

	virtual void Update() = 0;
	virtual void Renderer()const = 0;
	


protected:

	std::shared_ptr<FrameWork::Window> windowContext;	//ウインドウコンテキスト

	Sequence moveScene;	//シーン推移
};

#endif


