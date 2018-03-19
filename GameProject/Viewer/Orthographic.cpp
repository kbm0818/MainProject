#include "stdafx.h"
#include "Orthographic.h"

Orthographic::Orthographic(float left, float right, float bottom, float top, float zn, float zf)
{
	Set(left, right, bottom, top, zn, zf);
}

Orthographic::~Orthographic()
{
}

void Orthographic::GetMatrix(D3DXMATRIX * mat)
{
	memcpy(mat, &orthographic, sizeof(D3DXMATRIX));
}

void Orthographic::Set(float left, float right, float bottom, float top, float zn, float zf)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->zn = zn;
	this->zf = zf;

	D3DXMatrixOrthoOffCenterLH(&orthographic, left, right, bottom, top, zn, zf);
}