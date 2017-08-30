///-------------------------------------------------------------------
//*
//*	@作成日		2017/08/28
//*
//*	@名前		GamePlay.cpp
//*
//* @役割		ゲームプレイシーンの処理クラス
//*
//*	@著者		加藤 彰馬
//*
///-------------------------------------------------------------------

// ヘッダのインクルード
#include "pch.h"
#include "WICTextureLoader.h"
#include "GamePlay.h"

// 名前空間
using namespace DirectX;
using namespace DirectX::SimpleMath;



////////////////////////
//* メンバ変数の定義 *//
////////////////////////

////----------------------------------------------------------------------
////! @関数名：GamePlay
////!
////! @役割：プレイシーンのコンストラクタ
////!
////! @引数：なし(void)
////!
////! @戻り値：存在しない
////----------------------------------------------------------------------
GamePlay::GamePlay()
{
}

////----------------------------------------------------------------------
////! @関数名：GamePlay
////!
////! @役割：プレイシーンのデストラクタ
////!
////! @引数：存在しない
////!
////! @戻り値：存在しない
////----------------------------------------------------------------------
GamePlay::~GamePlay()
{
}

////----------------------------------------------------------------------
////! @関数名：GamePlay
////!
////! @役割：プレイシーンの初期化
////!
////! @引数：レンダリングおよびリソースの作成に使用されるデバイス (ID3D11Device*)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void GamePlay::Initialize(ID3D11Device* device)
{
	// テクスチャを初期化する
	m_paddle = nullptr;
	m_ball = nullptr;
	m_block = nullptr;
	m_clear = nullptr;
	m_over = nullptr;
	m_return = nullptr;

	// 絵をロードする
	CreateWICTextureFromFile(device, L"Images\\paddle.png", nullptr, m_paddle.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\ball.png", nullptr, m_ball.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\block.png", nullptr, m_block.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\clear.png", nullptr, m_clear.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\over.png", nullptr, m_over.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\return.png", nullptr, m_return.GetAddressOf());

	// パドルの初期位置
	m_paddlePos.x = (WINDOW_WIDTH / 2.0f) - PADDLE_WIDTH / 2.0f;
	m_paddlePos.y = WINDOW_HEIGHT - 70.0f;
	// ボールの初期位置
	m_ballPos.x = m_paddlePos.x + (BALL_HEIGHT / 2);
	m_ballPos.y = m_paddlePos.y - BALL_WIDTH;
	// ゲームクリア、オーバーテクスチャの位置
	m_clearPos.x = (WINDOW_WIDTH - END_WIDTH) / 2;
	m_overPos.x = (WINDOW_WIDTH - END_WIDTH) / 2;
	m_clearPos.y = 50;
	m_overPos.y = 50;
	m_returnPos.x = m_overPos.x;
	m_returnPos.y = END_HEIGHT;

	// パドルの速度
	m_paddleV = 5.5f;
	// ボールの速度
	m_ballV.x = -3.0f;
	m_ballV.y = -3.0f;

	// ゲーム状態の設定
	m_state = 0;

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		m_blockPos[i].x = BLOCK_WIDTH * (i / 3);
		m_blockPos[i].y = BLOCK_HEIGHT * (i % 3);
	}
}

////----------------------------------------------------------------------
////! @関数名：Update
////!
////! @役割：プレイシーンの更新
////!
////! @引数：キーボード、キーボードの状態を見る何か
////!		 (DirectX::Keyboard* DirectX::Keyboard::KeyboardStateTracker)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void GamePlay::Update(Keyboard* keyboard, Keyboard::KeyboardStateTracker* keyboardTracker)
{
	// キーボードの状態取得
	auto kb = keyboard->GetState();
	keyboardTracker->Update(kb);


	//* パドルの移動処理 *// 
	// ←キーで左へ
	if (kb.Left)
	{
		m_paddlePos.x = m_paddlePos.x - m_paddleV;
		// 左端に行ったらそこで止まる
		if (m_paddlePos.x < 0.0f)
		{
			m_paddlePos.x = 0.0f;
		}
	}
	// →キーで右へ
	if (kb.Right)
	{
		m_paddlePos.x = m_paddlePos.x + m_paddleV;
		// 右端に行ったらそこで止まる
		if (m_paddlePos.x > WINDOW_WIDTH - PADDLE_WIDTH)
		{
			m_paddlePos.x = WINDOW_WIDTH - PADDLE_WIDTH;
		}
	}


	//* ボールの移動処理 *//
	// 常に等速移動する
	m_ballPos.x = m_ballPos.x + m_ballV.x;
	m_ballPos.y = m_ballPos.y + m_ballV.y;
	// 画面端に行ったら反射or終了
	// 画面上
	if (m_ballPos.y < 0)
	{
		m_ballV.y *= -1.0f;
	}
	// 画面下
	if (m_ballPos.y + BALL_HEIGHT > WINDOW_HEIGHT)
	{
		m_ballV.x = 0.0f;
		m_ballV.y = 0.0f;
		m_state = 2;
	}
	// 画面左右
	if (m_ballPos.x < 0 || m_ballPos.x + BALL_WIDTH > WINDOW_WIDTH)
	{
		m_ballV.x = -m_ballV.x;
	}


	//* ボールとパドルの衝突処理 *//
	// パドル上部とボール下部がぶつかったら上に跳ね返る
	if ((m_ballPos.x <= m_paddlePos.x + PADDLE_WIDTH) &&
		(m_ballPos.x + BALL_WIDTH >= m_paddlePos.x) &&		
		(m_ballPos.y <= m_paddlePos.y + PADDLE_HEIGHT) &&	
		(m_ballPos.y + BALL_HEIGHT >= m_paddlePos.y))		
	//* NOTE:
	/* ボールの左上端がパドルの右上端より左側にあって且つ */
	/* ボールの右上端がパドルの左上側より右側にあって且つ */
	/* ボールの左上端がパドルの左下端より上側にあって且つ */
	/* ボールの右上端がパドルの左上側より下側にあるならば */ /// みたいなコードになってる？
	{
		m_ballV.y = -m_ballV.y;
	}

	//* ボールとブロックの衝突処理 *//
	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		if ((m_blockPos[i].x <= m_ballPos.x + 32) &&
			(m_blockPos[i].x + 32 >= m_ballPos.x) &&
			(m_blockPos[i].y <= m_ballPos.y + 32) &&
			(m_blockPos[i].y + 32 >= m_ballPos.y))
		{
			m_ballV.y = -m_ballV.y;
		}
	}

}

////----------------------------------------------------------------------
////! @関数名：Render
////!
////! @役割：プレイシーンの描画
////!
////! @引数：スプライトバッチ (SpriteBatch*)
////!
////! @戻り値：なし(void)
////----------------------------------------------------------------------
void GamePlay::Render(SpriteBatch* spriteBatch)
{
	// パドル、ボール、ブロックの描画
	spriteBatch->Draw(m_paddle.Get(), m_paddlePos);
	spriteBatch->Draw(m_ball.Get(), m_ballPos);
	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		spriteBatch->Draw(m_block.Get(), m_blockPos[i]);
	}


	// ゲームの状態によって、描画されるテクスチャが変わる
	// クリアなら、クリアテクスチャとタイトルへテクスチャ
	if (m_state == 1)
	{
		spriteBatch->Draw(m_clear.Get(), m_clearPos);
		spriteBatch->Draw(m_return.Get(), m_returnPos);
	}
	// ゲームオーバーなら、オーバーテクスチャとタイトルへテクスチャ
	if (m_state == 2)
	{
		spriteBatch->Draw(m_over.Get(), m_overPos);
		spriteBatch->Draw(m_return.Get(), m_returnPos);
	}
}
