///-------------------------------------------------------------------
//*
//*	@�쐬��		2017/08/28
//*
//*	@���O		SceneManager.h
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
#include "BaseScene.h"
#include "GameTitle.h"
#include "GamePlay.h"



class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	// �Q�[���V�[�����X�g
	enum SCENE
	{
		TITLE,
		PLAY
	};

	// �V�[���̐؂�ւ��֐�
	void ChangeScenes(SCENE scene);
	// ���݂̃V�[���̍X�V�֐�
	void Update(DirectX::Keyboard* keyboard, DirectX::Keyboard::KeyboardStateTracker* keyboardTracker);
	// ���݂̃V�[���̕`��֐�
	void Render(DirectX::SpriteBatch* spriteBatch);

private:
	// ���݂̃V�[��
	BaseScene* m_scene;

};

