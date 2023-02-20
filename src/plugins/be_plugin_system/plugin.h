#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_interface.h"
// #include "kernel/be_timer.h"

#include <sstream>

	// CLASS 1
		class CPUInfo: public BEntity
		{
			public:
				CPUInfo() : BEntity(), m_timer_ms_total(0)
				{
					// SET PROCESSING BIT
						setProcessing();
// 						m_flags.m_has_processing = true;
				};

				virtual ~CPUInfo() {};
				virtual void process();
				virtual void construct();
			private:
				std::string m_line;
				std::istringstream m_split_stringstream;
				std::string m_piece;
				// BeTimer m_timer; // we use a timer because below 10s we get bad recordings, so this acts as a cap
				BEntity* m_timer_ms_total;
				Buint m_last_processed;
		};

#endif
