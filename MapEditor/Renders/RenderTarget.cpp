#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = (UINT)desc.Width;
	textureDesc.Height = (UINT)desc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

	HRESULT hr;
	hr = D3D::GetDevice()->CreateTexture2D(&textureDesc, NULL, &texture);
	assert(SUCCEEDED(hr));


	D3D11_RENDER_TARGET_VIEW_DESC renderDesc;
	ZeroMemory(&renderDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	renderDesc.Format = textureDesc.Format;
	renderDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderDesc.Texture2D.MipSlice = 0;

	hr = D3D::GetDevice()->CreateRenderTargetView(texture, &renderDesc, &renderView);
	assert(SUCCEEDED(hr));


	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	viewDesc.Format = textureDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;

	hr = D3D::GetDevice()->CreateShaderResourceView(texture, &viewDesc, &resourceView);
	assert(SUCCEEDED(hr));
}

RenderTarget::~RenderTarget()
{
	SAFE_RELEASE(resourceView);
	SAFE_RELEASE(renderView);
	SAFE_RELEASE(texture);
}

void RenderTarget::SetTarget()
{
	D3D::GetDC()->OMSetRenderTargets(1, &renderView, BackBuffer::Get()->GetDepthView());
}

void RenderTarget::Clear(D3DXCOLOR color)
{
	D3D::GetDC()->ClearRenderTargetView(renderView, color);
	D3D::GetDC()->ClearDepthStencilView
	(
		BackBuffer::Get()->GetDepthView()
		, D3D11_CLEAR_DEPTH, 1, 0
	);
}

void RenderTarget::SaveTexture(wstring file)
{
	HRESULT hr;
	hr = D3DX11SaveTextureToFile
	(
		D3D::GetDC(), texture, D3DX11_IFF_PNG, file.c_str()
	);
	assert(SUCCEEDED(hr));
}
