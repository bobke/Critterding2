#ifndef PHYSICSMODELRIGIDTRIANGLEMESH_H_INCLUDED
#define PHYSICSMODELRIGIDTRIANGLEMESH_H_INCLUDED

#include "physicsmodel_rigid.h"
#include "be_geometry.h"

class BodypartRigidTrianglemesh : public BeRigidBody
{
	public:
		BodypartRigidTrianglemesh(const btVector3* const gVertices, const unsigned int numVertices, int* const gVIndices, const unsigned int numVIndices, const btTransform& transform, const float weight, const float linearDamping, const float angularDamping );
		BodypartRigidTrianglemesh(boost::shared_ptr<BeGeometry> model, const btTransform& transform, const float weight, const float linearDamping, const float angularDamping, const btVector3& scaling );
 		virtual ~BodypartRigidTrianglemesh() {};
	private:
		boost::shared_ptr<btTriangleIndexVertexArray> m_triangleIndexVertexArray;
// 		virtual void reScale( const btVector3& scale );
};

#endif
 
