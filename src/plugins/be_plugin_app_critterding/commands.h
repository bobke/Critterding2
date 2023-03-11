#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "kernel/be_entity_core_types.h"

	class cmd_launchAdminWindow: public BEntity_trigger
	{
		public:
			cmd_launchAdminWindow() { };
			virtual ~cmd_launchAdminWindow() {};
			bool set();
	};

	class cmd_launchControlPanel: public BEntity_trigger
	{
		public:
			cmd_launchControlPanel() { };
			virtual ~cmd_launchControlPanel() {};
			bool set();
	};

		class cmd_launchSystemMonitor: public BEntity_trigger
	{
		public:
			cmd_launchSystemMonitor() { };
			virtual ~cmd_launchSystemMonitor() {};
			bool set();
	};
	
#endif
