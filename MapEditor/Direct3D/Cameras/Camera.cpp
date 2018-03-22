#include "../stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(0, 0, 0)
	, forward(0, 0, 1), right(1, 0, 0), up(0, 1, 0)
	, rotate(0, 0), translationSpeed(100), rotationSpeed(2.5f)
{
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	buffer = new CameraBuffer();
}

Camera::~Camera()
{
	SAFE_DELETE(buffer);
}

void Camera::GetRay(D3DXVECTOR3 * origin, D3DXVECTOR3 * direction, D3DXMATRIX& world)
{
	D3DXVECTOR3 mouse = Mouse::Get()->GetPosition();

	D3DDesc info;
	D3D::GetDesc(&info);

	D3DXVECTOR2 point;
	point.x = ((2.0f * mouse.x) / info.width) - 1.0f;
	point.y = (((2.0f * mouse.y) / info.height) - 1.0f) * -1.0f;

	point.x = point.x / projection._11;
	point.y = point.y / projection._22;

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);

	D3DXVECTOR3 dir;
	dir.x = (point.x * invView._11) + (point.y * invView._21) + invView._31;
	dir.y = (point.x * invView._12) + (point.y * invView._22) + invView._32;
	dir.z = (point.x * invView._13) + (point.y * invView._23) + invView._33;

	D3DXVec3Normalize(&dir, &dir);

	D3DXMATRIX invWorldMatrix;
	D3DXMatrixInverse(&invWorldMatrix, NULL, &world);

	D3DXVECTOR3 rayOrigin, rayDirection;
	D3DXVec3TransformCoord(&rayOrigin, &position, &invWorldMatrix);
	D3DXVec3TransformNormal(&rayDirection, &dir, &invWorldMatrix);	

																	
	D3DXVec3Normalize(&rayDirection, &rayDirection);

	*origin = position;
	*direction = dir;
}

void Camera::GetRay(float px, float py, D3DXVECTOR3 * origin, D3DXVECTOR3 * direction, D3DXMATRIX & world)
{
	D3DXVECTOR3 mouse = D3DXVECTOR3(px, py, 0.0f);

	D3DDesc info;
	D3D::GetDesc(&info);

	D3DXVECTOR2 point;
	point.x = ((2.0f * mouse.x) / info.width) - 1.0f;
	point.y = (((2.0f * mouse.y) / info.height) - 1.0f) * -1.0f;

	point.x = point.x / projection._11;
	point.y = point.y / projection._22;

	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);

	D3DXVECTOR3 dir;
	dir.x = (point.x * invView._11) + (point.y * invView._21) + invView._31;
	dir.y = (point.x * invView._12) + (point.y * invView._22) + invView._32;
	dir.z = (point.x * invView._13) + (point.y * invView._23) + invView._33;

	D3DXVec3Normalize(&dir, &dir);

	D3DXMATRIX invWorldMatrix;
	D3DXMatrixInverse(&invWorldMatrix, NULL, &world);

	D3DXVECTOR3 rayOrigin, rayDirection;
	D3DXVec3TransformCoord(&rayOrigin, &position, &invWorldMatrix);
	D3DXVec3TransformNormal(&rayDirection, &dir, &invWorldMatrix);


	D3DXVec3Normalize(&rayDirection, &rayDirection);

	*origin = position;
	*direction = dir;
}

void Camera::SetPerspective(float width, float height, float fov, float zn, float zf)
{
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	float aspect = width / height;
	D3DXMatrixPerspectiveFovLH(&projection, fov, aspect, zn, zf);
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float zn, float zf)
{
	SetOrthographic(0, 0, left, right, bottom, top, zn, zf);
}

void Camera::SetOrthographic(float leftTopX, float leftTopY, float left, float right, float bottom, float top, float zn, float zf)
{
	float width = max(left, right) - min(left, right);
	float height = max(bottom, top) - min(bottom, top);

	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = leftTopX;
	viewport.TopLeftY = leftTopY;

	D3DXMatrixOrthoOffCenterLH(&projection, left, right, bottom, top, zn, zf);
}

void Camera::Move(D3DXVECTOR3 translation)
{
	position += translation * Time::Delta();
	UpdateView();
}

void Camera::MoveLeft()
{
	Move(-right * translationSpeed);
}

void Camera::MoveRight()
{
	Move(right * translationSpeed);
}

void Camera::MoveUp()
{
	Move(up * translationSpeed);
}

void Camera::MoveDown()
{
	Move(-up * translationSpeed);
}

void Camera::MoveForward()
{
	Move(forward * translationSpeed);
}

void Camera::MoveBackward()
{
	Move(-forward * translationSpeed);
}

void Camera::Rotate(D3DXVECTOR2 rotate)
{
	this->rotate.x += rotate.x * Time::Delta() * rotationSpeed;
	this->rotate.y += rotate.y * Time::Delta() * rotationSpeed;

	UpdateRotation();
	UpdateView();
}

void Camera::RotateUp()
{
	Rotate(D3DXVECTOR2(1, 0));
}

void Camera::RotateDown()
{
	Rotate(D3DXVECTOR2(-1, 0));
}

void Camera::RotateLeft()
{
	Rotate(D3DXVECTOR2(0, 1));
}

void Camera::RotateRight()
{
	Rotate(D3DXVECTOR2(0, -1));
}

void Camera::RotateValue(D3DXVECTOR2 radian)
{
	this->rotate = radian;

	UpdateRotation();
	UpdateView();
}

void Camera::UpdateRotation()
{
	D3DXMATRIX x, y;
	D3DXMatrixRotationX(&x, rotate.x);
	D3DXMatrixRotationY(&y, rotate.y);

	rotation = x * y;

	D3DXVec3TransformCoord(&forward, &D3DXVECTOR3(0, 0, 1), &rotation);
	D3DXVec3TransformCoord(&right, &D3DXVECTOR3(1, 0, 0), &rotation);
	D3DXVec3TransformCoord(&up, &D3DXVECTOR3(0, 1, 0), &rotation);
}