#pragma once
#include "Camera.h"

class TopView : public Camera
{
public:
	void SetHeight(float height)
	{
		this->height = height;
	}
	
private:
	virtual void Rotate(D3DXVECTOR2 rotate);
	virtual void RotateUp();
	virtual void RotateDown();
	virtual void RotateLeft();
	virtual void RotateRight();

	friend class CameraFactory;
	void UpdateView();

	TopView();
	~TopView();

	float height;
};