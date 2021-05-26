#ifndef ___EDITOR_HPP_
#define ___EDITOR_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

class Entry;
class Editor : public Scene
{
public:
	Editor(std::shared_ptr<FrameWork::Window> w, std::string path);		//コンストラクタ
	~Editor();	//デストラクタ

	void Update();			//更新
	void Renderer()const;	//レンダリング
	void Loop(Entry* e);	//ループ


private:
	
	//タイルの種類
	enum class TileType
	{
		None = 0xFF,
	};

	
	bool isNewFile;	//新しいファイルなのかファイル編集なのかを判定

	//描画変数
	std::shared_ptr<FrameWork::Line> line;				//枠組みを描画
	std::shared_ptr<FrameWork::Rectangle> rectCursor;	//カーソルを描画
	std::shared_ptr<FrameWork::Rectangle> rectMenu;	//メニュー範囲を描画

	std::shared_ptr<FrameWork::Sprite> sprite;			//スプライトを描画


	typedef struct sprite_data
	{
		glm::vec2 startSize;
		glm::vec2 endSize;
	}SpriteData;

	std::shared_ptr<std::vector<SpriteData>> tileData;	//タイルリスト
	std::shared_ptr<std::vector<byte>> stageData;		//エディットするステージ

	glm::vec2 mousePosition;				//マウス座標

	
	int selectTile = 0;	//選択するタイル

	bool holdRight = false;	//長押し判定
	bool holdLeft = false;	//長押し判定
	int keyRight = 0;	//入力時間
	int keyLeft = 0;	//入力時間



};


#endif
