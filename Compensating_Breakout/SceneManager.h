///-------------------------------------------------------------------
//*
//*	@作成日		2017/08/28
//*
//*	@名前		SceneManager.h
//*
//* @役割		ゲームシーンの管理クラス
//*
//*	@著者		加藤 彰馬
//*
///-------------------------------------------------------------------

// 多重インクルードの防止
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "BaseScene.h"
#include "GameTitle.h"
#include "GamePlay.h"



class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// ゲームシーンリスト
	enum SCENE
	{
		TITLE,
		PLAY
	};

	// シーンの切り替え関数
	void ChangeScenes(SCENE scene);
	// 現在のシーンの更新関数
	void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker);
	// 現在のシーンの描画関数
	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	// 現在のシーン
	BaseScene* m_scene;

};

