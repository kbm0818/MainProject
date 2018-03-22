#pragma once
#include "CameraBuffer.h"

class Camera
{
public:
	void GetPosition(D3DXVECTOR3* vec)
	{
		*vec = position;
	}

	void SetPosition(float x, float y)
	{
		SetPosition(&D3DXVECTOR3(x, y, 0.0f));
	}

	void SetPosition(float x, float y, float z)
	{
		SetPosition(&D3DXVECTOR3(x, y, z));
	}

	void SetPosition(D3DXVECTOR3* vec)
	{
		position = *vec;

		UpdateView();
	}

	void SetVSBuffer(D3DXMATRIX* world)
	{
		buffer->SetWorld(world);
		buffer->SetView(&view);
		buffer->SetProjection(&projection);

		buffer->SetVSBuffer(0);
		D3D::GetDC()->RSSetViewports(1, &viewport);
	}

	void GetRay(D3DXVECTOR3* origin, D3DXVECTOR3* direction, D3DXMATRIX& world);
	void GetRay(float px, float py, D3DXVECTOR3* origin, D3DXVECTOR3* direction, D3DXMATRIX& world);

	void SetPerspective(float width, float height, float fov, float zn, float zf);
	void SetOrthographic(float left, float right, float bottom, float top, float zn, float zf);
	void SetOrthographic(float leftTopX, float leftTopY, float left, float right, float bottom, float top, float zn, float zf);

	virtual void Move(D3DXVECTOR3 translation);
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveForward();
	virtual void MoveBackward();

	virtual void Rotate(D3DXVECTOR2 rotate);
	virtual void RotateUp();
	virtual void RotateDown();
	virtual void RotateLeft();
	virtual void RotateRight();
	virtual void RotateValue(D3DXVECTOR2 radian);
	
protected:
	friend class CameraFactory;

	virtual void UpdateRotation();
	virtual void UpdateView() = 0;

	Camera();
	virtual ~Camera();

	CameraBuffer* buffer;

	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	D3DXVECTOR3 position;
	float translationSpeed;

	D3DXVECTOR2 rotate;
	D3DXMATRIX rotation;
	float rotationSpeed;

	D3D11_VIEWPORT viewport;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};