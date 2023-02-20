#include "be_plugin_base_entity_types.h"
#include "be_entity_core_types.h"
// #include "command/be_commands.h"
// #include "be_entity_core_types.h"
#include "be_entity_io_handler.h"
// #include <iostream>

// 	// REFERENCE
// 		BEntity_reference::BEntity_reference()
// 		: m_value(0)
// 		{
// 		};
// 
// 		bool BEntity_reference::set( BEntity* value )
// 		{
// 			m_value = value;
// 			return true;
// 		}
// 		BEntity* BEntity_reference::get_reference()
// 		{
// 			return m_value;
// 		}

// 	// TRIGGER
// 
// 		BEntity_trigger::BEntity_trigger()
// 		{
// // // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 	
// 		bool BEntity_trigger::set()
// 		{
// // 			std::cout << "BEntity_trigger::set : " << id() << std::endl;
// 			onUpdate();
// 			return true;
// 		}
// 
// 		bool BEntity_trigger::apply( BEntity* const e ) const
// 		{
// // 			std::cout << "BEntity_trigger::apply : " << id() << std::endl;
// 			return e->set();
// 		}
// 
// 	// BOOL
// 		BEntity_bool::BEntity_bool()
// 		: m_value(0)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 
// 		bool BEntity_bool::set( const Bbool& value )
// 		{
// 			if ( m_value != value )
// 			{
// 				m_value = value;
// // 				if ( do_update )
// 					onUpdate();
// 				return true;
// 			}
// 			return false;
// 		}
// 
// 		bool BEntity_bool::apply( BEntity* const e ) const
// 		{
// 			return e->set( m_value );
// 		}
// 
// 		Bbool BEntity_bool::get_bool()
// 		{
// 			return m_value;
// 		}
// 
// 	// BOOL_PROPERTY
// 		BEntity_bool_property::BEntity_bool_property()
// // 		: m_value(0)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 		
// 		bool BEntity_bool_property::set( const Bbool& value )
// 		{
// 			if ( parent() /*&& value != m_value*/ )
// 			{
// 				return parent()->set( name(), value );
// // 				if ( parent()->set( name(), value ) )
// // 				{
// // 					m_value = value;
// // 					return true;
// // 				}
// 			}
// 			return false;
// 		}
// 
// 		Bbool BEntity_bool_property::get_bool()
// 		{
// 			if ( parent() /*&& value != m_value*/ )
// 			{
// 				return parent()->get_bool( name() );
// 			}
// 			return 0;
// 		}
// 		
// 		bool BEntity_bool_property::apply( BEntity* const e )
// 		{
// 			// std::cout << "BEntity_float_property::apply" << std::endl;
// 			if ( parent() )
// 			{
// // 				return e->set( m_value );
// 				return e->set( parent()->get_bool(name()) );
// 			}
// 			return false;
// 		}
// 
// 		
// 	// UINT
// 		BEntity_uint::BEntity_uint()
// 		: m_value(0)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 
// 		bool BEntity_uint::set( const Buint& value )
// 		{
// 			// std::cout << "BEntity_uint::set( const Buint& value ) " << name() << " " << id() << " to " << value << std::endl;
// 			if ( m_value != value )
// 			{
// 				m_value = value;
// // 				if ( do_update )
// 					onUpdate();
// 				return true;
// 			}
// 			return false;
// 		}
// 
// 		bool BEntity_uint::apply( BEntity* const e ) const
// 		{
// 			return e->set( m_value );
// 		}
// 
// 		Buint BEntity_uint::get_uint()
// 		{
// 			return m_value;
// 		}
// 
// 	// UINT_PROPERTY
// 		BEntity_uint_property::BEntity_uint_property()
// // 		: m_value(0)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 		
// 		bool BEntity_uint_property::set( const Buint& value )
// 		{
// 			if ( parent() /*&& value != m_value*/ )
// 			{
// 				return parent()->set( name(), value );
// // 				if ( parent()->set( name(), value ) )
// // 				{
// // 					m_value = value;
// // 					return true;
// // 				}
// 			}
// 			return false;
// 		}
// 
// 		Buint BEntity_uint_property::get_uint()
// 		{
// 			if ( parent() /*&& value != m_value*/ )
// 			{
// 				return parent()->get_uint( name() );
// 			}
// 			return 0;
// 		}
// 		
// 		bool BEntity_uint_property::apply( BEntity* const e )
// 		{
// 			// std::cout << "BEntity_float_property::apply" << std::endl;
// 			if ( parent() )
// 			{
// // 				return e->set( m_value );
// 				return e->set( parent()->get_uint(name()) );
// 			}
// 			return false;
// 		}
// 
// // 		void BEntity_uint::adminButtons( BEntity* hboxlayout, BEntity* plugin_manager )
// // 		{
// // // 			BEntity* button = hboxlayout->addChild("button_rm", plugin_manager->create( "qt5_button_draggable") );
// // // 				button->set("label", name());
// // 
// // 			BEntity* button_rm = hboxlayout->addChild("button_rm", plugin_manager->create( "qt5_button") );
// // 				button_rm->set("label", "rm");
// // 				BEntity* cmd_remove = button_rm->addChild("cmd_remove", new CMD_remove() );
// // 				cmd_remove->set(this);
// // 				button_rm->connectServerServer(cmd_remove);
// // 
// // 			BEntity* lineedit_value = hboxlayout->addChild("lineedit_value", plugin_manager->create( "qt5_lineedit") );
// // 				lineedit_value->set("value", m_value);
// // 				BEntity* lineedit_value_prop = lineedit_value->addChild("value", plugin_manager->create( "uint_property") );
// // 				connectServerServer(lineedit_value_prop);
// // 				lineedit_value_prop->connectServerServer(this);
// // 		}
// 
// 	// FLOAT
// 		BEntity_float::BEntity_float()
// 		: m_value(0.0f)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 
// 		bool BEntity_float::set( const Bfloat& value )
// 		{
// 			if ( m_value != value )
// 			{
// 				m_value = value;
// // 				if ( do_update )
// 					onUpdate();
// 				return true;
// 			}
// 			return false;
// 		}
// 
// 		bool BEntity_float::apply( BEntity* const e ) const
// 		{
// // 			std::cout << "applying " << m_value << std::endl;
// 			return e->set( m_value );
// 		}
// 
// 		Bfloat BEntity_float::get_float()
// 		{
// 			return m_value;
// 		}
// 
// 	// FLOAT_PROPERTY
// 		BEntity_float_property::BEntity_float_property()
// // 		: m_value(0.0f)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 		
// 		bool BEntity_float_property::set( const Bfloat& value )
// 		{
// 			if ( parent() /*&& value != m_value*/ )
// 			{
// 				return parent()->set( name(), value );
// // 				if ( parent()->set( name(), value ) )
// // 				{
// // 					m_value = value;
// // 					return true;
// // 				}
// 			}
// 			return false;
// 		}
// 
// // 		Bfloat* BEntity_float_property::get_float()
// // 		{
// // 			std::cout << "get_float" << std::endl;
// // 			if ( parent() )
// // 				return parent()->get_float(name());
// // 			return 0;
// // 		}
// 
// 		bool BEntity_float_property::apply( BEntity* const e )
// 		{
// 			// std::cout << "BEntity_float_property::apply" << std::endl;
// 			if ( parent() )
// 			{
// // 				return e->set( m_value );
// 				return e->set( parent()->get_float(name()) );
// 			}
// 			return false;
// 		}
// 
// 	// DOUBLE
// 		BEntity_double::BEntity_double()
// 		: m_value(0.0)
// 		{
// // 			setInput( new BEInput(this) );
// // 			setOutput( new BEOutput(this) );
// 		};
// 
// 		bool BEntity_double::set( const Bdouble& value )
// 		{
// 			if ( m_value != value )
// 			{
// 				m_value = value;
// // 				if ( do_update )
// 					onUpdate();
// 				return true;
// 			}
// 			return false;
// 		}
// 
// 		bool BEntity_double::apply( BEntity* const e ) const
// 		{
// // 			std::cout << "applying " << m_value << std::endl;
// 			return e->set( m_value );
// 		}
// 
// 		Bdouble BEntity_double::get_double()
// 		{
// 			return m_value;
// 		}
// 		
// 
// 	// STRING
// 		BEntity_string::BEntity_string()
// // 		: m_value(0.0f)
// 		{
// 		};
// 
// 		bool BEntity_string::set( const char* value )
// 		{
// 			if ( m_value != value )
// 			{
// 				m_value = value;
// 					onUpdate();
// 				return true;
// 			}
// 			return false;
// 		}
// 
// 		bool BEntity_string::apply( BEntity* const e ) const
// 		{
// 			return e->set( m_value.c_str() );
// 		}
// 
// 		Bstring* BEntity_string::get_string()
// 		{
// 			return &m_value;
// 		}
// 
// 	// STRING_PROPERTY
// 		BEntity_string_property::BEntity_string_property()
// 		{
// 		};
// 		
// 		bool BEntity_string_property::set( const char* value )
// 		{
// // 			std::cout << "BEntity_string_property::set " << value << std::endl;
// 			if ( parent() /*&& value != m_value*/ )
// 			{
// 				return parent()->set( name(), value );
// 			}
// 			return false;
// 		}
// 
// 		bool BEntity_string_property::apply( BEntity* const e )
// 		{
// 			// std::cout << "BEntity_string_property::apply" << std::endl;
// 			if ( parent() )
// 			{
// 				return e->set( (*parent()->get_string(name())).c_str() );
// 			}
// 			return false;
// 		}		
		
// 		void BEntity_float::adminButtons( BEntity* hboxlayout, BEntity* plugin_manager )
// 		{
// // 			BEntity* button = hboxlayout->addChild("button_rm", plugin_manager->create( "qt5_button_draggable") );
// // 				button->set("label", name());
// 
// 			BEntity* button_rm = hboxlayout->addChild("button_rm", plugin_manager->create( "qt5_button") );
// 				button_rm->set("label", "rm");
// 				BEntity* cmd_remove = button_rm->addChild("cmd_remove", new CMD_remove() );
// 				cmd_remove->set(this);
// 				button_rm->connectServerServer(cmd_remove);
// 
// 			BEntity* lineedit_value = hboxlayout->addChild("lineedit_value", plugin_manager->create( "qt5_lineedit") );
// 				lineedit_value->set("value", m_value);
// 				BEntity* lineedit_value_prop = lineedit_value->addChild("value", plugin_manager->create( "float_property") );
// 				connectServerServer(lineedit_value_prop);
// 				lineedit_value_prop->connectServerServer(this);
// 		}




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

		// ENTITIES
			else
			{
				BEntity* i(0);
				
				if ( type == CLASS::REFERENCE )
					i = new BEntity_reference();

				else if ( type == CLASS::EXTERNAL )
					i = new BEntity_external();

				else if ( type == CLASS::TRIGGER )
					i = new BEntity_trigger();

				else if ( type == CLASS::BOOL )
					i = new BEntity_bool();

				else if ( type == CLASS::BOOL_PROPERTY )
					i = new BEntity_bool_property();

				else if ( type == CLASS::UINT )
					i = new BEntity_uint();

				else if ( type == CLASS::UINT_PROPERTY )
					i = new BEntity_uint_property();
				
				else if ( type == CLASS::INT )
					i = new BEntity_int();

				else if ( type == CLASS::INT_PROPERTY )
					i = new BEntity_int_property();

				else if ( type == CLASS::FLOAT )
					i = new BEntity_float();

				else if ( type == CLASS::FLOAT_PROPERTY )
					i = new BEntity_float_property();
				
				else if ( type == CLASS::STRING )
					i = new BEntity_string();

				else if ( type == CLASS::STRING_PROPERTY )
					i = new BEntity_string_property();
				
				else
					std::cout << "BEntityTypes::create::Class implementation is missing" << std::endl;

				return i;
			}
	}

	extern "C" void destroy(BEntity* p)
	{
// 		std::cout << "LIB DESTROY:: " << p->id() << std::endl;
		delete p;
	}
		
