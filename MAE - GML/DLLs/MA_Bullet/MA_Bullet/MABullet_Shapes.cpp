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

DLLEXPORT MAB_ShapeCreateCapsule(double Radius, double Height, double UpAxis)
{
	int axis = (int)UpAxis;
	btCollisionShape* shape;
	if (axis == 0) shape = new btCapsuleShapeX((btScalar)Radius, (btScalar)Height);
	else if (axis == 1) shape = new btCapsuleShape((btScalar)Radius, (btScalar)Height);
	else shape = new btCapsuleShapeZ((btScalar)Radius, (btScalar)Height);
	return G.addShape(shape);
}

DLLEXPORT MAB_ShapeCreatePlane(double NX, double NY, double NZ, double Distance)
{
	btCollisionShape* shape = new btStaticPlaneShape(btVector3((btScalar)NX, (btScalar)NY, (btScalar)NZ), (btScalar)Distance);
	return G.addShape(shape);
}

DLLEXPORT MAB_ShapeCreateCylinder(double Radius, double Height, double UpAxis)
{
	int axis = (int)UpAxis;
	btCollisionShape* shape;
	if (axis == 0) shape = new btCylinderShapeX(btVector3((btScalar)Height, (btScalar)Radius, (btScalar)Radius));
	else if (axis == 1) shape = new btCylinderShape(btVector3((btScalar)Radius, (btScalar)Height, (btScalar)Radius));
	else shape = new btCylinderShapeZ(btVector3((btScalar)Radius, (btScalar)Radius, (btScalar)Height));
	return G.addShape(shape);
}

DLLEXPORT MAB_ShapeCreateCone(double Radius, double Height, double UpAxis)
{
	int axis = (int)UpAxis;
	btCollisionShape* shape;
	if (axis == 0) shape = new btConeShapeX((btScalar)Radius, (btScalar)Height);
	else if (axis == 1) shape = new btConeShape((btScalar)Radius, (btScalar)Height);
	else shape = new btConeShapeZ((btScalar)Radius, (btScalar)Height);
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


