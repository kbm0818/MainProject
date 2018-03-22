#include "../stdafx.h"
#include "BackBuffer.h"

BackBuffer* BackBuffer::instance = NULL;

BackBuffer * BackBuffer::Get()
{
	assert(instance != NULL);

	return instance;
}

void BackBuffer::Create()
{
	assert(instance == NULL);

	instance = new BackBuffer();
}

void BackBuffer::Delete()
{
	SAFE_DELETE(instance);
}

void BackBuffer::SetTarget()
{
	D3D::GetDC()->OMSetRenderTargets(1, &renderView, depthView);
}

BackBuffer::BackBuffer()
{
	CreateTexture();
	CreateRenderTarget();
	CreateView();
}

BackBuffer::~BackBuffer()
{
	SAFE_RELEASE(depthView);
	SAFE_RELEASE(renderView);
	SAFE_RELEASE(texture);
}

void BackBuffer::CreateTexture()
{
	D3DDesc d3dDesc;
	D3D::GetDesc(&d3dDesc);

	D3D11_TEXTURE2D_DESC desc = { 0 };
	desc.Width = (UINT)d3dDesc.width;
	desc.Height = (UINT)d3dDesc.height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	HRESULT hr;
	hr = D3D::GetDevice()->CreateTexture2D(&desc, NULL, &texture);
	assert(SUCCEEDED(hr));
}

void BackBuffer::CreateRenderTarget()
{
	ID3D11Texture2D* backbufferPointer;
	HRESULT hr = D3D::GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backbufferPointer);
	assert(SUCCEEDED(hr));

	hr = D3D::GetDevice()->CreateRenderTargetView(backbufferPointer, NULL, &renderView);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(backbufferPointer);
}

void BackBuffer::CreateView()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	HRESULT hr = D3D::GetDevice()->CreateDepthStencilView(texture, &desc, &depthView);
	assert(SUCCEEDED(hr));

	D3D::GetDC()->OMSetRenderTargets(1, &renderView, depthView);
}
