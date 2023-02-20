#ifndef CONFIG_LIBRARIES_H_INCLUDED
#define CONFIG_LIBRARIES_H_INCLUDED

#include "kernel/be_entity_interface.h"

	// 	CONFIG LIBRARIES WINDOW
		class BConfigLibraries: public BEntity
		{
			public:
				BConfigLibraries() : BEntity() {};
				virtual ~BConfigLibraries() {};
				
				virtual void construct();
			private:
				void add_config_libraries_groupbox( BEntity* parent, BEntity* entity );
				void add_config_libraries_list( BEntity* parent, BEntity* entity );
				void add_config_libraries_item( BEntity* parent, BEntity* entity );
		};


#endif
