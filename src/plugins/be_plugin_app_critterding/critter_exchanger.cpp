#include "critter_exchanger.h"
#include "species_system.h"
#include "kernel/be_entity_core_types.h"
// #include "kernel/be_entity_ops_copy.h"
#include <iostream>
#include <unistd.h>

	void CdCritterExchanger::construct()
	{
		setFps(1);

		m_active = addChild( "active", new BEntity_bool() );
		m_active->set( false );

		auto critterding = topParent()->getChild("Scene", 1)->getChild("Critterding");

		m_critter_system = dynamic_cast<CdCritterSystem*>( critterding->getChild("critter_system") );
		m_species_system = dynamic_cast<CdSpeciesSystem*>( critterding->getChild("species_system") );
		m_critter_unit_container = m_critter_system->getChild("unit_container");

		m_rng = critterding->getChild("random_number_generator");

		// TIMER
			m_interval_seconds = addChild( "interval_seconds", new BEntity_float() );
			m_interval_seconds->set( 180.0f );
			m_last_updated = 0.0f;
			auto timer = topParent()->getChild("sys", 1)->getChild("timer", 1);
			m_timer_s_total = timer->getChild("s_total", 1);
			m_timer_frame = timer->getChild("frame", 1);
			
		// WEIGHTS
			m_weight_save = addChild( "weight_save", new BEntity_uint() );
			m_weight_load = addChild( "weight_load", new BEntity_uint() );
			
			m_weight_save->set( Buint(40) );
			m_weight_load->set( Buint(60) );
	} 

	void CdCritterExchanger::process()
	{
		if ( m_active->get_bool() )
		{
			// CHECK TIME
			const float elapsed_seconds = m_timer_s_total->get_float() - m_last_updated;
			if ( elapsed_seconds >= m_interval_seconds->get_float() )
			{
				std::cout << std::endl;
				std::cout << "EXCHANGER: " << std::endl;
				
				int sum = m_weight_save->get_uint() + m_weight_load->get_uint();

				// PICK SAVE OR LOAD
				m_rng->set( "min", Bint(0) );
				m_rng->set( "max", sum );

				// NOTE: complex loading/saving if's, but it works out

				// LOADING // FIXME RESET AGE
				if ( m_rng->get_int() < m_weight_load->get_uint() )
				{
					std::cout << " LOADING: " << std::endl;
					
					// CREATE TEMPORARY FILENAME
						auto ms_start = topParent()->getChild("sys", 1)->getChild("timer", 1)->getChild("ms_start")->get_uint();
						std::string filename_to_rename_to = std::to_string(ms_start);
						filename_to_rename_to.append(".ent");
					
					// CREATE FILENAME
						std::string filename;
						unsigned int count(0);
						unsigned int countmax(100);
     
						filename = "critter_exchange_unit_";
						filename.append(std::to_string(count));
						filename.append(".ent");
     
						std::cout << "  finding candidate" << std::endl;
						while ( rename( filename.c_str(), filename_to_rename_to.c_str() ) != 0 && count++ < countmax )
						{
							// file exists
							filename= "critter_exchange_unit_";
							filename.append(std::to_string(count));
							filename.append(".ent");
						}
						std::cout << "  finding candidate done" << std::endl;
     
						// found
						if ( count < countmax )
						{
							// LOAD CRITTER
								std::cout << "  loading " << filename << std::endl;
								BEntityLoad b;
								b.loadEntity(m_critter_unit_container, filename_to_rename_to);
								std::cout << "  loading " << filename << " done" << std::endl;

								auto critter = m_critter_unit_container->children().rbegin();
								m_species_system->addNewSpecies( *critter );

								
								// reset age
									(*critter)->getChild("age", 1)->set( Buint(0) );
     
								// REMOVE FILE
								std::cout << "  removing" << std::endl;
								if( remove( filename_to_rename_to.c_str() ) != 0 )
								{
									std::cout << "Error deleting file" << std::endl;
								}
								else
								{
									std::cout << "File successfully deleted" << std::endl;
								}
								std::cout << "  removing done" << std::endl;
						}
					std::cout << " LOADING done " << std::endl;
				}

				// SAVING
				else
				{
					if ( m_critter_unit_container->hasChildren() )
					{
						std::cout << " SAVING: " << std::endl;
						// std::cout << "elapsed_seconds: " << elapsed_seconds << std::endl;

						// PICK RANDOM CRITTER
							m_rng->set( "min", Bint(0) );
							m_rng->set( "max", Bint( m_critter_unit_container->numChildren())-1 );
							auto randomChild = m_critter_unit_container->children()[m_rng->get_int()];

						// CREATE TEMPORARY FILENAME
							auto ms_start = topParent()->getChild("sys", 1)->getChild("timer", 1)->getChild("ms_start")->get_uint();
							std::string filename_to_save_to = std::to_string(ms_start);
							filename_to_save_to.append(".ent");
							
						// SAVE CRITTER
							std::cout << "  saving to " << filename_to_save_to << std::endl;
							BEntitySave b;
							b.saveEntity( randomChild, filename_to_save_to );
							std::cout << "  saving to " << filename_to_save_to << "done" << std::endl;

						// FIND FILENAME
							std::string filename_to_rename_to;
							unsigned int count(0);
							filename_to_rename_to = "critter_exchange_unit_";
							filename_to_rename_to.append(std::to_string(count));
							filename_to_rename_to.append(".ent");

							std::cout << "  checking existing files" << std::endl;
							while (access(filename_to_rename_to.c_str(), F_OK) == 0)
							{
								// file exists
								filename_to_rename_to = "critter_exchange_unit_";
								filename_to_rename_to.append(std::to_string(++count));
								filename_to_rename_to.append(".ent");
							}
							std::cout << "  checking existing files done" << std::endl;

						// RENAME
							std::cout << "  renaming" << std::endl;
							if ( rename( filename_to_save_to.c_str(), filename_to_rename_to.c_str() ) != 0 )
							{
								std::cout << "Error renaming file" << std::endl;
							}
							else
							{
								std::cout << "File successfully renamed" << std::endl;
							}
							std::cout << "  renaming done" << std::endl;

						std::cout << " SAVING done " << std::endl;
					}
				}

				// SET VALUES NEEDED FOR NEXT UPDATE
					m_last_updated = m_timer_s_total->get_float();

				std::cout << "EXCHANGER done " << std::endl;
				std::cout << std::endl;
			}

		}
	}
