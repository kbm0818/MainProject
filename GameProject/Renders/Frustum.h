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
	D3DXVECTOR3	m_vtx[8];	/// 프러스텀을 구성할 정점 8개
	D3DXVECTOR3	m_vPos;		/// 현재 카메라의 월드좌표
	D3DXPLANE	m_plane[6];	/// 프러스텀을 구성하는 6개의 평면

	float radius;
};