#pragma once

class BackBuffer
{
public:
	static BackBuffer* Get();
	
	static void Create();
	static void Delete();

	ID3D11DepthStencilView* GetDepthView()
	{
		return depthView;
	}

	ID3D11RenderTargetView* GetRenderView()
	{
		return renderView;
	}

	void SetTarget();

private:
	BackBuffer();
	~BackBuffer();

	void CreateTexture();
	void CreateRenderTarget();
	void CreateView();


	static BackBuffer* instance;

	ID3D11Texture2D* texture;
	ID3D11DepthStencilView* depthView;
	ID3D11RenderTargetView* renderView;
};