#include <MAE/Bullet/BulletDebugDraw.h>
#include <MAE/Main.h>
#include <MAE/Rendering/RendererImpl.h>

void MABulletDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	Vertices.push_back(Vertex(from.x(), from.y(), from.z(), D3DXCOLOR(fromColor.x(), fromColor.y(), fromColor.z(), 1.0f)));
	Vertices.push_back(Vertex(to.x(), to.y(), to.z(), D3DXCOLOR(toColor.x(), toColor.y(), toColor.z(), 1.0f)));
}

void MABulletDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	Vertices.push_back(Vertex(from.x(), from.y(), from.z(), D3DXCOLOR(color.x(), color.y(), color.z(), 1.0f)));
	Vertices.push_back(Vertex(to.x(), to.y(), to.z(), D3DXCOLOR(color.x(), color.y(), color.z(), 1.0f)));
}

void MABulletDebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	btVector3 from = PointOnB;
	btVector3 to = from + normalOnB;
	Vertices.push_back(Vertex(from.x(), from.y(), from.z(), D3DXCOLOR(color.x(), color.y(), color.z(), 1.0f)));
	Vertices.push_back(Vertex(to.x(), to.y(), to.z(), D3DXCOLOR(color.x(), color.y(), color.z(), 1.0f)));
}

void MABulletDebugDraw::debugDraw(Renderer* renderer)
{
	if (update)
	{
		Vertices.clear();
		mabullet.world->debugDrawWorld();
		update = false;
	}
	if (Vertices.size() > 1)
	{
		auto device = ((RendererImpl*) renderer)->getDevice();

		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->DrawPrimitiveUP(D3DPT_LINELIST, Vertices.size() / 2, &Vertices[0], sizeof(Vertex));
	}
}
