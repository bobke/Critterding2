#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "kernel/be_entity_core_types.h"

	class cmd_launchAdminWindow: public BEntity_trigger
	{
		public:
			cmd_launchAdminWindow() { };
			virtual ~cmd_launchAdminWindow() {};
			const char* class_id() const { return "cmd_launchAdminWindow"; }
			bool set();
	};

	class cmd_launchControlPanel: public BEntity_trigger
	{
		public:
			cmd_launchControlPanel() { };
			virtual ~cmd_launchControlPanel() {};
			const char* class_id() const { return "cmd_launchControlPanel"; }
			bool set();
	};

	
#endif
