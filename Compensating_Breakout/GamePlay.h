///-------------------------------------------------------------------
//*
//*	@作成日		2017/08/28
//*
//*	@名前		GamePlay.h
//*
//* @役割		ゲームプレイシーンの処理クラス
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



//////////////////////////
//* プレイシーンクラス *//
//////////////////////////

class GamePlay : public BaseScene
{
	//* NOTE:const staticを使ったマクロ定義は、int,enumに限った場合(つまり整数？)のみ, クラスの中で初期化できるが、
	//* NOTE:それ以外の型は宣言しか書けず、クラスの外で定義を書かないといけない、らしい

	//* NOTE:そもそも、constの後にstaticを付けるのは、複数箇所からインクルードされるような
	//* NOTE:ヘッダファイルにて、多重定義を防ぐために行うもの、らしい

	// マクロ定義
	const static int PADDLE_WIDTH = 64;
	const static int PADDLE_HEIGHT = 16;
	const static int BALL_WIDTH = 32;
	const static int BALL_HEIGHT = 32;
	const static int BLOCK_WIDTH = 32;
	const static int BLOCK_HEIGHT = 32;
	const static int END_WIDTH = 512;
	const static int END_HEIGHT = 256;
	const static int WINDOW_WIDTH = 800;
	const static int WINDOW_HEIGHT = 600;
	const static int NUM_BLOCKS = 15;

public:
	GamePlay();
	~GamePlay();

	// 初期化関数
	void Initialize(ID3D11Device* device);
	// 更新関数
	void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker);
	// 描画関数
	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_paddle;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ball;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_block;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_over;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_return;

	// テクスチャの座標
	DirectX::SimpleMath::Vector2 m_paddlePos;
	DirectX::SimpleMath::Vector2 m_ballPos;
	DirectX::SimpleMath::Vector2 m_blockPos[NUM_BLOCKS];
	DirectX::SimpleMath::Vector2 m_clearPos;
	DirectX::SimpleMath::Vector2 m_overPos;
	DirectX::SimpleMath::Vector2 m_returnPos;

	// パドルの速度
	float m_paddleV;
	// ボールの速度
	DirectX::SimpleMath::Vector2 m_ballV;

	// ゲームの状態
	//enum STATE
	//{
	//	PLAYING,
	//	CLEAR,
	//	OVER
	//};

	//* NOTE:列挙型だとうまくいかなかった（というかやり方がわからなかった）のでintに
	int m_state;	/* 0=Playing, 1=Clear, 2=Over */
};



////////////////////////
////* ブロッククラス *//
////////////////////////
//
//class Block
//{
//public:
//	Block();
//	~Block();
//
//	// 消滅関数
//	void Disappear();
//};