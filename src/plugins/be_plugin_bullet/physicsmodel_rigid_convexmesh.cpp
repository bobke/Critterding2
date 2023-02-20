#include "physicsmodel_rigid_convexmesh.h"
// #include "kernel/be_profiler.h"

BodypartRigidConvexmesh::BodypartRigidConvexmesh(const btVector3* const gVertices, const unsigned int numVertices, int* const gVIndices, const unsigned int numVIndices, const btTransform& transform ,const float weight, const float linearDamping, const float angularDamping  )
{
    // BE_FUNCTION_PROFILER;
    m_triangleIndexVertexArray.reset( new btTriangleIndexVertexArray(numVIndices/3, gVIndices, 3*sizeof(int), numVertices/3,(btScalar*) &gVertices[0].x(),3*sizeof(btScalar)) );
    m_convexTriangleMeshShape.reset(new btConvexTriangleMeshShape(m_triangleIndexVertexArray.get(),true));
    m_shapeHull.reset(new btShapeHull(m_convexTriangleMeshShape.get()));
    btScalar margin = m_convexTriangleMeshShape->getMargin();
    m_shapeHull->buildHull(margin);
    m_shape.reset(new btConvexHullShape((btScalar*)m_shapeHull->getVertexPointer(),m_shapeHull->numVertices()));
//     generalSetup( weight, transform, linearDamping, angularDamping );
}

BodypartRigidConvexmesh::BodypartRigidConvexmesh(boost::shared_ptr<BeGeometry> model, const btTransform& transform ,const float weight, const float linearDamping, const float angularDamping, const btVector3& scaling  )
{
    // BE_FUNCTION_PROFILER;
    m_triangleIndexVertexArray.reset( new btTriangleIndexVertexArray( model->getNumberVIndices()/3, model->indices.get(), 3*sizeof(int), model->getNumberVertices()/3, (btScalar*) model->vertices.get(), 3*sizeof(btScalar) ) );
    m_convexTriangleMeshShape.reset(new btConvexTriangleMeshShape(m_triangleIndexVertexArray.get(),true));
    m_shapeHull.reset(new btShapeHull(m_convexTriangleMeshShape.get()));
    btScalar margin = m_convexTriangleMeshShape->getMargin();
    m_shapeHull->buildHull(margin);
    m_shape.reset(new btConvexHullShape((btScalar*)m_shapeHull->getVertexPointer(),m_shapeHull->numVertices()));
	m_shape->setLocalScaling(scaling);
	
		m_shape->calculateLocalInertia( weight, m_localInertia );
	
//     generalSetup( weight, transform, linearDamping, angularDamping );
}
 
