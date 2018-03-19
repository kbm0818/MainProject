#pragma once

class Orthographic
{
public:
	Orthographic(float left, float right, float bottom, float top, float zn = 0.0f, float zf = 1.0f);
	~Orthographic();

	void GetMatrix(D3DXMATRIX* mat);
	void Set(float left, float right, float bottom, float top, float zn = 0.0f, float zf = 1.0f);

private:
	float left, right;
	float bottom, top;
	float zn, zf;

	D3DXMATRIX orthographic;
};