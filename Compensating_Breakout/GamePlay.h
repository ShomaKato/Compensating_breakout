///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/08/28
//*
//*	@���O		GamePlay.h
//*
//* @����		�Q�[���v���C�V�[���̏����N���X
//*
//*	@����		���� ���n
//*
///-------------------------------------------------------------------

// ���d�C���N���[�h�̖h�~
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include "BaseScene.h"



//////////////////////////
//* �v���C�V�[���N���X *//
//////////////////////////

class GamePlay : public BaseScene
{
	//* NOTE:const static���g�����}�N����`�́Aint,enum�Ɍ������ꍇ(�܂萮���H)�̂�, �N���X�̒��ŏ������ł��邪�A
	//* NOTE:����ȊO�̌^�͐錾�����������A�N���X�̊O�Œ�`�������Ȃ��Ƃ����Ȃ��A�炵��

	//* NOTE:���������Aconst�̌��static��t����̂́A�����ӏ�����C���N���[�h�����悤��
	//* NOTE:�w�b�_�t�@�C���ɂāA���d��`��h�����߂ɍs�����́A�炵��

	// �}�N����`
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

	// �������֐�
	void Initialize(ID3D11Device* device);
	// �X�V�֐�
	void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker);
	// �`��֐�
	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_paddle;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ball;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_block;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clear;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_over;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_return;

	// �e�N�X�`���̍��W
	DirectX::SimpleMath::Vector2 m_paddlePos;
	DirectX::SimpleMath::Vector2 m_ballPos;
	DirectX::SimpleMath::Vector2 m_blockPos[NUM_BLOCKS];
	DirectX::SimpleMath::Vector2 m_clearPos;
	DirectX::SimpleMath::Vector2 m_overPos;
	DirectX::SimpleMath::Vector2 m_returnPos;

	// �p�h���̑��x
	float m_paddleV;
	// �{�[���̑��x
	DirectX::SimpleMath::Vector2 m_ballV;

	// �Q�[���̏��
	//enum STATE
	//{
	//	PLAYING,
	//	CLEAR,
	//	OVER
	//};

	//* NOTE:�񋓌^���Ƃ��܂������Ȃ������i�Ƃ������������킩��Ȃ������j�̂�int��
	int m_state;	/* 0=Playing, 1=Clear, 2=Over */
};



////////////////////////
////* �u���b�N�N���X *//
////////////////////////
//
//class Block
//{
//public:
//	Block();
//	~Block();
//
//	// ���Ŋ֐�
//	void Disappear();
//};