#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_interface.h"
// #include "kernel/be_timer.h"

	// SCENE
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() {};
				virtual ~Scene() {};
				
				virtual void construct();
		};
		
	// SYSTEM MONITOR
		class BSystemMonitor: public BEntity
		{
			public:
				BSystemMonitor() : BEntity(), m_timer_s_total(0), m_timer_frame(0)
				{
					// SET PROCESSING BIT
						setProcessing();
// 						m_flags.m_has_processing = true;
				};
				virtual ~BSystemMonitor() {};
				
				virtual void construct();
				virtual void process();
// 				virtual void process_general();
			private:
				BEntity* m_width;
// 				BEntity* m_qtapp;
// 				BEntity* m_CPUInfo; // CAN BE REMOVED
// 				BEntity* m_raycast_scene; // CAN BE REMOVED
				
				// LINE EDITS
				BEntity* m_line_edit_frame_counter;
				BEntity* m_line_edit_fps_cur;
				BEntity* m_line_edit_fps_avg;
				BEntity* m_line_edit_entities;
				BEntity* m_line_edit_last_entity_id;
				BEntity* m_line_edit_uptime;
				BEntity* m_line_edit_memory;
				
				BEntity* m_timer_s_total;
				BEntity* m_timer_frame;
				Buint64 m_frame_counter_last;
				Bfloat m_last_updated;

				Buint m_last_processed_qapp;
				
				// Buint m_background_strive_fps;
				// BEntity* m_line_edit_fps_background;
				BEntity* m_line_edit_vk_loadmodel_fps;
		};

		class BGLApp: public BEntity
		{
			public:
				BGLApp() : BEntity() {};
				virtual ~BGLApp() {};
				
				virtual void construct();
		};
#endif
