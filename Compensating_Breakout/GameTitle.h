///-------------------------------------------------------------------
//*
//*	@作成日		2017/08/28
//*
//*	@名前		GameTitle.h
//*
//* @役割		ゲームタイトルの処理クラス
//*
//*	@著者		加藤 彰馬
//*
///-------------------------------------------------------------------

// 多重インクルードの防止
#pragma once

// ヘッダファイルのインクルード
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>


//////////////////////
//* タイトルクラス *//
//////////////////////
class GameTitle
{
public:
	GameTitle();
	~GameTitle();

	// 初期化関数
	void Initialize();
	// 更新関数
	void Update();
	// 描画関数
	void Render();
	// 読み込み関数
	void CreateDevice();

private:
	// キーボード
	DirectX::Keyboard* m_keyboard;

	//* タイトルテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	//* タイトルテクスチャの位置（ど真ん中）
	DirectX::SimpleMath::Vector2 m_pos;
	//* 多分、タイトルテクスチャのアンカーの座標
	DirectX::SimpleMath::Vector2 m_titleOrigin;


};

