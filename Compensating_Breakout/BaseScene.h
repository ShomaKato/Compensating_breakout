///-------------------------------------------------------------------
//*
//*	@作成日		2017/08/29
//*
//*	@名前		BaseScene.h
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
#include <Keyboard.h>
#include "SpriteBatch.h"



class BaseScene
{
public:
	BaseScene();
	~BaseScene();

	// 仮想初期化関数
	virtual void Initialize(ID3D11Device* device) = 0;
	// 仮想更新関数
	virtual void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker) = 0;
	// 仮想描画関数
	virtual void Render(DirectX::SpriteBatch* m_spriteBatch) = 0;

protected:

	//* NOTE:関数の引数というものをどう利用すべきかすらを忘れていた頃の遺物たち
	//// スプライトバッチ
	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//// デバイス
	//Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//// コンテキストデバイス
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//// テクスチャ読み込みに使う、何かのリソース
	//Microsoft::WRL::ComPtr<ID3D11Resource> resource;

};

