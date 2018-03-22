#pragma once

struct D3DDesc
{
	wstring appName;
	HINSTANCE instance;
	HWND mainHandle;
	float width;
	float height;
	bool bVsync;
	bool bFullScreen;
	D3DXCOLOR color;
};

class D3D
{
public:
	static D3D* Get();

	static void Create();
	static void Delete();

	static ID3D11Device* GetDevice()
	{
		return device;
	}

	static ID3D11DeviceContext* GetDC()
	{
		return deviceContext;
	}

	static IDXGISwapChain* GetSwapChain()
	{
		return swapChain;
	}

	static void GetDesc(D3DDesc* desc)
	{
		*desc = d3dDesc;
	}

	static void SetDesc(D3DDesc& desc)
	{
		d3dDesc = desc;
	}

	void BeginScene();
	void EndScene();

private:
	D3D();
	~D3D();

	static D3D* instance;

	static D3DDesc d3dDesc;
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;
	static IDXGISwapChain* swapChain;

	D3D_FEATURE_LEVEL version;
	UINT gpuMemorySize;
	wstring gpuDescription;

	UINT numerator;
	UINT denominator;
};