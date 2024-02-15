#include "critter_system.h"
#include "kernel/be_entity_core_types.h"
// #include "species_system.h"
#include "plugins/be_plugin_bullet/be_entity_mousepicker.h"
// #include <iostream>
 
	void CdCritterSystem::construct()
	{
		m_command_buffer = getCommandBuffer();
		auto settings = addChild( "settings", new BEntity() );

		// BRAINZ SYSTEM
			m_brain_system = addChild( "brain_system", "BrainSystem" );

		// BODY SYSTEM
			auto body_system = addChild( "body_system", "CdBodySystem" );
			m_body_system_unit_container = body_system->getChild("unit_container", 1);
			// m_body_system = addChild( "body_system", "CdBodySystem" );

		// // SO MOVE THIS UP THE TREE, HAVE A set("register" entity*) in visionsystem, then register it in plugin.cpp
		// // VISION SYSTEM
		// 	auto vision_system = addChild( "vision_system", "CdVisionSystem" );
		// 	addChild("SDLSwapBuffers", "SDLSwapBuffers");

		// // SPECIES SYSTEM
		// 	m_species_system = new CdSpeciesSystem();
		// 	addChild( "species_system", m_species_system );

		// UNIT CONTAINER
			m_unit_container = addChild( "unit_container", new BEntity() );
		
		// // REGISTER UNIT CONTAINER IN VISION SYSTEM
		// 	vision_system->set("register_container", m_unit_container);
		
		// SETTINGS
		m_minimum_number_of_units = settings->addChild( "minimum_number_of_units", new BEntity_uint() );
		m_maximum_age = settings->addChild( "maximum_age", new BEntity_uint() );
		m_intitial_energy = settings->addChild( "intitial_energy", new BEntity_float() );
		m_procreate_minimum_energy = settings->addChild( "procreate_minimum_energy ", new BEntity_float() );
		
		auto dropzone = settings->addChild( "dropzone", new BEntity() );
		m_dropzone_position_x = dropzone->addChild( "position_x", new BEntity_float() );
		m_dropzone_position_y = dropzone->addChild( "position_y", new BEntity_float() );
		m_dropzone_position_z = dropzone->addChild( "position_z", new BEntity_float() );
		m_dropzone_size_x = dropzone->addChild( "size_x", new BEntity_float() );
		m_dropzone_size_y = dropzone->addChild( "size_y", new BEntity_float() );
		m_dropzone_size_z = dropzone->addChild( "size_z", new BEntity_float() );
		
		m_minimum_number_of_units->set( Buint(20) );
		m_intitial_energy->set( Bfloat(1500.0f) );
		m_procreate_minimum_energy->set( Bfloat(2501.0f) );
		m_maximum_age->set( Buint(18000) );
		m_dropzone_position_x->set( Bfloat(-100.0f) );
		m_dropzone_position_y->set( Bfloat(-18.0f) );
		m_dropzone_position_z->set( Bfloat(-170.0f) );
		m_dropzone_size_x->set( Bfloat(200.0f) );
		m_dropzone_size_y->set( Bfloat(1.5f) );
		m_dropzone_size_z->set( Bfloat(140.0f) );

		// m_minimum_number_of_units->set( Buint(1) );
		// m_intitial_energy->set( Bfloat(1500.0f) );
		// m_procreate_minimum_energy->set( Bfloat(2501.0f) );
		// m_maximum_age->set( Buint(16000000) );
		// m_dropzone_position_x->set( Bfloat(-90.0f) );
		// m_dropzone_position_y->set( Bfloat(-18.0f) );
		// m_dropzone_position_z->set( Bfloat(-190.0f) );
		// m_dropzone_size_x->set( Bfloat(180.0f) );
		// m_dropzone_size_y->set( Bfloat(1.0f) );
		// m_dropzone_size_z->set( Bfloat(180.0f) );
		
		m_insert_frame_interval = settings->addChild( "insert_frame_interval", new BEntity_uint() );
		m_insert_frame_interval->set( (Buint)20 );

		m_copy_random_position = settings->addChild( "copy_random_position", new BEntity_bool() );
		m_copy_random_position->set( false );
		
		m_mouse_picker = 0;
		auto ext = parent()->getChild("external_mousepicker", 1);
		if ( ext )
			m_mouse_picker = dynamic_cast<BMousePicker*>( ext->get_reference() );

		m_collisions = 0;
	}
	
	void CdCritterSystem::process()
	{
		// // GIVE SPECIES SPECIES, FIXME this is a fix for a manually loaded critter
		// 	// pick the last entity from m_unit_container
		// 	auto it = m_unit_container->children().rbegin();
		// 	if ( it != m_unit_container->children().rend() )
		// 	{
		// 		// if it doesn't have a species_reference, create a new species
		// 		auto species_reference = (*it)->getChild("species_reference", 1);
		// 		if ( !species_reference )
		// 		{
		// 			// species
		// 			m_species_system->addNewSpecies( (*it) );
		// 		}
		// 	}
		
		// AGE ALL UNITS WITH A DAY, COUNT UP ALL ENERGY FROM UNITS (FIXME ACCOUNT FOR CRITTERS, MAKE GLOBAL VARIABLE FOR TOTAL ENERGY)
			float total_energy_in_entities(0.0f);
			for_all_children_of( m_unit_container )
			{
				auto critter_unit = dynamic_cast<CdCritter*>( *child );
				if ( critter_unit )
				{
					critter_unit->setAge( 1+critter_unit->age() );
					total_energy_in_entities += critter_unit->energy();
					// critter_unit->m_always_firing_input->onUpdate();
				}
			}

		// INSERT NEW RANDOM CRITTER, only check every 100 frames
			if ( m_minimum_number_of_units->get_uint() > 0 && (++m_framecount == m_insert_frame_interval->get_uint() || m_insert_frame_interval->get_uint() == 0 ) )
			{
				// std::cout << "new random critter" << std::endl;
				m_framecount = 0;
				if ( m_unit_container->numChildren() < m_minimum_number_of_units->get_uint() )
				{
					auto cmd_insert = m_command_buffer->addChild( "pass_command", new BEntity_reference() );
					cmd_insert->set(this);
					auto command = cmd_insert->addChild( "command", new BEntity_string() );
					command->set("insert_critter");

					// PREVENT FURTHER ACTIONS IN THIS FRAME
						return;
				}
			}

		// DIE FROM OLD AGE OR ENERGY DEPLETION
		{
			for_all_children_of2( m_unit_container )
			{
				auto critter_unit = dynamic_cast<CdCritter*>( *child2 );
				if ( critter_unit )
				{
					// reached max age or energy is depleted
					if ( critter_unit->age() >= m_maximum_age->get_uint() || critter_unit->energy() <= 0.0f )
					{
						removeCritter( *child2 );
						
						// PREVENT FURTHER ACTIONS IN THIS FRAME
							return; 
					}
				}
			}
		}

		// PROCREATE
// 		if ( 1 == 1 )
		{
			static Buint t_highest(0);
			
			for_all_children_of2( m_unit_container )
			{
				auto critter_unit = dynamic_cast<CdCritter*>( *child2 );
				if ( critter_unit )
				{
					// energy is enough
					if ( critter_unit->energy() >= m_procreate_minimum_energy->get_float() )
					{
						auto procreate = critter_unit->getChild( "motor_neurons", 1)->getChild( "procreate", 1);
						
						// FIXME SHOULD THIS BE IsFiring? TURNS OUT THIS ARE FLOATS and not motor neurons
						if ( procreate->get_float() != 0.0f )
						// if ( dynamic_cast<BNeuron*>(procreate)->m_firing->get_bool() )
						// if ( procreate->get_reference()->getChild("firing", 1)->get_bool() )
						{
							procreate->set( 0.0f );
							critter_unit->setEnergy( critter_unit->energy() / 2 );

							auto cmd_procreate = m_command_buffer->addChild( "pass_command", new BEntity_reference() );
							cmd_procreate->set(this);
							auto command = cmd_procreate->addChild( "command", new BEntity_string() );
							command->set("procreate_critter");
							command->addChild( "entity", new BEntity_reference() )->set( critter_unit );
							
							// std::cout << "COPYING CRITTER: " << critter_unit->id() << " done" << std::endl << std::endl;
							// PREVENT FURTHER ACTIONS IN THIS FRAME
								return; 
						}
					}
				}
			}
		}
	}

	// bool CdCritterSystem::set( const char* value )
	bool CdCritterSystem::set( const Bstring& id, BEntity* value )
	{
		if ( id == std::string("insert_critter") )
		{
					auto critter_unit = new CdCritter();
					m_unit_container->addChild( "critter_unit", critter_unit );
					critter_unit->setEnergy( m_intitial_energy->get_float() );

					// BODY
						// auto newBody = body_unit_system->addChild( "body", new BBody() );
						auto newBody = m_body_system_unit_container->addChild( "body", new BEntity() );
						auto fixed_1 = newBody->addChild( "body_fixed1", "BodyFixed1" );

						critter_unit->m_transform_shortcut = fixed_1->getChild("bodyparts", 1)->getChild("external_bodypart_physics", 1)->get_reference()->getChild("transform", 1);
						
						// auto fixed_1 = body_unit_system->addChild( "body_fixed1", "BodyFixed1" );
						
						// auto fixed_1 = newBody->addChild( "body_fixed1", new BEntity() );

						// BodyFixed1Maker m;
						// m.make( fixed_1 );
						
							
						// REFERENCE TO EXTERNAL CHILD
							critter_unit->addChild( "external_body", new BEntity_external() )->set( newBody );

					// BRAIN
						critter_unit->m_brain = m_brain_system->getChild( "unit_container", 1)->addChild( "brain", "Brain" );
					
						// OUTPUTS
						// reference body constraints as brain outputs
						auto outputs = critter_unit->m_brain->getChild( "outputs", 1 );
						auto constraints_ref = outputs->addChild( "bullet_constraints", new BEntity_reference() );
						auto constraints = fixed_1->getChild( "constraints", 1 );
						constraints_ref->set( constraints );
						
						// motor neurons
						// eat
						auto motor_neurons = critter_unit->addChild( "motor_neurons", new BEntity() );
						auto motor_neuron_eat = motor_neurons->addChild( "eat",new BEntity_float() );
						auto motor_neuron_procreate = motor_neurons->addChild( "procreate",new BEntity_float() );

						auto motor_neurons_ref = outputs->addChild( "motor_neurons_ref", new BEntity_reference() );
						motor_neurons_ref->set( motor_neurons );
						
						// INPUTS
							auto inputs = critter_unit->m_brain->getChild( "inputs", 1 );

							// ALWAYS FIRING NEURON
								// critter_unit->m_always_firing_input = inputs->addChild( "always_firing_input", new BEntity_float() );

							// CONSTRAINTS
								for_all_children_of3( constraints )
								{
									auto constraint_angle_input = inputs->addChild( "constraint_angle", new BEntity_float() );
									auto angle = (*child3)->get_reference()->getChild("angle", 1);
									if ( angle )
									{
										if ( constraint_angle_input )
										{
											// std::cout << "connecting" << std::endl;
											angle->connectServerServer( constraint_angle_input );
										}
										else
										{
											std::cout << "error: constraint_angle not found" << std::endl;
										}
									}
									else
									{
										std::cout << "error: angle not found" << std::endl;
									}
								}

							// VISION
								unsigned int retinasize = 8;
								do_times( retinasize*retinasize )
								{
									inputs->addChild( "vision_value_R", new BEntity_float() );
									inputs->addChild( "vision_value_G", new BEntity_float() );
									inputs->addChild( "vision_value_B", new BEntity_float() );
									inputs->addChild( "vision_value_A", new BEntity_float() );
								}

					
						critter_unit->m_brain = m_brain_system->getChildCustom( critter_unit->m_brain, "new" );

						// REFERENCE TO EXTERNAL CHILD
							critter_unit->addChild( "external_brain", new BEntity_external() )->set( critter_unit->m_brain );

					// // // SPECIES
					// 	m_species_system->addNewSpecies( critter_unit );

			return true;
		}

		if ( id == std::string("procreate_critter") )
		{
			auto critter_unit = dynamic_cast<CdCritter*>( value->getChild("entity", 1)->get_reference() );
			// std::cout << "ad: " << critter_unit->getChild( "adam_distance", 1 )->get_uint() << " total:" << m_unit_container->numChildren()+1 << "(h: " << t_highest << ")" << ": " << critter_unit->id() << std::endl;
			std::cout << "ad: " << critter_unit->getChild( "adam_distance", 1 )->get_uint() << " total:" << m_unit_container->numChildren()+1 << ": " << critter_unit->id() << std::endl;

			// critter_unit->setEnergy( critter_unit->energy() / 2 );
			// critter_unit->setAge( Buint(0) );
			
			// COPY CRITTER
				auto critter_new = m_entityCopy.copyEntity( critter_unit );
				critter_new->getChild( "age", 1 )->set( Buint(0) );
				// critter_new->getChild( "energy", 1 )->set( Buint(0) );

			// CHANGE POSITION to above parent
			if ( !m_copy_random_position->get_bool() )
			{
				auto bodyparts_old = critter_unit->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );
				auto bodyparts_new = critter_new->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );
				
				const auto& children_old = bodyparts_old->children();
				auto old_child = children_old.begin();
				// for ( auto child2(children_vector2.begin()); child2 != children_vector2.end(); ++child2 )

				for_all_children_of3( bodyparts_new )
				{
					auto t = (*child3)->get_reference()->getChild( "transform", 1 );
					auto oldt = (*old_child)->get_reference()->getChild( "transform", 1 );
					if ( t )
					{
						// std::cout << "changing position" << std::endl;
						t->set("position_x", oldt->get_float("position_x"));
						t->set("position_y", oldt->get_float("position_y") + 0.75f);
						t->set("position_z", oldt->get_float("position_z"));
					}
					old_child++;
				}
			}

			// MUTATE CRITTER BRAIN

				// get brain from critter
				BEntity* brain_new;
				for_all_children_of3( critter_new )
				{
					if ( (*child3)->name() == "external_brain" )
					{
						if ( (*child3)->get_reference()->name() == "brain" )
						{
							brain_new = (*child3)->get_reference();
						}
					}
				}
				
				// ACTUAL MUTATE
				if ( m_brain_system->set( "mutate", brain_new ) )
				{
					auto ad = critter_new->getChild( "adam_distance", 1 );
					ad->set( ad->get_uint() + 1 );
// 					
// 					m_species_system->addNewSpecies( critter_new );
				}
				// else
				// {
				// 	m_species_system->copySpecies( critter_unit, critter_new );
				// }

			return true;
		}

		// if ( id == std::string("migrate_critter") )
		// {
		// 	return true;
		// }
		return false;
	}

	void CdCritterSystem::removeCritter( BEntity* entity, bool force_direct_deletion )
	{
		// shortcut
			auto bodyparts = entity->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );

		// COLLISIONS
			while ( removeFromCollisions( bodyparts ) ) {;}

		// MOUSEPICKER, loop all bodyparts
			if ( m_mouse_picker )
			{
				for_all_children_of3( bodyparts )
				{
					m_mouse_picker->removeGrabbedEntity( (*child3)->get_reference() );
				}
			}

		// // SPECIES
		// 	m_species_system->removeFromSpecies( entity );

		// ACTUAL REMOVAL
			if ( force_direct_deletion )
			{
				m_unit_container->removeChild( entity );
			}
			else
			{
				auto cmd_rm = m_command_buffer->addChild( "remove", new BEntity_reference() );
				cmd_rm->set( entity );
			}
	}

	bool CdCritterSystem::removeFromCollisions( BEntity* to_remove_list )
	{
		if ( m_collisions == 0 )
		{
			m_collisions = parent()->getChild("physicsworld", 1)->getChild("collisions", 1);
		}

		for_all_children_of( m_collisions )
		{
			auto e1 = (*child)->getChild( "entity1", 1 )->get_reference();
			auto e2 = (*child)->getChild( "entity2", 1 )->get_reference();
			
			// check if e1 is a bodypart belonging to to_remove
			for_all_children_of2( to_remove_list )
			{
				if ( e1 == (*child2)->get_reference() || e2 == (*child2)->get_reference() )
				{
					// std::cout << "removing critter" << std::endl;
					m_collisions->removeChild( *child );
					// std::cout << "removing critter done" << std::endl;
					return true;
				}
			}
		}
		return false;
	}

	void CdCritter::construct()
	{
		m_age = addChild( "age", new BEntity_uint() );
		m_energy = addChild( "energy", new BEntity_float() );
		addChild( "adam_distance", new BEntity_uint() )->set( Buint(0) );
		
		m_brain_inputs = 0;
		m_physics_component = 0;
	}
	
	
	
	
