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

DLLEXPORT MAB_ShapeCreateCompound()
{
	btCollisionShape* shape = new btCompoundShape(true);
	return G.addShape(shape);
}

DLLEXPORT MAB_ShapeAddChild(double ParentID, double ChildID, double X, double Y, double Z, double RX, double RY, double RZ, double RW)
{
	btCompoundShape* parent = dynamic_cast<btCompoundShape*>(G.getShape(ParentID));
	if(!parent) return -1;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	parent->addChildShape(trans, G.getShape(ChildID));
	return parent->getNumChildShapes()-1;
}

DLLEXPORT MAB_ShapeRemoveChild(double ParentID, double ChildIndex)
{
	btCompoundShape* parent = dynamic_cast<btCompoundShape*>(G.getShape(ParentID));
	if (!parent) return 0;
	parent->removeChildShapeByIndex((int)ChildIndex);
	return 1;
}

DLLEXPORT MAB_ShapeUpdateChildTransform(double ParentID, double ChildIndex, double X, double Y, double Z, double RX, double RY, double RZ, double RW)
{
	btCompoundShape* parent = dynamic_cast<btCompoundShape*>(G.getShape(ParentID));
	if (!parent) return 0;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	parent->updateChildTransform((int)ChildIndex, trans, true);
	return 1;
}

DLLEXPORT MAB_ShapeDestroy(double ShapeID, double DestroyChildShapes)
{
	if (!G.shapeExists(ShapeID)) return 0;
	if (DestroyChildShapes) {
		btCompoundShape* compound = dynamic_cast<btCompoundShape*>(G.getShape(ShapeID));
		if (compound) {
			for (int i = 0; i < compound->getNumChildShapes(); i++) {
				G.Shapes.erase(compound->getChildShape(i)->getUserIndex());
				delete compound->getChildShape(i);			
			}
		}
	}
	int ID = (int)ShapeID;
	delete G.Shapes[ID];
	G.Shapes.erase(ID);
	return 1;
}

DLLEXPORT MAB_ShapeDestroyAll()
{
	if (G.Shapes.size() == 0) return 0;
	for (auto i : G.Shapes)
	{
		delete i.second;
	}
	G.Shapes.clear();
	return 1;
}

DLLEXPORT MAB_ShapeSetMargin(double ShapeID, double Margin)
{
	G.getShape(ShapeID)->setMargin((btScalar)Margin);
	return 1;
}

DLLEXPORT MAB_ShapeSetScaling(double ShapeID, double X, double Y, double Z)
{
	G.getShape(ShapeID)->setLocalScaling(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}
