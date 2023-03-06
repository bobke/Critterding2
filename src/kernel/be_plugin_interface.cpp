#include "be_plugin_interface.h"
#include "be_plugin_base_entity_types.h"

	void BClassesHelper::addClass( BEntity* parent, Buint id, const std::string& name )
	{
		BEntity* t_cl = parent->addChild( name, new BEntity_uint() );
		t_cl->set( id );
	}
