#include "physicsmodel_rigid_trianglemesh.h"
// #include "kernel/be_profiler.h"
#include "BulletCollision/Gimpact/btGImpactShape.h"
// #include "be_entity_types.h"
// #include <iostream>

BodypartRigidTrianglemesh::BodypartRigidTrianglemesh(const btVector3* const gVertices, const unsigned int numVertices, int* const gVIndices, const unsigned int numVIndices, const btTransform& transform ,const float weight, const float linearDamping, const float angularDamping  )
 : BeRigidBody()
{
// 	BE_FUNCTION_PROFILER;
	m_triangleIndexVertexArray.reset( new btTriangleIndexVertexArray(numVIndices/3, gVIndices, 3*sizeof(int), numVertices/3,(btScalar*) &gVertices[0].x(),3*sizeof(btScalar)) );
	if ( weight > 0.0f )
	{
// 		std::cout << weight << " :: " << "btGImpactMeshShape" << std::endl;
		btGImpactMeshShape * tshape = new btGImpactMeshShape(m_triangleIndexVertexArray.get());
// 		tshape->setLocalScaling(btVector3(2.0f,1.0f,1.0f));
		tshape->calculateLocalInertia( weight, m_localInertia );
		tshape->updateBound();
		m_shape.reset(tshape);
	}
	else
	{
// 		std::cout << weight << " :: " << "btBvhTriangleMeshShape" << std::endl;
		m_shape.reset(new btBvhTriangleMeshShape(m_triangleIndexVertexArray.get(),true));
	}
// 	m_shape->setLocalScaling(btVector3(2.0f,1.0f,1.0f));
// 	generalSetup( weight, transform, linearDamping, angularDamping );
}

BodypartRigidTrianglemesh::BodypartRigidTrianglemesh(boost::shared_ptr<BeGeometry> model, const btTransform& transform ,const float weight, const float linearDamping, const float angularDamping, const btVector3& scaling )
 : BeRigidBody()
{
	
//     BE_FUNCTION_PROFILER;
//     m_triangleIndexVertexArray.reset( new btTriangleIndexVertexArray( model->getNumberVIndices()/3, model->indices.get(), 3*sizeof(int), model->getNumberVertices()/3, (btScalar*) model->vertices.get(), 3*sizeof(btScalar) ) );
//     m_convexTriangleMeshShape.reset(new btConvexTriangleMeshShape(m_triangleIndexVertexArray.get(),true));
//     m_shapeHull.reset(new btShapeHull(m_convexTriangleMeshShape.get()));
//     btScalar margin = m_convexTriangleMeshShape->getMargin();
//     m_shapeHull->buildHull(margin);
//     m_shape.reset(new btConvexHullShape((btScalar*)m_shapeHull->getVertexPointer(),m_shapeHull->numVertices()));
//     generalSetup( weight, transform, linearDamping, angularDamping );

// 	BE_FUNCTION_PROFILER;
	
// 	BETransform t(transform);
// 	std::stringstream to_post;
// 	to_post << "BodypartRigidTrianglemesh::BodypartRigidTrianglemesh: weight:" << weight << "'";
// 	t.postInvalid( to_post.str(), true );
	
// 	std::cout << "Vertices : " << model->getNumberVertices() << std::endl;
// 	exit(0);
	
	m_triangleIndexVertexArray.reset( new btTriangleIndexVertexArray( model->getNumberVIndices()/3, model->indices.get(), 3*sizeof(int), model->getNumberVertices()/3, (btScalar*) model->vertices.get(), 3*sizeof(btScalar) ) );
	if ( weight > 0.0f )
	{
// 		std::cout << weight << " :: " << "btGImpactMeshShape" << std::endl;
		btGImpactMeshShape * tshape = new btGImpactMeshShape(m_triangleIndexVertexArray.get());
		tshape->setLocalScaling(scaling);
		tshape->updateBound();
		
		tshape->calculateLocalInertia( weight, m_localInertia );
		
		// std::cout << " Local inertia : x: " << m_localInertia.x() << std::endl;
		// std::cout << " Local inertia : y: " << m_localInertia.y() << std::endl;
		// std::cout << " Local inertia : z: " << m_localInertia.z() << std::endl;
		
// 		tshape->postUpdate();
// 		tshape->postUpdate();
		m_shape.reset(tshape);
	}
	else
	{
// 		std::cout << weight << " :: " << "btBvhTriangleMeshShape" << std::endl;
		m_shape.reset(new btBvhTriangleMeshShape(m_triangleIndexVertexArray.get(),true));
		m_shape->setLocalScaling(scaling);
	}
// 	m_shape->setLocalScaling(btVector3(2.0f,1.0f,1.0f));
// 	generalSetup( weight, transform, linearDamping, angularDamping );
}


// BodypartRigidTrianglemesh::BodypartRigidTrianglemesh(boost::shared_ptr<BeGeometry> model, const btTransform& transform ,const float weight, const float linearDamping, const float angularDamping, const btVector3& scaling  )
//   : BeRigidBody()
// {
// 	BE_FUNCTION_PROFILER;
// 	m_triangleIndexVertexArray.reset( new btTriangleIndexVertexArray( model->getNumberVIndices()/3, model->indices.get(), 3*sizeof(int), model->getNumberVertices()/3, (btScalar*) model->vertices.get(), 3*sizeof(btScalar) ) );
//     if ( weight > 0.0f )
//     {
//         btGImpactMeshShape * tshape = new btGImpactMeshShape(m_triangleIndexVertexArray.get());
//         tshape->setLocalScaling(btVector3(1.f,1.f,1.f));
//         tshape->updateBound();
//         m_shape.reset(tshape);
//     }
//     else
// 	    m_shape.reset(new btBvhTriangleMeshShape(m_triangleIndexVertexArray.get(),true));
// // 	generalSetup( weight, transform, linearDamping, angularDamping );
// }



// void BodypartRigidTrianglemesh::reScale( const btVector3& scale )
// {
// 	std::cout << "scaling  " << "x : " << scale.x() << ", y : " << scale.y() << ", z : " << scale.z() << std::endl;
// 	m_shape->setLocalScaling(scale);
// 	btGImpactMeshShape* entity = dynamic_cast<btGImpactMeshShape*>(m_shape.get());
// 	if ( entity )
// 	{
// 		entity->updateBound();
// 	}
// }
 
