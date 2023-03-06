#include "be_plugin_base_entity_types.h"
		
// ---- FACTORIES
	enum CLASS
	{
		PLUGIN_INFO
		, REFERENCE
		, EXTERNAL
		, TRIGGER
		, BOOL
		, BOOL_PROPERTY
		, UINT
		, UINT_PROPERTY
		, INT
		, INT_PROPERTY
		, FLOAT
		, FLOAT_PROPERTY
		, STRING
		, STRING_PROPERTY
	};

	extern "C" BEntity* create( BEntity* parent, const Buint type )
	{
// 		std::cout << "LIB CREATE:: type: " << type  << std::endl;

		// PLUGIN DESCRIPTION ENTITY
			if ( type == PLUGIN_INFO )
			{
				BClassesHelper i;
					i.addClass( parent, CLASS::REFERENCE, "reference" );
					i.addClass( parent, CLASS::EXTERNAL, "external_child" );
					i.addClass( parent, CLASS::TRIGGER, "trigger" );
					i.addClass( parent, CLASS::BOOL, "bool" );
					i.addClass( parent, CLASS::BOOL_PROPERTY, "bool_property" );
					i.addClass( parent, CLASS::UINT, "uint" );
					i.addClass( parent, CLASS::UINT_PROPERTY, "uint_property" );
					i.addClass( parent, CLASS::INT, "int" );
					i.addClass( parent, CLASS::INT_PROPERTY, "int_property" );
					i.addClass( parent, CLASS::FLOAT, "float" );
					i.addClass( parent, CLASS::FLOAT_PROPERTY, "float_property" );
					i.addClass( parent, CLASS::STRING, "string" );
					i.addClass( parent, CLASS::STRING_PROPERTY, "string_property" );
				return 0;
			}

// 		// ENTITIES
// 			else
// 			{
// 				BEntity* i(0);
// 				
// 				if ( type == CLASS::REFERENCE )
// 					i = new BEntity_reference();
// 
// 				else if ( type == CLASS::EXTERNAL )
// 					i = new BEntity_external();
// 
// 				else if ( type == CLASS::TRIGGER )
// 					i = new BEntity_trigger();
// 
// 				else if ( type == CLASS::BOOL )
// 					i = new BEntity_bool();
// 
// 				else if ( type == CLASS::BOOL_PROPERTY )
// 					i = new BEntity_bool_property();
// 
// 				else if ( type == CLASS::UINT )
// 					i = new BEntity_uint();
// 
// 				else if ( type == CLASS::UINT_PROPERTY )
// 					i = new BEntity_uint_property();
// 				
// 				else if ( type == CLASS::INT )
// 					i = new BEntity_int();
// 
// 				else if ( type == CLASS::INT_PROPERTY )
// 					i = new BEntity_int_property();
// 
// 				else if ( type == CLASS::FLOAT )
// 					i = new BEntity_float();
// 
// 				else if ( type == CLASS::FLOAT_PROPERTY )
// 					i = new BEntity_float_property();
// 				
// 				else if ( type == CLASS::STRING )
// 					i = new BEntity_string();
// 
// 				else if ( type == CLASS::STRING_PROPERTY )
// 					i = new BEntity_string_property();
// 				
// 				else
// 					std::cout << "BEntityTypes::create::Class implementation is missing" << std::endl;
// 
// 				return i;
// 			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}
		
