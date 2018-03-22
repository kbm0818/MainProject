#include "../stdafx.h"
#include "TopView.h"

TopView::TopView()
	: Camera(), height(500)
{
	D3DXVECTOR2 radian = D3DXVECTOR2(90, 0);
	radian *= (float)D3DX_PI / 180.0f;

	RotateValue(radian);

	UpdateView();
}

TopView::~TopView()
{

}

void TopView::Rotate(D3DXVECTOR2 rotate)
{
}

void TopView::RotateUp()
{
}

void TopView::RotateDown()
{
}

void TopView::RotateLeft()
{
}

void TopView::RotateRight()
{

}

void TopView::UpdateView()
{
	//position.y = height;

	D3DXVECTOR3 at = position + D3DXVECTOR3(0, -1, 0);
	D3DXMatrixLookAtLH(&view, &position, &at, &D3DXVECTOR3(0, 0, 1));

	D3DXMATRIX S;
	D3DXMatrixScaling(&S, 10, 10, 10);
	view = S * view;
}