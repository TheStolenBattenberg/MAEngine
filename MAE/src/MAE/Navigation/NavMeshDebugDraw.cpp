#include <MAE/Navigation/NavMeshDebugDraw.h>
#include <MAE/Main.h>

void NavMeshDebugDraw::depthMask(bool state)
{
	mainObj->d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, (DWORD)state);
}

void NavMeshDebugDraw::texture(bool state)
{
}

void NavMeshDebugDraw::begin(duDebugDrawPrimitives prim, float size)
{
	Vertices.clear();
	DrawType = prim;
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
	mainObj->d3ddev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	int count = 0;
	D3DPRIMITIVETYPE D3DDrawType;
	switch (DrawType)
	{
	case DU_DRAW_POINTS:
		D3DDrawType = D3DPT_POINTLIST;
		count = 1;
		break;
	case DU_DRAW_LINES:
		D3DDrawType = D3DPT_LINELIST;
		count = 2;
		break;
	case DU_DRAW_TRIS:
		D3DDrawType = D3DPT_TRIANGLELIST;
		count = 3;
		break;
	};
	mainObj->d3ddev->DrawPrimitiveUP(D3DDrawType, Vertices.size() / count, &Vertices[0], sizeof(DVertex));
}
