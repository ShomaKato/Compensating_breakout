///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/08/28
//*
//*	@���O		GamePlay.cpp
//*
//* @����		�Q�[���v���C�V�[���̏����N���X
//*
//*	@����		���� ���n
//*
///-------------------------------------------------------------------

// �w�b�_�̃C���N���[�h
#include "pch.h"
#include "WICTextureLoader.h"
#include "GamePlay.h"

// ���O���
using namespace DirectX;
using namespace DirectX::SimpleMath;



////////////////////////
//* �����o�ϐ��̒�` *//
////////////////////////

////----------------------------------------------------------------------
////! @�֐����FGamePlay
////!
////! @�����F�v���C�V�[���̃R���X�g���N�^
////!
////! @�����F�Ȃ�(void)
////!
////! @�߂�l�F���݂��Ȃ�
////----------------------------------------------------------------------
GamePlay::GamePlay()
{
}

////----------------------------------------------------------------------
////! @�֐����FGamePlay
////!
////! @�����F�v���C�V�[���̃f�X�g���N�^
////!
////! @�����F���݂��Ȃ�
////!
////! @�߂�l�F���݂��Ȃ�
////----------------------------------------------------------------------
GamePlay::~GamePlay()
{
}

////----------------------------------------------------------------------
////! @�֐����FGamePlay
////!
////! @�����F�v���C�V�[���̏�����
////!
////! @�����F�����_�����O����у��\�[�X�̍쐬�Ɏg�p�����f�o�C�X (ID3D11Device*)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void GamePlay::Initialize(ID3D11Device* device)
{
	// �e�N�X�`��������������
	m_paddle = nullptr;
	m_ball = nullptr;
	m_block = nullptr;
	m_clear = nullptr;
	m_over = nullptr;
	m_return = nullptr;

	// �G�����[�h����
	CreateWICTextureFromFile(device, L"Images\\paddle.png", nullptr, m_paddle.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\ball.png", nullptr, m_ball.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\block.png", nullptr, m_block.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\clear.png", nullptr, m_clear.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\over.png", nullptr, m_over.GetAddressOf());
	CreateWICTextureFromFile(device, L"Images\\return.png", nullptr, m_return.GetAddressOf());

	// �p�h���̏����ʒu
	m_paddlePos.x = (WINDOW_WIDTH / 2.0f) - PADDLE_WIDTH / 2.0f;
	m_paddlePos.y = WINDOW_HEIGHT - 70.0f;
	// �{�[���̏����ʒu
	m_ballPos.x = m_paddlePos.x + (BALL_HEIGHT / 2);
	m_ballPos.y = m_paddlePos.y - BALL_WIDTH;
	// �Q�[���N���A�A�I�[�o�[�e�N�X�`���̈ʒu
	m_clearPos.x = (WINDOW_WIDTH - END_WIDTH) / 2;
	m_overPos.x = (WINDOW_WIDTH - END_WIDTH) / 2;
	m_clearPos.y = 50;
	m_overPos.y = 50;
	m_returnPos.x = m_overPos.x;
	m_returnPos.y = END_HEIGHT;

	// �p�h���̑��x
	m_paddleV = 5.5f;
	// �{�[���̑��x
	m_ballV.x = -3.0f;
	m_ballV.y = -3.0f;

	// �Q�[����Ԃ̐ݒ�
	m_state = 0;

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		m_blockPos[i].x = BLOCK_WIDTH * (i / 3);
		m_blockPos[i].y = BLOCK_HEIGHT * (i % 3);
	}
}

////----------------------------------------------------------------------
////! @�֐����FUpdate
////!
////! @�����F�v���C�V�[���̍X�V
////!
////! @�����F�L�[�{�[�h�A�L�[�{�[�h�̏�Ԃ����鉽��
////!		 (DirectX::Keyboard* DirectX::Keyboard::KeyboardStateTracker)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void GamePlay::Update(Keyboard* keyboard, Keyboard::KeyboardStateTracker* keyboardTracker)
{
	// �L�[�{�[�h�̏�Ԏ擾
	auto kb = keyboard->GetState();
	keyboardTracker->Update(kb);


	//* �p�h���̈ړ����� *// 
	// ���L�[�ō���
	if (kb.Left)
	{
		m_paddlePos.x = m_paddlePos.x - m_paddleV;
		// ���[�ɍs�����炻���Ŏ~�܂�
		if (m_paddlePos.x < 0.0f)
		{
			m_paddlePos.x = 0.0f;
		}
	}
	// ���L�[�ŉE��
	if (kb.Right)
	{
		m_paddlePos.x = m_paddlePos.x + m_paddleV;
		// �E�[�ɍs�����炻���Ŏ~�܂�
		if (m_paddlePos.x > WINDOW_WIDTH - PADDLE_WIDTH)
		{
			m_paddlePos.x = WINDOW_WIDTH - PADDLE_WIDTH;
		}
	}


	//* �{�[���̈ړ����� *//
	// ��ɓ����ړ�����
	m_ballPos.x = m_ballPos.x + m_ballV.x;
	m_ballPos.y = m_ballPos.y + m_ballV.y;
	// ��ʒ[�ɍs�����甽��or�I��
	// ��ʏ�
	if (m_ballPos.y < 0)
	{
		m_ballV.y *= -1.0f;
	}
	// ��ʉ�
	if (m_ballPos.y + BALL_HEIGHT > WINDOW_HEIGHT)
	{
		m_ballV.x = 0.0f;
		m_ballV.y = 0.0f;
		m_state = 2;
	}
	// ��ʍ��E
	if (m_ballPos.x < 0 || m_ballPos.x + BALL_WIDTH > WINDOW_WIDTH)
	{
		m_ballV.x = -m_ballV.x;
	}


	//* �{�[���ƃp�h���̏Փˏ��� *//
	// �p�h���㕔�ƃ{�[���������Ԃ��������ɒ��˕Ԃ�
	if ((m_ballPos.x <= m_paddlePos.x + PADDLE_WIDTH) &&
		(m_ballPos.x + BALL_WIDTH >= m_paddlePos.x) &&		
		(m_ballPos.y <= m_paddlePos.y + PADDLE_HEIGHT) &&	
		(m_ballPos.y + BALL_HEIGHT >= m_paddlePos.y))		
	//* NOTE:
	/* �{�[���̍���[���p�h���̉E��[��荶���ɂ����Ċ��� */
	/* �{�[���̉E��[���p�h���̍��㑤���E���ɂ����Ċ��� */
	/* �{�[���̍���[���p�h���̍����[���㑤�ɂ����Ċ��� */
	/* �{�[���̉E��[���p�h���̍��㑤��艺���ɂ���Ȃ�� */ /// �݂����ȃR�[�h�ɂȂ��Ă�H
	{
		m_ballV.y = -m_ballV.y;
	}

	//* �{�[���ƃu���b�N�̏Փˏ��� *//
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
////! @�֐����FRender
////!
////! @�����F�v���C�V�[���̕`��
////!
////! @�����F�X�v���C�g�o�b�` (SpriteBatch*)
////!
////! @�߂�l�F�Ȃ�(void)
////----------------------------------------------------------------------
void GamePlay::Render(SpriteBatch* spriteBatch)
{
	// �p�h���A�{�[���A�u���b�N�̕`��
	spriteBatch->Draw(m_paddle.Get(), m_paddlePos);
	spriteBatch->Draw(m_ball.Get(), m_ballPos);
	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		spriteBatch->Draw(m_block.Get(), m_blockPos[i]);
	}


	// �Q�[���̏�Ԃɂ���āA�`�悳���e�N�X�`�����ς��
	// �N���A�Ȃ�A�N���A�e�N�X�`���ƃ^�C�g���փe�N�X�`��
	if (m_state == 1)
	{
		spriteBatch->Draw(m_clear.Get(), m_clearPos);
		spriteBatch->Draw(m_return.Get(), m_returnPos);
	}
	// �Q�[���I�[�o�[�Ȃ�A�I�[�o�[�e�N�X�`���ƃ^�C�g���փe�N�X�`��
	if (m_state == 2)
	{
		spriteBatch->Draw(m_over.Get(), m_overPos);
		spriteBatch->Draw(m_return.Get(), m_returnPos);
	}
}
