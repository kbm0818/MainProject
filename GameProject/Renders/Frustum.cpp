#include "stdafx.h"
#include "Frustum.h"

Frustum::Frustum()
{
	ZeroMemory(m_vtx, sizeof(m_vtx[0]) * 8);
	ZeroMemory(m_plane, sizeof(m_plane[0]) * 6);
	radius = 5.0f;
}

Frustum::Frustum(float radius)
	: radius(radius)
{
	ZeroMemory(m_vtx, sizeof(m_vtx[0]) * 8);
	ZeroMemory(m_plane, sizeof(m_plane[0]) * 6);
}

Frustum::~Frustum()
{
}

bool Frustum::Create(D3DXMATRIXA16 * pmatViewProj)
{
	int				i;
	D3DXMATRIXA16	matInv;

	m_vtx[0].x = -1.0f;	m_vtx[0].y = -1.0f;	m_vtx[0].z = 0.0f;
	m_vtx[1].x = 1.0f;	m_vtx[1].y = -1.0f;	m_vtx[1].z = 0.0f;
	m_vtx[2].x = 1.0f;	m_vtx[2].y = -1.0f;	m_vtx[2].z = 1.0f;
	m_vtx[3].x = -1.0f;	m_vtx[3].y = -1.0f;	m_vtx[3].z = 1.0f;
	m_vtx[4].x = -1.0f;	m_vtx[4].y = 1.0f;	m_vtx[4].z = 0.0f;
	m_vtx[5].x = 1.0f;	m_vtx[5].y = 1.0f;	m_vtx[5].z = 0.0f;
	m_vtx[6].x = 1.0f;	m_vtx[6].y = 1.0f;	m_vtx[6].z = 1.0f;
	m_vtx[7].x = -1.0f;	m_vtx[7].y = 1.0f;	m_vtx[7].z = 1.0f;

	D3DXMatrixInverse(&matInv, NULL, pmatViewProj);

	for (i = 0; i < 8; i++)
		D3DXVec3TransformCoord(&m_vtx[i], &m_vtx[i], &matInv);

	m_vPos = (m_vtx[0] + m_vtx[5]) / 2.0f;

	//	D3DXPlaneFromPoints(&m_plane[0], m_vtx+4, m_vtx+7, m_vtx+6);	// 상 평면(top)
	//	D3DXPlaneFromPoints(&m_plane[1], m_vtx  , m_vtx+1, m_vtx+2);	// 하 평면(bottom)
	//	D3DXPlaneFromPoints(&m_plane[2], m_vtx  , m_vtx+4, m_vtx+5);	// 근 평면(near)
	D3DXPlaneFromPoints(&m_plane[3], m_vtx + 2, m_vtx + 6, m_vtx + 7);	// 원 평면(far)
	D3DXPlaneFromPoints(&m_plane[4], m_vtx, m_vtx + 3, m_vtx + 7);	// 좌 평면(left)
	D3DXPlaneFromPoints(&m_plane[5], m_vtx + 1, m_vtx + 5, m_vtx + 6);	// 우 평면(right)

	return true;
}

bool Frustum::IsIn(D3DXVECTOR3 * pv)
{
	float fDist = D3DXPlaneDotCoord(&m_plane[3], pv);
	if (fDist > radius) return false;	
	fDist = D3DXPlaneDotCoord(&m_plane[4], pv);
	if (fDist > radius) return false;
	fDist = D3DXPlaneDotCoord(&m_plane[5], pv);
	if (fDist > radius) return false;

	return true;
}

bool Frustum::IsInSphere(D3DXVECTOR3 * pv, float radius)
{
	float fDist = D3DXPlaneDotCoord(&m_plane[3], pv);
	if (fDist > radius) return false;
	fDist = D3DXPlaneDotCoord(&m_plane[4], pv);
	if (fDist > radius) return false;
	fDist = D3DXPlaneDotCoord(&m_plane[5], pv);
	if (fDist > radius) return false;

	return true;
}