#ifndef BE_PLUGIN_INTERFACE_H_INCLUDED
#define BE_PLUGIN_INTERFACE_H_INCLUDED

#include "be_entity_interface.h"

	class BClassesHelper
	{
		// CONSTRUCTORS / DESTRUCTOR
			public:
				BClassesHelper() {};
				virtual ~BClassesHelper() {};
				void addClass( BEntity* parent, Buint id, const std::string& name );
	};

#endif
