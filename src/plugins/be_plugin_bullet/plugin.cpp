#include "plugin.h"
#include "be_entity_physicsworld.h"
#include "be_entity_physics_entity.h"
#include "be_entity_constraint_hinge.h"
#include "be_entity_raycast.h"
#include "be_entity_mousepicker.h"
#include "physicsmodel_rigid.h"

// ---- FACTORIES
	enum CLASS
	{
		  PLUGIN_INFO
		, PHYSICSWORLD
		, PHYSICSENTITY
		, PHYSICSENTITY_CUBE
		, CONSTRAINT_HINGE
		, BULLET_RAYCAST
		, BULLET_MOUSEPICKER
		, BULLET_TRANSFORM
		, BULLET_TRANSFORM_EMITTER
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::PHYSICSWORLD, "PhysicsWorld" );
					i.addClass( parent, CLASS::PHYSICSENTITY, "PhysicsEntity" );
					i.addClass( parent, CLASS::PHYSICSENTITY_CUBE, "PhysicsEntity_Cube" );
					i.addClass( parent, CLASS::CONSTRAINT_HINGE, "Constraint_Hinge" );
					i.addClass( parent, CLASS::BULLET_RAYCAST, "Bullet_Raycast" );
					i.addClass( parent, CLASS::BULLET_MOUSEPICKER, "Bullet_MousePicker" );
					i.addClass( parent, CLASS::BULLET_TRANSFORM, "Bullet_Transform" );
					i.addClass( parent, CLASS::BULLET_TRANSFORM_EMITTER, "Bullet_Transform_Emitter" );
				return 0;
			}

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::PHYSICSWORLD )
					i = new BPhysicsWorld();
				else if ( type == CLASS::PHYSICSENTITY )
					i = new BPhysicsEntityTriangleMesh();
				else if ( type == CLASS::PHYSICSENTITY_CUBE )
					i = new BPhysicsEntityCube();
				else if ( type == CLASS::CONSTRAINT_HINGE )
					i = new BConstraintHinge();
				else if ( type == CLASS::BULLET_RAYCAST )
					i = new BRaycast();
				else if ( type == CLASS::BULLET_MOUSEPICKER )
					i = new BMousePicker();
				else if ( type == CLASS::BULLET_TRANSFORM )
					i = new BBulletTransform();
				else if ( type == CLASS::BULLET_TRANSFORM_EMITTER )
					i = new transformEmitter();
				
			
				
				
// 				else if ( type == CLASS::TASK_SORT )
// 					i = new taskSort();

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
		delete p;
	}
