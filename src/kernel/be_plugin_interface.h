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

// class BEntityClasses : public BEntity
// {
// 	// CONSTRUCTORS / DESTRUCTOR
// 		public:
// 			BEntityClasses();
// 			virtual ~BEntityClasses();
// 			void addClass( const Buint id, const std::string& name );
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager ) { (void)hboxlayout; (void) plugin_manager; };
// };

// class BEntityType : public BEntity
// {
// 	// CONSTRUCTORS / DESTRUCTOR
// 		public:
// 			BEntityType() { };
// 			virtual ~BEntityType() { };
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// };

#endif
