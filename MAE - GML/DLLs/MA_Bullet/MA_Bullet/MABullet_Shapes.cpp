#include "MABullet.h"

DLLEXPORT MAB_ShapeCreateBox(double XSize, double YSize, double ZSize)
{
	btCollisionShape* shape = new btBoxShape(btVector3((btScalar)XSize, (btScalar)YSize, (btScalar)ZSize));
	return G.addShape(shape);
}

DLLEXPORT MAB_ShapeCreateSphere(double Radius)
{
	btCollisionShape* shape = new btSphereShape((btScalar)Radius);
	return G.addShape(shape);
}

DLLEXPORT MAB_ShapeDestroy(double ShapeID)
{
	int ID = (int)ShapeID;
	if (!G.shapeExists(ShapeID)) return 0;
	delete G.Shapes[ID];
	G.Shapes.erase(ID);
	return 1;
}
