#pragma once
#include "Camera.h"

class FirstPerson : public Camera
{
public:

private:
	friend class CameraFactory;

	void UpdateView();

	FirstPerson();
	~FirstPerson();


};