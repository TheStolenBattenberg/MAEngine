#pragma once

#include "MABullet.h"
#include "d3d9.h"
#include "d3dx9.h"
#include <iostream>
#include <vector>

struct Vertex
{
	D3DXVECTOR3 position;
	D3DCOLOR color;

	Vertex(float x, float y, float z, D3DCOLOR color) : position(x, y, z), color(color){}
};

class MABulletDebugDraw : public btIDebugDraw
{
	int m_debugMode;
	LPDIRECT3DDEVICE9 d3ddev;

	std::vector<Vertex> Vertices;

public:
	bool update = false;

	MABulletDebugDraw(LPDIRECT3DDEVICE9 device)
	{
		d3ddev = device; 
		m_debugMode = btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE | btIDebugDraw::DBG_DrawContactPoints;
	};

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
	virtual void draw3dText(const btVector3& location, const char* textString) { return; }

	virtual void reportErrorWarning(const char* warningString) { std::cout << warningString << std::endl; }

	virtual void setDebugMode(int debugMode) { m_debugMode = debugMode; }
	virtual int  getDebugMode() const { return m_debugMode; }

	void debugDraw();

};
