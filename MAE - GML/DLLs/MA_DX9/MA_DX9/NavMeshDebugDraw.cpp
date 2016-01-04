#include "NavMeshDebugDraw.h"
#include <iostream>

void NavMeshDebugDraw::depthMask(bool state)
{
	// TODO
}

void NavMeshDebugDraw::texture(bool state)
{
	// Ignore texture for now
}

void NavMeshDebugDraw::begin(duDebugDrawPrimitives prim, float size)
{
	Vertices.clear();

	switch (prim)
	{
	case DU_DRAW_POINTS:
		DrawType = D3DPT_POINTLIST;
		break;
	case DU_DRAW_LINES:
		DrawType = D3DPT_LINELIST;
		break;
	case DU_DRAW_TRIS:
		DrawType = D3DPT_TRIANGLELIST;
		break;
	case DU_DRAW_QUADS:
		std::cout << "This happened" << std::endl;
		// ???
		break;
	};
}

void NavMeshDebugDraw::vertex(const float* pos, unsigned int color)
{
	Vertices.push_back(DVertex(-pos[0], pos[2], pos[1], D3DXCOLOR(color)));
}

void NavMeshDebugDraw::vertex(const float x, const float y, const float z, unsigned int color)
{
	Vertices.push_back(DVertex(-x, z, y, D3DXCOLOR(color)));
}

void NavMeshDebugDraw::vertex(const float* pos, unsigned int color, const float* uv)
{
	Vertices.push_back(DVertex(-pos[0], pos[2], pos[1], D3DXCOLOR(color)));
}

void NavMeshDebugDraw::vertex(const float x, const float y, const float z, unsigned int color, const float u, const float v)
{
	Vertices.push_back(DVertex(-x, z, y, D3DXCOLOR(color)));
}

void NavMeshDebugDraw::end()
{
	mamain->d3ddev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	int count = 1;
	if (DrawType == D3DPT_LINELIST) count = 2;
	else if (DrawType == D3DPT_TRIANGLELIST) count = 3;
	mamain->d3ddev->DrawPrimitiveUP(DrawType, Vertices.size() / count, &Vertices[0], sizeof(DVertex));
}
