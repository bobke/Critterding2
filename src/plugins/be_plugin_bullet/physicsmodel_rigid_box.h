#ifndef PHYSICSMODELRIGIDBOX_H_INCLUDED
#define PHYSICSMODELRIGIDBOX_H_INCLUDED

#include "physicsmodel_rigid.h"

class BodypartRigidBox : public BeRigidBody
{
	public:
		BodypartRigidBox(const btVector3& dimensions, const btTransform& transform , const float weight, const float linearDamping, const float angularDamping );
		virtual ~BodypartRigidBox();
};
#endif
 
