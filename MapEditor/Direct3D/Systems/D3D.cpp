#include "../stdafx.h"
#include "D3D.h"

D3D* D3D::instance = NULL;

D3DDesc D3D::d3dDesc;
ID3D11Device* D3D::device = NULL;
ID3D11DeviceContext* D3D::deviceContext = NULL;
IDXGISwapChain* D3D::swapChain = NULL;

D3D * D3D::Get()
{
	assert(instance != NULL);

	return instance;
}

void D3D::Create()
{
	assert(instance == NULL);

	instance = new D3D();
}

void D3D::Delete()
{
	SAFE_DELETE(instance);
}

void D3D::BeginScene()
{
	deviceContext->ClearRenderTargetView
	(
		BackBuffer::Get()->GetRenderView(), d3dDesc.color
	);

	deviceContext->ClearDepthStencilView
	(
		BackBuffer::Get()->GetDepthView(), D3D11_CLEAR_DEPTH, 1, 0
	);
}

void D3D::EndScene()
{
	swapChain->Present(d3dDesc.bVsync == true ? 1 : 0, 0);
}

D3D::D3D()
	: version(D3D_FEATURE_LEVEL_11_0)
	, numerator(0), denominator(1)
{
	HRESULT hr;

	IDXGIFactory* factory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&factory);
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter;
	hr = factory->EnumAdapters(0, &adapter);
	assert(SUCCEEDED(hr));

	IDXGIOutput* adapterOutput;
	hr = adapter->EnumOutputs(0, &adapterOutput);
	assert(SUCCEEDED(hr));

	UINT modeCount;
	hr = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM
		, DXGI_ENUM_MODES_INTERLACED
		, &modeCount
		, NULL
	);
	assert(SUCCEEDED(hr));

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	hr = adapterOutput->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM
		, DXGI_ENUM_MODES_INTERLACED
		, &modeCount
		, displayModeList
	);
	assert(SUCCEEDED(hr));

	for (UINT i = 0; i < modeCount; i++)
	{
		bool isCheck = true;
		isCheck &= displayModeList[i].Width == d3dDesc.width;
		isCheck &= displayModeList[i].Height == d3dDesc.height;

		if (isCheck == true)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	hr = adapter->GetDesc(&adapterDesc);
	assert(SUCCEEDED(hr));

	gpuMemorySize = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	gpuDescription = adapterDesc.Description;

	delete[] displayModeList;
	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);


	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = (UINT)d3dDesc.width;
	swapChainDesc.BufferDesc.Height = (UINT)d3dDesc.height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (d3dDesc.bVsync == true)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = d3dDesc.mainHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !d3dDesc.bFullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	hr = D3D11CreateDeviceAndSwapChain
	(
		NULL
		, D3D_DRIVER_TYPE_HARDWARE
		, NULL
		, 0
		, &version
		, 1
		, D3D11_SDK_VERSION
		, &swapChainDesc
		, &swapChain
		, &device
		, NULL
		, &deviceContext
	);
	assert(SUCCEEDED(hr));
}

D3D::~D3D()
{
	if (swapChain != NULL)
		swapChain->SetFullscreenState(false, NULL);

	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
	SAFE_RELEASE(swapChain);
}
