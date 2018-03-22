#pragma once

class Frustum
{
public:
	Frustum();
	Frustum(float radius);
	~Frustum();

	bool Create(D3DXMATRIXA16* pmatViewProj);

	bool IsIn(D3DXVECTOR3* pv);
	bool IsInSphere(D3DXVECTOR3* pv, float radius);

private:
	D3DXVECTOR3	m_vtx[8];	/// ���������� ������ ���� 8��
	D3DXVECTOR3	m_vPos;		/// ���� ī�޶��� ������ǥ
	D3DXPLANE	m_plane[6];	/// ���������� �����ϴ� 6���� ���

	float radius;
};