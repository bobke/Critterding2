#pragma once

#include "kernel/be_entity_core_types.h"

	class cmd_launch: public BEntity_trigger
	{
		public:
			cmd_launch() { };
			virtual ~cmd_launch() {};
			bool set();
	};

