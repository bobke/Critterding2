#ifndef PHYSICSMODELRIGIDCONVEXMESH_H_INCLUDED
#define PHYSICSMODELRIGIDCONVEXMESH_H_INCLUDED

#include "physicsmodel_rigid.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
#include "be_geometry.h"

class BodypartRigidConvexmesh : public BeRigidBody
{
public:
    BodypartRigidConvexmesh(const btVector3* const gVertices, const unsigned int numVertices, int* const gVIndices, const unsigned int numVIndices, const btTransform& transform, const float weight, const float linearDamping, const float angularDamping );
    BodypartRigidConvexmesh(boost::shared_ptr<BeGeometry> model, const btTransform& transform, const float weight, const float linearDamping, const float angularDamping, const btVector3& scaling );
    virtual ~BodypartRigidConvexmesh() {};
private:
    boost::shared_ptr<btTriangleIndexVertexArray> m_triangleIndexVertexArray;
    boost::shared_ptr<btConvexTriangleMeshShape> m_convexTriangleMeshShape;
    boost::shared_ptr<btShapeHull> m_shapeHull;
};

#endif
 
