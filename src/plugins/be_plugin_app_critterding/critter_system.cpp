#include "critter_system.h"
#include "kernel/be_entity_core_types.h"
#include "species_system.h"
#include "body_system.h"
#include <iostream>
 
	void CdCritterSystem::construct()
	{
		auto settings = addChild( "settings", new BEntity() );

		// SPECIES SYSTEM
			m_species_system = new CdSpeciesSystem();
			addChild( "species_system", m_species_system );

		m_unit_container = addChild( "unit_container", new BEntity() );
		
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
		m_maximum_age->set( Buint(16000) );
		m_dropzone_position_x->set( Bfloat(-65.0f) );
		m_dropzone_position_y->set( Bfloat(-18.0f) );
		m_dropzone_position_z->set( Bfloat(-165.0f) );
		m_dropzone_size_x->set( Bfloat(130.0f) );
		m_dropzone_size_y->set( Bfloat(1.0f) );
		m_dropzone_size_z->set( Bfloat(130.0f) );

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
		m_insert_frame_interval->set( (Buint)500 );

		m_copy_random_position = settings->addChild( "copy_random_position", new BEntity_bool() );
		m_copy_random_position->set( false );
		
		m_collisions = parent()->getChild("physicsworld", 1)->getChild("collisions", 1);
	}
	
	void CdCritterSystem::process()
	{
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

		// LOAD CRITTER
		if ( 1 == 0 )
		{
			static unsigned int frame_counter( 0 );
			const unsigned int offset( 0 );
			if ( 
				++frame_counter == offset+1000
				|| frame_counter == offset+6000
				|| frame_counter == offset+7000
				|| frame_counter == offset+8000
				|| frame_counter == offset+9000
			)
			{
				m_entityLoad.loadEntity( m_unit_container );
				
				// pick the last entity from m_unit_container
				auto it = m_unit_container->children().rbegin();
				if ( it != m_unit_container->children().rend() )
				{
					// if it doesn't have a species_reference, create a new species
					auto species_reference = (*it)->getChild("species_reference", 1);
					if ( !species_reference )
					{
						// species
						m_species_system->addNewSpecies( (*it) );
					}
				}

				// frame_counter = 1001;
			}
		}
			
			
		// INSERT NEW RANDOM CRITTER, only check every 100 frames
			if ( m_minimum_number_of_units->get_uint() > 0 && (++m_framecount == m_insert_frame_interval->get_uint() || m_insert_frame_interval->get_uint() == 0 ) )
			{
				// std::cout << "new random critter" << std::endl;
				m_framecount = 0;
				if ( m_unit_container->numChildren() < m_minimum_number_of_units->get_uint() )
				{
					auto critter_unit = new CdCritter();
					m_unit_container->addChild( "critter_unit", critter_unit );
					critter_unit->setEnergy( m_intitial_energy->get_float() );

					// generate random body
					auto body_system = parent()->getChild( "body_system", 1 );
					auto body_unit_system = body_system->getChild("unit_container", 1);
					
					// auto newBody = body_unit_system->addChild( "body", new BBody() );
					auto newBody = body_unit_system->addChild( "body", new BEntity() );

					auto fixed_1 = newBody->addChild( "body_fixed1", "BodyFixed1" );
					// auto fixed_1 = newBody->addChild( "body_fixed1", new BEntity() );

					// BodyFixed1Maker m;
					// m.make( fixed_1 );
					
						
					// REFERENCE TO EXTERNAL CHILD
						critter_unit->addChild( "external_body", new BEntity_external() )->set( newBody );

					// generate random brain
					auto brain_system = parent()->getChild( "brain_system", 1 );

					critter_unit->m_brain = brain_system->getChild( "unit_container", 1)->addChild( "brain", "Brain" );

					// OUTPUTS
						// reference body constraints as brain outputs
						auto outputs = critter_unit->m_brain->getChild( "outputs", 1 );
						auto constraints_ref = outputs->addChild( "bullet_constraints", new BEntity_reference() );
						auto constraints = fixed_1->getChild( "constraints", 1 );
						constraints_ref->set( constraints );
						
						// motor neurons
						// eat
						auto motor_neurons = critter_unit->addChild( "motor_neurons", new BEntity() );
				// 		auto motor_neuron_eat = motor_neurons->addChild( "eat", "Neuron" );
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


					
					critter_unit->m_brain = brain_system->getChildCustom( critter_unit->m_brain, "new" );

					// REFERENCE TO EXTERNAL CHILD
						critter_unit->addChild( "external_brain", new BEntity_external() )->set( critter_unit->m_brain );

					// species
					m_species_system->addNewSpecies( critter_unit );

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
						if ( procreate->get_float() != 0.0f )
						{
							std::cout << "COPY: " << critter_unit->id() << " ad: " << critter_unit->getChild( "adam_distance", 1 )->get_uint() << " total:" << m_unit_container->numChildren() << "(h: " << t_highest << ")" << std::endl;

							critter_unit->setEnergy( critter_unit->energy() / 2 );
// 							critter_unit->setAge( Buint(0) );
							procreate->set( 0.0f );
							
							// COPY CRITTER
								auto critter_new = m_entityCopy.copyEntity( critter_unit );
								critter_new->getChild( "age", 1 )->set( Buint(0) );
// 								critter_new->getChild( "energy", 1 )->set( Buint(0) );

								if ( m_unit_container->numChildren() > t_highest )
								{
									t_highest = m_unit_container->numChildren();
								}
								
								
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
								auto brain_system = parent()->getChild( "brain_system", 1 );

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
								if ( brain_system->set( "mutate", brain_new ) )
								{
									auto ad = critter_new->getChild( "adam_distance", 1 );
									ad->set( ad->get_uint() + 1 );
									
									m_species_system->addNewSpecies( critter_new );
								}
								else
								{
									m_species_system->copySpecies( critter_unit, critter_new );
								}
							
							// std::cout << "COPYING CRITTER: " << critter_unit->id() << " done" << std::endl << std::endl;
							// PREVENT FURTHER ACTIONS IN THIS FRAME
								return; 
						}
					}
				}
			}
		}
		
		// // DIE BECAUSE CRITTER LIMIT REACHED
		// if ( m_unit_container->numChildren() >= 150 )
		// {
		// 	for_all_children_of2( m_unit_container )
		// 	{
		// 		m_unit_container->removeChild( *child2 );
  // 
		// 		// PREVENT FURTHER ACTIONS IN THIS FRAME
		// 			break;
		// 	}
		// }
	}
	
	void CdCritterSystem::removeCritter( BEntity* entity )
	{
		// HACK first external child one is body
		auto bodyparts = entity->getChild( "external_body", 1 )->get_reference()->getChild( "body_fixed1", 1 )->getChild( "bodyparts", 1 );
		while ( removeFromCollisions( bodyparts ) ) {;}

		// species
		m_species_system->removeFromSpecies( entity );

		m_unit_container->removeChild( entity );
		
	}
	
	bool CdCritterSystem::removeFromCollisions( BEntity* to_remove_list )
	{
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
		// m_species = addChild( "species_reference", new BEntity_reference() );
		addChild( "adam_distance", new BEntity_uint() )->set( Buint(0) );
	}
	
	
	
	
