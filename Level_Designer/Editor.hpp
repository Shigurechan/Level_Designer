#ifndef ___EDITOR_HPP_
#define ___EDITOR_HPP_

#include "Scene.hpp"
#include <FrameWork.hpp>

#define byte unsigned char 

//ステージサイズ
#define STAGE_SIZE_WIDTH 26
#define STAGE_SIZE_HEIGHT 17
#define STAGE_SIZE (STAGE_SIZE_WIDTH * STAGE_SIZE_HEIGHT)


//スプライト枚数
#define	SPRITE_NUM_WIDTH (480 / CELL)
#define SPRITE_NUM_HEIGHT (528 / CELL)

//タイル
#define	TILE_NUM_WIDTH (10)
#define TILE_NUM_HEIGHT (8)


//スプライト全部の枚数
#define SPRITE_MAX_NUM (SPRITE_NUM_WIDTH * SPRITE_NUM_HEIGHT)


class Entry;
class Editor : public Scene
{
public:
	Editor(std::shared_ptr<FrameWork::Window> w, std::string path);		//コンストラクタ
	~Editor();															//デストラクタ

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
	std::shared_ptr<FrameWork::Rectangle> rectMenu;		//メニュー範囲を描画
	std::shared_ptr<FrameWork::Sprite> sprite;			//スプライトを描画

	//スプライト描画範囲構造体
	typedef struct sprite_data
	{
		glm::vec2 startSize;
		glm::vec2 endSize;
	}SpriteData;

	std::shared_ptr<std::vector<SpriteData>> tileData;	//タイルリスト

	//エディットするステージ
	std::shared_ptr< std::vector<byte> > stageData;				//ステージ
	std::shared_ptr< std::vector<byte> > stageDataObject;		//マップオブジェクト

	glm::vec2 mousePosition;	//マウス座標
	
	int selectTile = 0;	//選択するタイル

	bool holdRight = false;	//長押し判定
	bool holdLeft = false;	//長押し判定
	int keyRight = 0;		//入力時間
	int keyLeft = 0;		//入力時間


	// 保存
	FrameWork::Animation anim;					//保存アニメーション
	bool isSave;								//保存キーを押したかどうか？
	std::shared_ptr<FrameWork::Text> saveText;	//セーブ文字を表示

	
};


#endif
