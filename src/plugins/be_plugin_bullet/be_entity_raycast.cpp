#include "kernel/be_entity_core_types.h"
#include "be_entity_raycast.h"
#include "be_entity_physicsworld.h"
// #include <iostream>

	void BRaycast::construct()
	{
		m_hit_entity = addChild( "hit_entity", new BEntity_reference() );

		auto hit_position = addChild( "hit_position", new BEntity() );
		m_hit_position_x = hit_position->addChild( "x", new BEntity_float() );
		m_hit_position_y = hit_position->addChild( "y", new BEntity_float() );
		m_hit_position_z = hit_position->addChild( "z", new BEntity_float() );

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

				if (resultCallback.hasHit())
				{
					auto e1 = static_cast<BEntity*>(resultCallback.m_collisionObject->getUserPointer());
					if ( e1 )
					{
						// std::cout << e1->name() << std::endl;
						m_hit_entity->set( e1 );
						m_hit_position_x->set( resultCallback.m_hitPointWorld.x() );
						m_hit_position_y->set( resultCallback.m_hitPointWorld.y() );
						m_hit_position_z->set( resultCallback.m_hitPointWorld.z() );
						return;
					}
				}
			}
		}

		m_hit_entity->set( (BEntity*)0 );
	}
