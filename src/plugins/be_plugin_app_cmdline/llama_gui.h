#pragma once
#include "kernel/be_plugin_interface.h"
#include "kernel/be_entity_core_types.h"
#include "be_parser.h"

// SCENE
	class LLama_GUI: public BEntity
	{
		public:
			LLama_GUI() : BEntity() {};
			virtual ~LLama_GUI() {};
			virtual void construct();
	};


