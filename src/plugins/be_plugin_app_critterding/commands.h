#pragma once

#include "kernel/be_entity_core_types.h"

	class cmd_toggleFullscreen: public BEntity_trigger
	{
		public:
			cmd_toggleFullscreen() { };
			virtual ~cmd_toggleFullscreen() {};
			bool set();
	};
	
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
	
	class cmd_launchSelectionWindow: public BEntity_trigger
	{
		public:
			cmd_launchSelectionWindow() { };
			virtual ~cmd_launchSelectionWindow() {};
			bool set();
	};

	class cmd_mousePickBody: public BEntity_trigger
	{
		public:
			cmd_mousePickBody() { };
			virtual ~cmd_mousePickBody() {};
			bool set();
	};

	class cmd_mouseUnpickBody: public BEntity_trigger
	{
		public:
			cmd_mouseUnpickBody() { };
			virtual ~cmd_mouseUnpickBody() {};
			bool set();
	};
