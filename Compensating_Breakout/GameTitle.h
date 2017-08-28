///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/08/28
//*
//*	@���O		GameTitle.h
//*
//* @����		�Q�[���^�C�g���̏����N���X
//*
//*	@����		���� ���n
//*
///-------------------------------------------------------------------

// ���d�C���N���[�h�̖h�~
#pragma once

// �w�b�_�t�@�C���̃C���N���[�h
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>


//////////////////////
//* �^�C�g���N���X *//
//////////////////////
class GameTitle
{
public:
	GameTitle();
	~GameTitle();

	// �������֐�
	void Initialize();
	// �X�V�֐�
	void Update();
	// �`��֐�
	void Render();
	// �ǂݍ��݊֐�
	void CreateDevice();

private:
	// �L�[�{�[�h
	DirectX::Keyboard* m_keyboard;

	//* �^�C�g���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	//* �^�C�g���e�N�X�`���̈ʒu�i�ǐ^�񒆁j
	DirectX::SimpleMath::Vector2 m_pos;
	//* �����A�^�C�g���e�N�X�`���̃A���J�[�̍��W
	DirectX::SimpleMath::Vector2 m_titleOrigin;


};

