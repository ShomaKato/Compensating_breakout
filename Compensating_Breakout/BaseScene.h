///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/08/29
//*
//*	@���O		BaseScene.h
//*
//* @����		�Q�[���V�[���̊Ǘ��N���X
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
#include "SpriteBatch.h"



class BaseScene
{
public:
	BaseScene();
	~BaseScene();

	// ���z�������֐�
	virtual void Initialize(ID3D11Device* device) = 0;
	// ���z�X�V�֐�
	virtual void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker) = 0;
	// ���z�`��֐�
	virtual void Render(DirectX::SpriteBatch* m_spriteBatch) = 0;

protected:

	//* NOTE:�֐��̈����Ƃ������̂��ǂ����p���ׂ��������Y��Ă������̈╨����
	//// �X�v���C�g�o�b�`
	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//// �f�o�C�X
	//Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//// �R���e�L�X�g�f�o�C�X
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//// �e�N�X�`���ǂݍ��݂Ɏg���A�����̃��\�[�X
	//Microsoft::WRL::ComPtr<ID3D11Resource> resource;

};

