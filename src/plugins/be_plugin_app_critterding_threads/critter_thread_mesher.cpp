#include "critter_thread_mesher.h"
#include "kernel/be_entity_core_types.h"
#include "plugins/be_plugin_app_critterding/critter_system.h"
// #include "critter_system.h"
#include <iostream>

	void CdCritterThreadMesher::construct()
	{
		setFps(1);

		m_critter_system = dynamic_cast<CdCritterSystem*>( parent()->getChild("critter_system", 1) );
		m_critter_unit_container = m_critter_system->getChild("unit_container", 1);

		m_x_active = addChild( "x_active", new BEntity_bool() );
		m_x_active->set( false );
		m_x_border = addChild( "x_border", new BEntity_float() );
		m_x_direction_is_right = addChild( "x_direction_is_right", new BEntity_bool() );
		m_x_target = addChild( "x_target", new BEntity_reference() );

		m_z_active = addChild( "z_active", new BEntity_bool() );
		m_z_active->set( false );
		m_z_border = addChild( "z_border", new BEntity_float() );
		m_z_direction_is_down = addChild( "z_direction_is_down", new BEntity_bool() );
		m_z_target = addChild( "z_target", new BEntity_reference() );
	} 

	void CdCritterThreadMesher::process()
	{
		// MOVE CRITTERS HAVING GONE PASSED BORDER
		for_all_children_of( m_critter_unit_container )
		{
			auto critter = dynamic_cast<CdCritter*>( *child );
			if ( critter )
			{
				if ( critter->m_transform_shortcut == 0 )
				{
					critter->m_transform_shortcut = (*child)->getChild("external_body", 1)->get_reference()->getChild("body_fixed1", 1)->getChild("bodyparts", 1)->getChild("external_bodypart_physics", 1)->get_reference()->getChild("transform", 1);
				}

				if ( m_x_active->get_bool() )
				{
					if ( m_x_direction_is_right->get_bool() )
					{
						if ( critter->m_transform_shortcut->getChild("position_x", 1)->get_float() > m_x_border->get_float() )
						{
							migrate( *child, m_x_target->get_reference() );
						}
					}
					else
					{
						if ( critter->m_transform_shortcut->getChild("position_x", 1)->get_float() < m_x_border->get_float() )
						{
							migrate( *child, m_x_target->get_reference() );
						}
					}
				}
				
				if ( m_z_active->get_bool() )
				{
					if ( m_z_direction_is_down->get_bool() )
					{
						if ( critter->m_transform_shortcut->getChild("position_z", 1)->get_float() > m_z_border->get_float() )
						{
							migrate( *child, m_z_target->get_reference() );
						}
					}
					else
					{
						if ( critter->m_transform_shortcut->getChild("position_z", 1)->get_float() < m_z_border->get_float() )
						{
							migrate( *child, m_z_target->get_reference() );
						}
					}
				}
			}
			
		}
	}

	void CdCritterThreadMesher::migrate( BEntity* entity, BEntity* target )
	{
		std::cout << "migrating critter " << entity->id() << " from " << entity->parent()->parent()->parent()->parent()->name() << " to " << target->parent()->parent()->parent()->name() << std::endl;

		m_mutex.lock();
		auto cmd_procreate = getCommandBuffer()->addChild( "pass_command", new BEntity_reference() );
		cmd_procreate->set(this);
		auto command = cmd_procreate->addChild( "command", new BEntity_string() );
		command->set("migrate_critter");
		command->addChild( "entity", new BEntity_reference() )->set( entity );
		command->addChild( "target", new BEntity_reference() )->set( target );
		m_mutex.unlock();
	}
	
	// bool CdCritterSystem::set( const char* value )
	bool CdCritterThreadMesher::set( const Bstring& id, BEntity* value )
	{
		if ( id == std::string("migrate_critter") ) //  wait, it's this one, or it's the one ine critter_system?
		{
			// COPY CRITTER
			auto entity = value->getChild("entity")->get_reference();
			auto critter_new = dynamic_cast<CdCritter*>( m_entityCopy.copyEntity( entity, value->getChild("target")->get_reference() ) );

			// FIXME should be inherent?
			// AGE, ENERGY, AD
				auto age = critter_new->getChild( "age", 1 );
				auto oldage = entity->getChild( "age", 1 );
				age->set(oldage->get_uint());
				auto energy = critter_new->getChild( "energy", 1 );
				auto oldenergy = entity->getChild( "energy", 1 );
				energy->set(oldenergy->get_float());
				auto ad = critter_new->getChild( "adam_distance", 1 );
				auto oldad = entity->getChild( "adam_distance", 1 );
				ad->set(oldad->get_uint());


			// POSITION BODYPARTS
				auto bodyparts_old = entity->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );
				critter_new->m_bodyparts_shortcut = critter_new->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );

				const auto& children_old = bodyparts_old->children();
				auto old_child = children_old.begin();

				for_all_children_of3( critter_new->m_bodyparts_shortcut )
				{
					auto t = (*child3)->get_reference()->getChild( "transform", 1 );
					auto oldt = (*old_child)->get_reference()->getChild( "transform", 1 );
					if ( t )
					{
						// std::cout << "changing position" << std::endl;
						t->set("position_x", oldt->get_float("position_x"));
						t->set("position_y", oldt->get_float("position_y"));
						t->set("position_z", oldt->get_float("position_z"));
						t->set("rotation_euler_x", oldt->get_float("rotation_euler_x"));
						t->set("rotation_euler_y", oldt->get_float("rotation_euler_y"));
						t->set("rotation_euler_z", oldt->get_float("rotation_euler_z"));
					}
					old_child++;
				}

			// REMOVE MIGRATED CRITTER
			m_critter_system->removeCritter( entity );
			return true;
			
		}
		return false;
	}
