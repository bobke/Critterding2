#include "control_panel.h"
#include "kernel/be_entity_core_types.h"
// #include "kernel/be_timer.h"
// #include "kernel/be_lib_handler.h"

	void CdControlPanel::construct()
	{
		setFps(2);
		
		// std::cout << "CdControlPanel::construct()" << std::endl;

		// FIND CRITTERDING
			auto critterding = topParent()->getChild("bin", 1)->getChild("Critterding", 1);

		// FIND ALL THREADS
			m_critter_unit_containers = addChild("unit_containers", new BEntity() );
			auto critter_systems = addChild("critter_systems", new BEntity() );
			auto food_systems = addChild("food_systems", new BEntity() );
			m_brain_systems = addChild("brain_systems", new BEntity() );
			auto brain_settings = addChild("brain_settings", new BEntity() );
			auto critter_settings = addChild("critter_settings", new BEntity() );
			m_food_unit_containers = addChild("food_unit_containers", new BEntity() );
			m_brain_unit_containers = addChild("brain_unit_containers", new BEntity() );
			for_all_children_of( critterding )
			{
				if ( (*child)->class_id() == std::string("thread") )
				{
					auto critter_system = (*child)->getChild("Critterding", 1)->getChild("critter_system", 1);
					auto unit_container = critter_system->getChild("unit_container", 1);
					auto food_system = (*child)->getChild("Critterding", 1)->getChild("food_system", 1);
					auto food_unit_container = food_system->getChild("unit_container", 1);
					auto brain_system = critter_system->getChild("brain_system", 1);
					auto brain_unit_container = brain_system->getChild("unit_container", 1);
					auto critter_sett = critter_system->getChild("settings", 1);
					auto brain_sett = brain_system->getChild("settings", 1);
					m_critter_unit_containers->addChild( "unit_container_ref", new BEntity_reference() )->set( unit_container );
					m_food_unit_containers->addChild( "unit_container_ref", new BEntity_reference() )->set( food_unit_container );
					critter_systems->addChild( "critter_system_ref", new BEntity_reference() )->set( critter_system );
					food_systems->addChild( "food_system_ref", new BEntity_reference() )->set( food_system );
					m_brain_systems->addChild( "brain_system_ref", new BEntity_reference() )->set( brain_system );
					critter_settings->addChild( "critter_settings_ref", new BEntity_reference() )->set( critter_sett );
					brain_settings->addChild( "brain_settings_ref", new BEntity_reference() )->set( brain_sett );
					m_brain_unit_containers->addChild( "brain_unit_containers_ref", new BEntity_reference() )->set( brain_unit_container );
				}
			}
			
		// SYSTEMS
			// auto critter_system = critterding->getChild("critter_system", 1);
			// auto food_system = critterding->getChild("food_system", 1);
			// auto brain_system = critter_system->getChild("brain_system", 1);
			// auto critter_settings = critter_system->getChild("settings", 1);

			// m_critter_unit_container = critter_system->getChild("unit_container", 1);
			// // m_critter_species_system_unit_container = critter_system->getChild("species_system", 1)->getChild("unit_container", 1);
			// m_food_unit_container = food_system->getChild("unit_container", 1);
			// m_brain_unit_container = brain_system->getChild("unit_container", 1);
			// m_critter_maximum_age = critter_settings->getChild("maximum_age", 1);

		// M_TIMER // FIXME getTimer()
			auto found_sys = topParent()->getChild("sys", 1);
			auto timer = found_sys->getChild("timer", 1);
			m_timer_frame = timer->getChild("frame", 1);

// 		// BASE TYPES
// 			pluginManager()->load( "basetypes", "src/kernel", "be_base_entity_types" );
// 			
// 		// GUI
// 			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );

		// QWINDOW
			auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
			qwindow->addChild( "title", "string_property" )->set("Critterding Control Panel");
			qwindow->addChild( "x", "uint_property" )->set(Buint(650));
			qwindow->addChild( "y", "uint_property" )->set(Buint(40));
			qwindow->addChild( "width", "uint_property" )->set(Buint(680));
			qwindow->addChild( "height", "uint_property" )->set(Buint(460));
			qwindow->set("on_close_destroy_entity", this);

		// GENERAL V LAYOUT
			auto general_layout_V = qwindow->addChild( "QT VBoxlayout", "QVBoxLayout" );
			
		// GENERAL V LAYOUT
			auto general_layout_H = general_layout_V->addChild( "QT VBoxlayout", "QVBoxLayout" );


			// STATS V LAYOUT
				auto layout_V = general_layout_H->addChild( "QT VBoxlayout for stats", "QVBoxLayout" );

			// LINE EDITS

				// ROW 1
					auto layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					auto layout_H = layout_H_row->addChild( "min_critters_layout", "QHBoxLayout" );
					{
						auto text_min_critters = layout_H->addChild( "min_critters", "QLabel" );
						text_min_critters->set("text", "minimum critters");
						text_min_critters->set("width", Buint(165));

						for_all_children_of( critter_settings )
						{
							auto critter_sett = (*child)->get_reference();
							auto line_edit_min_critters= layout_H->addChild( "min_critters_lineedit", "QLineEdit" );
							line_edit_min_critters->set("min_critters");
							line_edit_min_critters->set("width", Buint(41));
							line_edit_min_critters->set("height", Buint(28));

							auto critter_number_of_units = critter_sett->getChild("minimum_number_of_units", 1);
							line_edit_min_critters->set( critter_number_of_units->get_uint() );
							critter_number_of_units->connectServerServer( line_edit_min_critters );
							line_edit_min_critters->connectServerServer( critter_number_of_units );
						}
					}

					layout_H = layout_H_row->addChild( "energy layout", "QHBoxLayout" );
					{
						auto text_energy = layout_H->addChild( "energy", "QLabel" );
						text_energy->set("text", "energy");
						text_energy->set("width", Buint(165));

						for_all_children_of( food_systems )
						{
							
							auto line_edit_energy= layout_H->addChild( "energy_lineedit", "QLineEdit" );
							// m_line_edit_energy->set("energy");
							line_edit_energy->set("width", Buint(41));
							line_edit_energy->set("height", Buint(28));

							auto food_settings = (*child)->get_reference()->getChild("settings", 1);
							auto food_number_of_units = food_settings->getChild("number_of_units", 1);
							line_edit_energy->set( food_number_of_units->get_uint() );
							food_number_of_units->connectServerServer( line_edit_energy );
							line_edit_energy->connectServerServer( food_number_of_units );
						}
					}

				// ROW 2
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "mutation_rate", "QHBoxLayout" );
					{
						auto text_mutation_chance = layout_H->addChild( "mutation_chance", "QLabel" );
						text_mutation_chance->set("text", "mutation_chance");
						text_mutation_chance->set("width", Buint(165));
						
						for_all_children_of( brain_settings )
						{
							auto brain_sett = (*child)->get_reference();
							auto line_edit_mutation_chance = layout_H->addChild( "mutation_chance_lineedit", "QLineEdit" );
							line_edit_mutation_chance->set("mutation_chance");
							line_edit_mutation_chance->set("width", Buint(41));
							line_edit_mutation_chance->set("height", Buint(28));

							auto brain_mutation_chance = brain_sett->getChild("mutation_chance", 1);
							line_edit_mutation_chance->set( brain_mutation_chance->get_uint() );
							brain_mutation_chance->connectServerServer( line_edit_mutation_chance );
							line_edit_mutation_chance->connectServerServer( brain_mutation_chance );
						}
					}

					layout_H = layout_H_row->addChild( "mutationruns_max layout", "QHBoxLayout" );
					{
						auto text_mutationruns_max = layout_H->addChild( "mutationruns_max", "QLabel" );
						text_mutationruns_max->set("text", "mutationruns_max");
						text_mutationruns_max->set("width", Buint(165));
						
						for_all_children_of( brain_settings )
						{
							auto brain_sett = (*child)->get_reference();
						
							auto line_edit_mutationruns_max = layout_H->addChild( "mutationruns_max_lineedit", "QLineEdit" );
							// m_line_edit_mutationruns_max->set("mutationruns_max");
							line_edit_mutationruns_max->set("width", Buint(41));
							line_edit_mutationruns_max->set("height", Buint(28));

							auto brain_mutationruns_max = brain_sett->getChild("mutationruns_max", 1);
							line_edit_mutationruns_max->set( brain_mutationruns_max->get_uint() );
							brain_mutationruns_max->connectServerServer( line_edit_mutationruns_max );
							line_edit_mutationruns_max->connectServerServer( brain_mutationruns_max );
						}
					}

				// ROW 3
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "avg_adam_distance_layout", "QHBoxLayout" );
					{
						auto text_avg_adam_distance = layout_H->addChild( "avg_adam_distance", "QLabel" );
						text_avg_adam_distance->set("text", "avg_adam_distance");
						text_avg_adam_distance->set("width", Buint(165));
						m_line_edit_avg_adam_distance= layout_H->addChild( "avg_adam_distance_lineedit", "QLineEdit" );
						m_line_edit_avg_adam_distance->set("avg_adam_distance");
						m_line_edit_avg_adam_distance->set("width", Buint(164));
						m_line_edit_avg_adam_distance->set("height", Buint(28));
					}

					layout_H = layout_H_row->addChild( "generations layout", "QHBoxLayout" );
					{
						auto text_generations = layout_H->addChild( "generations", "QLabel" );
						text_generations->set("text", "generations");
						text_generations->set("width", Buint(165));
						m_line_edit_generations= layout_H->addChild( "generations_lineedit", "QLineEdit" );
						m_line_edit_generations->set("generations");
						m_line_edit_generations->set("width", Buint(164));
						m_line_edit_generations->set("height", Buint(28));
					}

				// ROW 4
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "critters_layout", "QHBoxLayout" );
					{
						auto text_critters = layout_H->addChild( "critters", "QLabel" );
						text_critters->set("text", "critters");
						text_critters->set("width", Buint(165));
						m_line_edit_critters= layout_H->addChild( "critters_lineedit", "QLineEdit" );
						m_line_edit_critters->set("critters");
						m_line_edit_critters->set("width", Buint(164));
						m_line_edit_critters->set("height", Buint(28));
					}

					layout_H = layout_H_row->addChild( "food layout", "QHBoxLayout" );
					{
						auto text_food = layout_H->addChild( "food", "QLabel" );
						text_food->set("text", "food");
						text_food->set("width", Buint(165));
						m_line_edit_food= layout_H->addChild( "food_lineedit", "QLineEdit" );
						m_line_edit_food->set("food");
						m_line_edit_food->set("width", Buint(164));
						m_line_edit_food->set("height", Buint(28));
					}

				// ROW 5
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "total neurons layout", "QHBoxLayout" );
					{
						auto text_total_neurons = layout_H->addChild( "text_total_neurons", "QLabel" );
						text_total_neurons->set("text", "neurons");
						text_total_neurons->set("width", Buint(165));
						m_line_edit_total_neurons = layout_H->addChild( "neurons_lineedit", "QLineEdit" );
						m_line_edit_total_neurons->set("neurons");
						m_line_edit_total_neurons->set("width", Buint(164));
						m_line_edit_total_neurons->set("height", Buint(28));
					}
					
					layout_H = layout_H_row->addChild( "total synapses layout", "QHBoxLayout" );
					{
						auto text_total_synapses = layout_H->addChild( "text_total_synapses", "QLabel" );
						text_total_synapses->set("text", "synapses");
						text_total_synapses->set("width", Buint(165));
						m_line_edit_total_synapses = layout_H->addChild( "total_synapses_lineedit", "QLineEdit" );
						m_line_edit_total_synapses->set("synapses");
						m_line_edit_total_synapses->set("width", Buint(164));
						m_line_edit_total_synapses->set("height", Buint(28));
					}

				// ROW 6
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "avg neurons layout", "QHBoxLayout" );
					{
						auto text_avg_neurons = layout_H->addChild( "text_avg_neurons", "QLabel" );
						text_avg_neurons->set("text", "avg neurons / critter");
						text_avg_neurons->set("width", Buint(165));
						m_line_edit_avg_neurons = layout_H->addChild( "avg_neurons_lineedit", "QLineEdit" );
						m_line_edit_avg_neurons->set("avg neurons");
						m_line_edit_avg_neurons->set("width", Buint(164));
						m_line_edit_avg_neurons->set("height", Buint(28));
					}
					
					layout_H = layout_H_row->addChild( "avg synapses layout", "QHBoxLayout" );
					{
						auto text_avg_synapses = layout_H->addChild( "text_avg_synapses", "QLabel" );
						text_avg_synapses->set("text", "avg synapses / neuron");
						text_avg_synapses->set("width", Buint(165));
						m_line_edit_avg_synapses = layout_H->addChild( "avg_synapses_lineedit", "QLineEdit" );
						m_line_edit_avg_synapses->set("avg synapses");
						m_line_edit_avg_synapses->set("width", Buint(164));
						m_line_edit_avg_synapses->set("height", Buint(28));
					}

				// ROW 7
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "species layout", "QHBoxLayout" );
					{
						// auto text_species = layout_H->addChild( "text_species", "QLabel" );
						// text_species->set("text", "species");
						// m_line_edit_species = layout_H->addChild( "species_lineedit", "QLineEdit" );
						// m_line_edit_species->set("species");
						// m_line_edit_species->set("width", Buint(164));
						// m_line_edit_species->set("height", Buint(28));
					}

					layout_H = layout_H_row->addChild( "avg crittersperspecies layout", "QHBoxLayout" );
					{
						// auto text_avg_crittersperspecies = layout_H->addChild( "text_avg_crittersperspecies", "QLabel" );
						// text_avg_crittersperspecies->set("text", "avg critters / species");
						// m_line_edit_avg_crittersperspecies = layout_H->addChild( "avg_crittersperspecies_lineedit", "QLineEdit" );
						// m_line_edit_avg_crittersperspecies->set("avg crittersperspecies");
						// m_line_edit_avg_crittersperspecies->set("width", Buint(164));
						// m_line_edit_avg_crittersperspecies->set("height", Buint(28));
					}

				// ROW WQT
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "graph layout", "QHBoxLayout" );
					{
						auto qwt_plot = layout_H->addChild( "plot", "QwtPlot" );
						
						{
							m_qwt_curve_critters = qwt_plot->addChild( "curve", "QwtCurve" );
							auto qpen = m_qwt_curve_critters->addChild( "pen", "QPen" );
							qpen->set( "color_r", Buint(50) );
							qpen->set( "color_g", Buint(50) );
							qpen->set( "color_b", Buint(255) );
						}
						{
							m_qwt_curve_food = qwt_plot->addChild( "curve", "QwtCurve" );
							auto qpen = m_qwt_curve_food->addChild( "pen", "QPen" );
							qpen->set( "color_g", Buint(200) );
						}
					}
	} 

	void CdControlPanel::process()
	{
		// FOOD
			unsigned int total_food(0);
			{
				for_all_children_of( m_food_unit_containers )
				{
					total_food += (*child)->get_reference()->numChildren();
				}
			}
			
			m_line_edit_food->set( (float)total_food );
			m_qwt_curve_food->set( total_food );

		// CRITTERS
			unsigned int total_critters(0);
			{
				for_all_children_of( m_critter_unit_containers )
				{
					total_critters += (*child)->get_reference()->numChildren();
				}
			}
			m_line_edit_critters->set( total_critters );
			m_qwt_curve_critters->set( total_critters );

			unsigned int total_adam_distance(0);
			{
				for_all_children_of( m_critter_unit_containers )
				{
					for_all_children_of2( (*child)->get_reference() )
					{
						total_adam_distance += (*child2)->getChild("adam_distance", 1)->get_uint();
					}
				}
			}

			m_line_edit_avg_adam_distance->set( float(total_adam_distance) / total_critters );

			// if ( m_critter_maximum_age->get_uint() > 0 )
			// {
			// 	auto this_generations = (float)m_timer_frame->get_uint() / m_critter_maximum_age->get_uint();
			// 	m_line_edit_generations->set( this_generations );
			// }

		// NEURONS & SYNAPSES
			// FIXME LOOP SPECIES FOR SPEED
			unsigned int neurons(0);
			unsigned int synapses(0);
			{
				for_all_children_of( m_brain_unit_containers )
				{
					for_all_children_of2( (*child)->get_reference() )
					{
						auto neuron_container = (*child2)->getChild("neurons", 1);
						neurons += neuron_container->numChildren();
						for_all_children_of3( neuron_container )
						{
							auto synapse_container = (*child3)->getChild("synapses", 1);
							synapses += synapse_container->numChildren();
						}
					}
				}
			}

			m_line_edit_total_neurons->set( neurons );
			m_line_edit_total_synapses->set( synapses );

			m_line_edit_avg_neurons->set( float(neurons) / total_critters );
			m_line_edit_avg_synapses->set( float(synapses) / neurons );

		// // CRITTERS / SPECIES
		// 	m_line_edit_species->set( m_critter_species_system_unit_container->numChildren() );
		// 	if ( m_critter_species_system_unit_container->numChildren() > 0 )
		// 	{
		// 		m_line_edit_avg_crittersperspecies->set( float(critters) / m_critter_species_system_unit_container->numChildren() );
		// 	}
		// 	else
		// 	{
		// 		m_line_edit_avg_crittersperspecies->set(Buint(0));
		// 	}
	}
