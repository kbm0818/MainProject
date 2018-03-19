#include "stdafx.h"
#include "FirstPerson.h"

FirstPerson::FirstPerson(float moveSpeed, float rotationSpeed)
	: moveSpeed(moveSpeed), rotationSpeed(rotationSpeed)
{

}

FirstPerson::~FirstPerson()
{

}

void FirstPerson::Update()
{
	D3DXVECTOR3 position;
	GetPosition(&position);
	{
		if (Keyboard::Get()->Press('W'))
			position += D3DXVECTOR3(0, 0, 1) * moveSpeed * Time::Delta();
		else if (Keyboard::Get()->Press('S'))
			position += D3DXVECTOR3(0, 0, -1) * moveSpeed * Time::Delta();

		if (Keyboard::Get()->Press('A'))
			position += D3DXVECTOR3(-1, 0, 0) * moveSpeed * Time::Delta();
		else if (Keyboard::Get()->Press('D'))
			position += D3DXVECTOR3(1, 0, 0) * moveSpeed * Time::Delta();

		if (Keyboard::Get()->Press('E'))
			position += D3DXVECTOR3(0, 1, 0) * moveSpeed * Time::Delta();
		else if (Keyboard::Get()->Press('Q'))
			position += D3DXVECTOR3(0, -1, 0) * moveSpeed * Time::Delta();
	}
	SetPosition(position);

	
	D3DXVECTOR2 rotation;
	GetRotation(&rotation);
	{
		if (Mouse::Get()->Press(1))
		{
			D3DXVECTOR3 move = Mouse::Get()->GetMoveValue();

			rotation.x += move.y * Time::Delta() * rotationSpeed;
			rotation.y += move.x * Time::Delta() * rotationSpeed;
		}
	}
	SetRotation(rotation);
}
