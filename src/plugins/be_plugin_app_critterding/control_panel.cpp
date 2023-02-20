#include "control_panel.h"
#include "kernel/be_timer.h"
#include "kernel/be_lib_handler.h"

	void CdControlPanel::construct()
	{
		setFps(2);
		
		// std::cout << "CdControlPanel::construct()" << std::endl;

		// FIND CRITTERDING
			auto critterding = topParent()->getChild("Scene", 1)->getChild("Critterding", 1);

		// SYSTEMS
			auto critter_system = critterding->getChild("critter_system", 1);
			auto food_system = critterding->getChild("food_system", 1);
			auto brain_system = critterding->getChild("brain_system", 1);
			auto critter_settings = critter_system->getChild("settings", 1);

			m_critter_unit_container = critter_system->getChild("unit_container", 1);
			m_critter_species_system_unit_container = critter_system->getChild("species_system", 1)->getChild("unit_container", 1);
			m_food_unit_container = food_system->getChild("unit_container", 1);
			m_brain_unit_container = brain_system->getChild("unit_container", 1);
			m_critter_maximum_age = critter_settings->getChild("maximum_age", 1);

		// M_TIMER // FIXME getTimer()
			auto found_sys = topParent()->getChild("sys", 1);
			auto timer = found_sys->getChild("timer", 1);
			m_timer_frame = timer->getChild("frame", 1);

		// BASE TYPES
			pluginManager()->load( "basetypes", "src/kernel", "be_base_entity_types" );
			
		// GUI
			pluginManager()->load( "qt6", "src/plugins/be_plugin_qt6", "be_plugin_qt6" );

		// QWINDOW
			auto qwindow = addChild( "QT MainWindow", "QMainWindow" );
			qwindow->addChild( "title", "string_property" )->set("Critterding Control Panel");
			qwindow->addChild( "x", "uint_property" )->set(Buint(1560));
			qwindow->addChild( "y", "uint_property" )->set(Buint(40));
			qwindow->addChild( "width", "uint_property" )->set(Buint(590));
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
						auto line_edit_min_critters= layout_H->addChild( "min_critters_lineedit", "QLineEdit" );
						line_edit_min_critters->set("min_critters");
						line_edit_min_critters->set("width", Buint(164));
						line_edit_min_critters->set("height", Buint(28));

						auto critter_system = critterding->getChild("critter_system", 1);
						auto critter_settings = critter_system->getChild("settings", 1);
						auto critter_number_of_units = critter_settings->getChild("minimum_number_of_units", 1);
						line_edit_min_critters->set( critter_number_of_units->get_uint() );
						critter_number_of_units->connectServerServer( line_edit_min_critters );
						line_edit_min_critters->connectServerServer( critter_number_of_units );
					}

					layout_H = layout_H_row->addChild( "energy layout", "QHBoxLayout" );
					{
						auto text_energy = layout_H->addChild( "energy", "QLabel" );
						text_energy->set("text", "energy");
						auto line_edit_energy= layout_H->addChild( "energy_lineedit", "QLineEdit" );
						// m_line_edit_energy->set("energy");
						line_edit_energy->set("width", Buint(164));
						line_edit_energy->set("height", Buint(28));

						auto food_system = critterding->getChild("food_system", 1);
						auto food_settings = food_system->getChild("settings", 1);
						auto food_number_of_units = food_settings->getChild("number_of_units", 1);
						line_edit_energy->set( food_number_of_units->get_uint() );
						food_number_of_units->connectServerServer( line_edit_energy );
						line_edit_energy->connectServerServer( food_number_of_units );
					}

				// ROW 2
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "mutation_rate", "QHBoxLayout" );
					{
						auto text_mutation_chance = layout_H->addChild( "mutation_chance", "QLabel" );
						text_mutation_chance->set("text", "mutation_chance");
						auto line_edit_mutation_chance = layout_H->addChild( "mutation_chance_lineedit", "QLineEdit" );
						line_edit_mutation_chance->set("mutation_chance");
						line_edit_mutation_chance->set("width", Buint(164));
						line_edit_mutation_chance->set("height", Buint(28));

						auto brain_system = critterding->getChild("brain_system", 1);
						auto brain_settings = brain_system->getChild("settings", 1);
						auto brain_mutation_chance = brain_settings->getChild("mutation_chance", 1);
						line_edit_mutation_chance->set( brain_mutation_chance->get_uint() );
						brain_mutation_chance->connectServerServer( line_edit_mutation_chance );
						line_edit_mutation_chance->connectServerServer( brain_mutation_chance );
					}

					layout_H = layout_H_row->addChild( "mutationruns_max layout", "QHBoxLayout" );
					{
						auto text_mutationruns_max = layout_H->addChild( "mutationruns_max", "QLabel" );
						text_mutationruns_max->set("text", "mutationruns_max");
						auto line_edit_mutationruns_max = layout_H->addChild( "mutationruns_max_lineedit", "QLineEdit" );
						// m_line_edit_mutationruns_max->set("mutationruns_max");
						line_edit_mutationruns_max->set("width", Buint(164));
						line_edit_mutationruns_max->set("height", Buint(28));

						auto brain_system = critterding->getChild("brain_system", 1);
						auto brain_settings = brain_system->getChild("settings", 1);
						auto brain_mutationruns_max = brain_settings->getChild("mutationruns_max", 1);
						line_edit_mutationruns_max->set( brain_mutationruns_max->get_uint() );
						brain_mutationruns_max->connectServerServer( line_edit_mutationruns_max );
						line_edit_mutationruns_max->connectServerServer( brain_mutationruns_max );
					}

				// ROW 3
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "avg_adam_distance_layout", "QHBoxLayout" );
					{
						auto text_avg_adam_distance = layout_H->addChild( "avg_adam_distance", "QLabel" );
						text_avg_adam_distance->set("text", "avg_adam_distance");
						m_line_edit_avg_adam_distance= layout_H->addChild( "avg_adam_distance_lineedit", "QLineEdit" );
						m_line_edit_avg_adam_distance->set("avg_adam_distance");
						m_line_edit_avg_adam_distance->set("width", Buint(164));
						m_line_edit_avg_adam_distance->set("height", Buint(28));
					}

					layout_H = layout_H_row->addChild( "generations layout", "QHBoxLayout" );
					{
						auto text_generations = layout_H->addChild( "generations", "QLabel" );
						text_generations->set("text", "generations");
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
						m_line_edit_critters= layout_H->addChild( "critters_lineedit", "QLineEdit" );
						m_line_edit_critters->set("critters");
						m_line_edit_critters->set("width", Buint(164));
						m_line_edit_critters->set("height", Buint(28));
					}

					layout_H = layout_H_row->addChild( "food layout", "QHBoxLayout" );
					{
						auto text_food = layout_H->addChild( "food", "QLabel" );
						text_food->set("text", "food");
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
						m_line_edit_total_neurons = layout_H->addChild( "neurons_lineedit", "QLineEdit" );
						m_line_edit_total_neurons->set("neurons");
						m_line_edit_total_neurons->set("width", Buint(164));
						m_line_edit_total_neurons->set("height", Buint(28));
					}
					
					layout_H = layout_H_row->addChild( "total synapses layout", "QHBoxLayout" );
					{
						auto text_total_synapses = layout_H->addChild( "text_total_synapses", "QLabel" );
						text_total_synapses->set("text", "synapses");
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
						m_line_edit_avg_neurons = layout_H->addChild( "avg_neurons_lineedit", "QLineEdit" );
						m_line_edit_avg_neurons->set("avg neurons");
						m_line_edit_avg_neurons->set("width", Buint(164));
						m_line_edit_avg_neurons->set("height", Buint(28));
					}
					
					layout_H = layout_H_row->addChild( "avg synapses layout", "QHBoxLayout" );
					{
						auto text_avg_synapses = layout_H->addChild( "text_avg_synapses", "QLabel" );
						text_avg_synapses->set("text", "avg synapses / neuron");
						m_line_edit_avg_synapses = layout_H->addChild( "avg_synapses_lineedit", "QLineEdit" );
						m_line_edit_avg_synapses->set("avg synapses");
						m_line_edit_avg_synapses->set("width", Buint(164));
						m_line_edit_avg_synapses->set("height", Buint(28));
					}

				// ROW 7
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "species layout", "QHBoxLayout" );
					{
						auto text_species = layout_H->addChild( "text_species", "QLabel" );
						text_species->set("text", "species");
						m_line_edit_species = layout_H->addChild( "species_lineedit", "QLineEdit" );
						m_line_edit_species->set("species");
						m_line_edit_species->set("width", Buint(164));
						m_line_edit_species->set("height", Buint(28));
					}

					layout_H = layout_H_row->addChild( "avg crittersperspecies layout", "QHBoxLayout" );
					{
						auto text_avg_crittersperspecies = layout_H->addChild( "text_avg_crittersperspecies", "QLabel" );
						text_avg_crittersperspecies->set("text", "avg critters / species");
						m_line_edit_avg_crittersperspecies = layout_H->addChild( "avg_crittersperspecies_lineedit", "QLineEdit" );
						m_line_edit_avg_crittersperspecies->set("avg crittersperspecies");
						m_line_edit_avg_crittersperspecies->set("width", Buint(164));
						m_line_edit_avg_crittersperspecies->set("height", Buint(28));
					}

				// ROW WQT
					layout_H_row = layout_V->addChild( "QT HBoxlayout", "QHBoxLayout" );
					layout_H = layout_H_row->addChild( "species layout", "QHBoxLayout" );
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
/*
					layout_H = layout_H_row->addChild( "avg crittersperspecies layout", "QHBoxLayout" );
					{
						auto text_avg_crittersperspecies = layout_H->addChild( "text_avg_crittersperspecies", "QLabel" );
						text_avg_crittersperspecies->set("text", "avg critters / species");
						m_line_edit_avg_crittersperspecies = layout_H->addChild( "avg_crittersperspecies_lineedit", "QLineEdit" );
						m_line_edit_avg_crittersperspecies->set("avg crittersperspecies");
						m_line_edit_avg_crittersperspecies->set("width", Buint(164));
						m_line_edit_avg_crittersperspecies->set("height", Buint(28));
					}*/
	} 

	void CdControlPanel::process()
	{
		// CRITTERS
			auto critters = m_critter_unit_container->numChildren();
			m_line_edit_critters->set( critters );
			m_qwt_curve_critters->set( critters );

			unsigned int total_adam_distance(0);
			for_all_children_of2( m_critter_unit_container )
			{
				total_adam_distance += (*child2)->getChild("adam_distance", 1)->get_uint();
			}

			m_line_edit_avg_adam_distance->set( float(total_adam_distance) / critters );

			if ( m_critter_maximum_age->get_uint() > 0 )
			{
				auto this_generations = (float)m_timer_frame->get_uint() / m_critter_maximum_age->get_uint();
				m_line_edit_generations->set( this_generations );
			}

		// FOOD
			auto food = m_food_unit_container->numChildren();
			m_line_edit_food->set( food );
			m_qwt_curve_food->set( food );

		// NEURONS & SYNAPSES
			// FIXME LOOP SPECIES FOR SPEED
			unsigned int neurons(0);
			unsigned int synapses(0);
			for_all_children_of( m_brain_unit_container )
			{
				auto neuron_container = (*child)->getChild("neurons", 1);
				neurons += neuron_container->numChildren();
				for_all_children_of2( neuron_container )
				{
					auto synapse_container = (*child2)->getChild("synapses", 1);
					synapses += synapse_container->numChildren();
				}
			}

			m_line_edit_total_neurons->set( neurons );
			m_line_edit_total_synapses->set( synapses );

			m_line_edit_avg_neurons->set( float(neurons) / critters );
			m_line_edit_avg_synapses->set( float(synapses) / neurons );

		// CRITTERS / SPECIES
			m_line_edit_species->set( m_critter_species_system_unit_container->numChildren() );
			if ( m_critter_species_system_unit_container->numChildren() > 0 )
			{
				m_line_edit_avg_crittersperspecies->set( float(critters) / m_critter_species_system_unit_container->numChildren() );
			}
			else
			{
				m_line_edit_avg_crittersperspecies->set(Buint(0));
			}
	}
