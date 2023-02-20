#include "physicsmodel_rigid_box.h"

BodypartRigidBox::BodypartRigidBox(const btVector3& dimensions, const btTransform& transform ,const float weight, const float linearDamping, const float angularDamping )
// : BeRigidBody( ownerWorld )
{
	m_shape.reset(new btBoxShape( dimensions ));
	m_shape->calculateLocalInertia( weight, m_localInertia );

// 	generalSetup( weight, transform, linearDamping, angularDamping );
}

BodypartRigidBox::~BodypartRigidBox()
{
}
 
