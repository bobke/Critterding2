#include "kernel/be_entity_core_types.h"
#include "be_entity_raycast.h"
#include "be_entity_physicsworld.h"
#include <iostream>

	void BRaycast::construct()
	{
		auto source = addChild( "source", new BEntity() );
		m_source_x = source->addChild( "x", new BEntity_float() );
		m_source_y = source->addChild( "y", new BEntity_float() );
		m_source_z = source->addChild( "z", new BEntity_float() );

		auto target = addChild( "target", new BEntity() );
		m_target_x = target->addChild( "x", new BEntity_float() );
		m_target_y = target->addChild( "y", new BEntity_float() );
		m_target_z = target->addChild( "z", new BEntity_float() );
		
	}

	void BRaycast::process()
	{
		// std::cout << "raycast: " << std::endl;
		
		btVector3 rayFrom( m_source_x->get_float(), m_source_y->get_float(), m_source_z->get_float() );
		btVector3 rayTo( m_target_x->get_float(), m_target_y->get_float(), m_target_z->get_float() );
		
		if ( rayFrom != rayTo )
		{
			auto physics_world_entity = dynamic_cast<BPhysicsWorld*>( parent()) ;
			if ( physics_world_entity )
			{
				btCollisionWorld::ClosestRayResultCallback resultCallback( rayFrom, rayTo );
				physics_world_entity->m_physics_world->rayTest( rayFrom, rayTo, resultCallback );
				// btDynWorld->rayTest( rayFrom, rayTo, resultCallback );

				if (resultCallback.hasHit())
				{

					auto e1 = static_cast<BEntity*>(resultCallback.m_collisionObject->getUserPointer());
					if ( e1 )
					{
						// std::cout << "raycast hit: " << e1->name() << std::endl;
					}

					// btRigidBody* b1 = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
					// btRigidBody* b2 = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);
					// auto e1 = static_cast<BEntity*>(b1->getUserPointer());
					// auto e2 = static_cast<BEntity*>(b2->getUserPointer());					
					
					// result.hit = true;
					// result.hitBody = resultCallback.m_collisionObject;
					// result.hitPosition = resultCallback.m_hitPointWorld;
				}
			}
		}
	}
	
	// castResult BRaycast::cast(const btVector3& rayFrom, const btVector3& rayTo)
	// {
 // 
	// 	return result;
	// }
