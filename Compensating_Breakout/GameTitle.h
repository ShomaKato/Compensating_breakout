///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/08/28
//*
//*	@���O		GameTitle.h
//*
//* @����		�Q�[���^�C�g���V�[���̏����N���X
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



class GameTitle : public  BaseScene
{
public:
	GameTitle();
	~GameTitle();

	// �������֐�
	//* NOTE:�R���|�C���^�̓|�C���^�^�Ƃ��Ĉ����Ɏg������ۂ��H
	//void Initialize(Microsoft::WRL::ComPtr<ID3D11Device> device);
	void Initialize(ID3D11Device* device);
	// �X�V�֐�
	void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker);
	// �`��֐�
	void Render(DirectX::SpriteBatch* spriteBatch);
	// ���Ŋ֐�
	void DestroyItself();

	//* NOTE:�e�N�X�`���̓ǂݍ��݂�Initialize�ōs���邱�Ƃ��킩�����̂Ł��֐��͍폜
	// �e�N�X�`���ǂݍ��݊֐�
	//void CreateDevice();

private:
	// �^�C�g���e�N�X�`��
	//* NOTE:�e�N�X�`���̓|�C���^�^�ł����j�[�N�|�C���^�^�ł��A�s���͈����Ȃ������@���ꂵ�Ă����OK�����H
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	//ID3D11ShaderResourceView* m_title;

	// �^�C�g���e�N�X�`���̍��W
	DirectX::SimpleMath::Vector2 m_pos;

	//* NOTE:�ʂɍ���ɃA���J�[�����Ă��ǂ������Ȃ̂ł��ꁫ�͎g��Ȃ����Ƃ�
	//// �����A�^�C�g���e�N�X�`���̃A���J�[�̍��W
	//DirectX::SimpleMath::Vector2 m_titleOrigin;
};

