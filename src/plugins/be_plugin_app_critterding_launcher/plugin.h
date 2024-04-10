#pragma once

#include "kernel/be_plugin_interface.h"

		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() { setProcessing(); };
				const char* class_id() const { return "CritterdingLauncher"; }
				virtual ~Scene() {};
				
				virtual void construct();
				virtual void process();
				
			private:
		};

