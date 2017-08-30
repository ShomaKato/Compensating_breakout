///-------------------------------------------------------------------
//*
//*	@作成日		2017/08/28
//*
//*	@名前		GameTitle.h
//*
//* @役割		ゲームタイトルシーンの処理クラス
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



class GameTitle : public  BaseScene
{
public:
	GameTitle();
	~GameTitle();

	// 初期化関数
	//* NOTE:コムポインタはポインタ型として引数に使えるっぽい？
	//void Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device);
	void Initialize(ID3D11Device* device);
	// 更新関数
	void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker);
	// 描画関数
	void Render(DirectX::SpriteBatch* spriteBatch);
	// 消滅関数
	void DestroyItself();

	//* NOTE:テクスチャの読み込みはInitializeで行えることがわかったので↓関数は削除
	// テクスチャ読み込み関数
	//void CreateDevice();

private:
	// タイトルテクスチャ
	//* NOTE:テクスチャはポインタ型でもユニークポインタ型でも、都合は悪くなさそう　統一してあればOKかも？
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	//ID3D11ShaderResourceView* m_title;

	// タイトルテクスチャの座標
	DirectX::SimpleMath::Vector2 m_pos;

	//* NOTE:別に左上にアンカーあっても良さそうなのでこれ↓は使わないことに
	//// 多分、タイトルテクスチャのアンカーの座標
	//DirectX::SimpleMath::Vector2 m_titleOrigin;
};

