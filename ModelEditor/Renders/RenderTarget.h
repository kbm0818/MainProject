#pragma once

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	ID3D11ShaderResourceView* GetResourceView()
	{
		return resourceView;
	}

	void SetTarget();
	void Clear(D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));

	void SaveTexture(wstring file);

private:
	ID3D11Texture2D* texture;
	ID3D11RenderTargetView* renderView;

	ID3D11ShaderResourceView* resourceView;
};