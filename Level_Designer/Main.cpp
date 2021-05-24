#include <iostream>
#include "Entry.hpp"
#include <FrameWork.cpp>

int main()
{
	FrameWork::Init();	//初期化

	std::shared_ptr<FrameWork::Window> window = std::make_shared<FrameWork::Window>(48 * 26, 48 * 18,"Level designer");	//ウインドウコンテキスト

	FrameWork::setVersion(4,5);	//バージョン設定


	std::shared_ptr<Entry> entry = std::make_shared<Entry>(window);



	while (*window)
	{
		window->FrameUpdate();

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		entry->Loop();
		



		window->SwapBuffers();
		window->Wait();

	}




	return 0;
}