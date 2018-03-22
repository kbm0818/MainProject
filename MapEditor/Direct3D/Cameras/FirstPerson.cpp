#include "../stdafx.h"
#include "FirstPerson.h"

FirstPerson::FirstPerson()
	: Camera()
{
	UpdateView();
}

FirstPerson::~FirstPerson()
{
	
}

void FirstPerson::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
}