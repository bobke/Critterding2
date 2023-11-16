#include "be_entity_mousepicker.h"
#include "kernel/be_entity_core_types.h"
#include "be_entity_physics_entity.h"
#include "physicsmodel_rigid.h"
#include "be_entity_physicsworld.h"

	BMousePicker::BMousePicker() : 
	  m_constraint(0)
	, m_picking_distance(0.0f)
	, m_do_attach(false)
	{
		setProcessing();
	}

	void BMousePicker::construct()
	{
		auto source = addChild( "source", new BEntity() );
		m_source_x = source->addChild( "x", new BEntity_float() );
		m_source_y = source->addChild( "y", new BEntity_float() );
		m_source_z = source->addChild( "z", new BEntity_float() );

		auto target = addChild( "target", new BEntity() );
		m_target_x = target->addChild( "x", new BEntity_float() );
		m_target_y = target->addChild( "y", new BEntity_float() );
		m_target_z = target->addChild( "z", new BEntity_float() );
		
		m_grabbed_entity = addChild( "grabbed_entity", new BEntity_reference() );
	}	

	void BMousePicker::process()
	{
			if ( m_do_attach )
			{
				auto raycaster = parent()->getChild("raycaster", 1);
				if ( raycaster )
				{
					auto hit_entity = raycaster->getChild("hit_entity", 1);
					if ( hit_entity && hit_entity->get_reference() != 0 )
					{
						std::cout << "hitentity parent " << hit_entity->get_reference()->parent()->parent()->parent()->name() << std::endl;
						std::cout << "mousepicker parent " << parent()->parent()->parent()->name() << std::endl;
						
						auto physics_world = dynamic_cast<BPhysicsWorld*>( parent() ) ;
						if ( physics_world )
						{
							auto btbody = dynamic_cast<BPhysicsEntity*>( hit_entity->get_reference() )->getPhysicsComponent()->getBody();
							if (btbody)
							{
								btbody->setActivationState(DISABLE_DEACTIVATION);
								std::cout << "btbody weight : " << btbody->getInvMass () << std::endl;
								
								std::cout << "btbody userpointer : " << static_cast<BEntity*>(btbody->getUserPointer())->name() << std::endl;
								

								auto hit_position = raycaster->getChild("hit_position", 1);
								btVector3 attachPosition = btVector3( hit_position->getChild("x", 1)->get_float(), hit_position->getChild("y", 1)->get_float(), hit_position->getChild("z", 1)->get_float() );
								btVector3 localPivot = btbody->getCenterOfMassTransform().inverse() * attachPosition;

								std::cout << "attachPosition: x: " << attachPosition.x() << " y: " << attachPosition.y() << " z: " << attachPosition.z() << std::endl;
								std::cout << "localPivot: x: " << localPivot.x() << " y: " << localPivot.y() << " z: " << localPivot.z() << std::endl;

								// create constraint and add it to bulletworld
								m_constraint = new btPoint2PointConstraint( *btbody, localPivot );
								m_constraint->m_setting.m_impulseClamp = 100.f;
								m_constraint->m_setting.m_tau = 0.9f;
			
								physics_world->m_physics_world->addConstraint( m_constraint );
			
								btVector3 rayFrom = btVector3( m_source_x->get_float(), m_source_y->get_float(), m_source_z->get_float() );
								m_picking_distance = (attachPosition - rayFrom).length();
			
								m_grabbed_entity->set( hit_entity->get_reference() );

							}
						}
					}
				}

				m_do_attach = false;
			}
		
		
		if ( m_constraint != 0 )
		{
			btVector3 rayFrom = btVector3( m_source_x->get_float(), m_source_y->get_float(), m_source_z->get_float() );
			btVector3 rayDirection = btVector3( m_target_x->get_float(), m_target_y->get_float(), m_target_z->get_float() );

			if ( rayFrom != m_previous_rayFrom || rayDirection != m_previous_rayDirection )
			{
				// MOVE
				btVector3 dir = ( rayFrom + rayDirection );
				dir.normalize();
				m_constraint->setPivotB( (dir * m_picking_distance) + rayFrom);

				m_previous_rayFrom = rayFrom;
				m_previous_rayDirection = rayDirection;
			}
		}
	}

	bool BMousePicker::set( const Bbool& value )
	{
		// ATTACH
		if ( value )
		{
			m_do_attach = true;
			return true;
		}

		// DETACH
		else if ( m_constraint != 0 )
		{
			auto raycaster = parent()->getChild("raycaster", 1);
			if ( raycaster )
			{
				auto physics_world = dynamic_cast<BPhysicsWorld*>( parent()) ;
				if ( physics_world )
				{
					physics_world->m_physics_world->removeConstraint( m_constraint );
					delete m_constraint;
					m_constraint = 0;
  
					m_grabbed_entity->set( (BEntity*)0 );
  
					return true;
				}
			}
		}

		return false;
	}

	bool BMousePicker::removeGrabbedEntity( BEntity* to_remove )
	{
		if ( m_constraint != 0 )
		{
			if ( to_remove == m_grabbed_entity->get_reference() )
			{
				// std::cout << "removing connection" << std::endl;
				return set( false );
			}
		}
		return false;
	}
