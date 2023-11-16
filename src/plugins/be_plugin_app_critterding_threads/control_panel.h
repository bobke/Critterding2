#ifndef CONTROL_PANEL_H_INCLUDED
#define CONTROL_PANEL_H_INCLUDED

#include "kernel/be_entity_interface.h"

	class CdControlPanel: public BEntity
	{
		public:
			CdControlPanel() : BEntity()
			{
				// SET PROCESSING BIT
					setProcessing();
			};
			virtual ~CdControlPanel() {};
			const char* class_id() const { return "CdControlPanel"; }

			virtual void construct();
			virtual void process();
		private:
			BEntity* m_width;
			
			// SHORTCUTS
			BEntity* m_critter_unit_containers;
			BEntity* m_food_unit_containers;
			BEntity* m_brain_unit_containers;
			BEntity* m_brain_systems;
			// BEntity* m_brain_settings;
			// BEntity* m_critter_maximum_age;
			// BEntity* m_critter_species_system_unit_container;

			// LINE EDITS
			BEntity* m_line_edit_avg_adam_distance;
			BEntity* m_line_edit_generations;
			BEntity* m_line_edit_critters;
			BEntity* m_line_edit_food;
			BEntity* m_line_edit_total_neurons;
			BEntity* m_line_edit_total_synapses;
			BEntity* m_line_edit_avg_neurons;
			BEntity* m_line_edit_avg_synapses;
			BEntity* m_line_edit_species;
			BEntity* m_line_edit_avg_crittersperspecies;
			BEntity* m_qwt_curve_critters;
			BEntity* m_qwt_curve_food;

			BEntity* m_timer_frame;
	};

#endif
