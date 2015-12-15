#include "MABullet.h"
#include "Main.h"

DLLEXPORT double MAB_ShapeCreateBox(double XSize, double YSize, double ZSize)
{
	btCollisionShape* shape = new btBoxShape(btVector3((btScalar)XSize, (btScalar)YSize, (btScalar)ZSize));
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreateSphere(double Radius)
{
	btCollisionShape* shape = new btSphereShape((btScalar)Radius);
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreateCapsule(double Radius, double Height, double UpAxis)
{
	int axis = (int)UpAxis;
	btCollisionShape* shape;
	if (axis == 0) shape = new btCapsuleShapeX((btScalar)Radius, (btScalar)Height);
	else if (axis == 1) shape = new btCapsuleShape((btScalar)Radius, (btScalar)Height);
	else shape = new btCapsuleShapeZ((btScalar)Radius, (btScalar)Height);
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreatePlane(double NX, double NY, double NZ, double Distance)
{
	btCollisionShape* shape = new btStaticPlaneShape(btVector3((btScalar)NX, (btScalar)NY, (btScalar)NZ), (btScalar)Distance);
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreateCylinder(double Radius, double Height, double UpAxis)
{
	int axis = (int)UpAxis;
	btCollisionShape* shape;
	if (axis == 0) shape = new btCylinderShapeX(btVector3((btScalar)Height, (btScalar)Radius, (btScalar)Radius));
	else if (axis == 1) shape = new btCylinderShape(btVector3((btScalar)Radius, (btScalar)Height, (btScalar)Radius));
	else shape = new btCylinderShapeZ(btVector3((btScalar)Radius, (btScalar)Radius, (btScalar)Height));
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreateCone(double Radius, double Height, double UpAxis)
{
	int axis = (int)UpAxis;
	btCollisionShape* shape;
	if (axis == 0) shape = new btConeShapeX((btScalar)Radius, (btScalar)Height);
	else if (axis == 1) shape = new btConeShape((btScalar)Radius, (btScalar)Height);
	else shape = new btConeShapeZ((btScalar)Radius, (btScalar)Height);
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreateCompound()
{
	btCollisionShape* shape = new btCompoundShape(true);
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeAddChild(double ParentID, double ChildID, double X, double Y, double Z, double RX, double RY, double RZ, double RW)
{
	btCompoundShape* parent = dynamic_cast<btCompoundShape*>(G.getShape(ParentID));
	if(!parent) return -1;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	parent->addChildShape(trans, G.getShape(ChildID));
	return parent->getNumChildShapes()-1;
}

DLLEXPORT double MAB_ShapeRemoveChild(double ParentID, double ChildIndex)
{
	btCompoundShape* parent = dynamic_cast<btCompoundShape*>(G.getShape(ParentID));
	if (!parent) return 0;
	parent->removeChildShapeByIndex((int)ChildIndex);
	return 1;
}

DLLEXPORT double MAB_ShapeUpdateChildTransform(double ParentID, double ChildIndex, double X, double Y, double Z, double RX, double RY, double RZ, double RW)
{
	btCompoundShape* parent = dynamic_cast<btCompoundShape*>(G.getShape(ParentID));
	if (!parent) return 0;
	btTransform trans;
	trans.setOrigin(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	trans.setRotation(btQuaternion((btScalar)RX, (btScalar)RY, (btScalar)RZ, (btScalar)RW));
	parent->updateChildTransform((int)ChildIndex, trans, true);
	return 1;
}

DLLEXPORT double MAB_ShapeCreateTriMesh(float* Buffer, double NumTriangles, double Convex, double WeldingThreshold)
{
	btTriangleMesh* mesh = new btTriangleMesh(false, false);
	mesh->m_weldingThreshold = (btScalar)WeldingThreshold;
	for (int i = 0; i < NumTriangles; i++)
	{
		int index = i * 9;
		btVector3 v1 = btVector3(Buffer[index + 0], Buffer[index + 1], Buffer[index + 2]);
		btVector3 v2 = btVector3(Buffer[index + 3], Buffer[index + 4], Buffer[index + 5]);
		btVector3 v3 = btVector3(Buffer[index + 6], Buffer[index + 7], Buffer[index + 8]);
		mesh->addTriangle(v1, v2, v3, (WeldingThreshold > 0));
	}
	btCollisionShape* shape;
	if (Convex)
	{
		shape = new btConvexTriangleMeshShape(mesh, true);
		delete mesh;
	}
	else {
		shape = new btBvhTriangleMeshShape(mesh, true, true);
	}
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeCreateConvexHull(float* Buffer, double NumVertices)
{
	btCollisionShape* shape = new btConvexHullShape(Buffer, (int)NumVertices, 12);
	return G.addShape(shape);
}

DLLEXPORT double MAB_ShapeDestroy(double ShapeID, double DestroyChildShapes)
{
	if (!G.shapeExists(ShapeID)) return 0;
	btCollisionShape* shape = G.getShape(ShapeID);
	if (DestroyChildShapes) {
		btCompoundShape* compound = dynamic_cast<btCompoundShape*>(shape);
		if (compound) {
			for (int i = 0; i < compound->getNumChildShapes(); i++) {
				G.Shapes.erase(compound->getChildShape(i)->getUserIndex());
				btBvhTriangleMeshShape* trimesh = dynamic_cast<btBvhTriangleMeshShape*>(compound->getChildShape(i));
				if (trimesh) delete trimesh->getMeshInterface();
				delete compound->getChildShape(i);			
			}
		}
	}
	btBvhTriangleMeshShape* trimesh = dynamic_cast<btBvhTriangleMeshShape*>(shape);
	if (trimesh) delete trimesh->getMeshInterface();
	int ID = (int)ShapeID;
	delete G.Shapes[ID];
	G.Shapes.erase(ID);
	return 1;
}

DLLEXPORT double MAB_ShapeDestroyAll()
{
	if (G.Shapes.size() == 0) return 0;
	for (auto i : G.Shapes)
	{
		btBvhTriangleMeshShape* trimesh = dynamic_cast<btBvhTriangleMeshShape*>(i.second);
		if (trimesh) delete trimesh->getMeshInterface();
		delete i.second;
	}
	G.Shapes.clear();
	return 1;
}

DLLEXPORT double MAB_ShapeSetMargin(double ShapeID, double Margin)
{
	G.getShape(ShapeID)->setMargin((btScalar)Margin);
	return 1;
}

DLLEXPORT double MAB_ShapeSetScaling(double ShapeID, double X, double Y, double Z)
{
	G.getShape(ShapeID)->setLocalScaling(btVector3((btScalar)X, (btScalar)Y, (btScalar)Z));
	return 1;
}
