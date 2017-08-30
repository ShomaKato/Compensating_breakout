//
// Game.h
//

#pragma once

#include <Keyboard.h>
#include "StepTimer.h"
#include "SpriteBatch.h"
#include "SimpleMath.h"
#include "BaseScene.h"
#include "SceneManager.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;


	////////////////////////
	////* �O���[�o���ϐ� *//
	////////////////////////

	//// �X�v���C�g�o�b�`
	//static std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//// �f�o�C�X
	//static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	//// �R���e�L�X�g�f�o�C�X
	//static Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext;
	//// ���\�[�X���w���R���|�C���^�i�H�j
	//static Microsoft::WRL::ComPtr<ID3D11Resource> resource;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;


	BaseScene* m_scene;


	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// �L�[�{�[�h
	//* NOTE:�L�[�{�[�h���͂ɂ͂��̓���K�{�A�炵��
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;
};