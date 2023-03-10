#include "be_entity_core_types.h"
#include <string.h>
#include <iostream>

	// REFERENCE
		BEntity_reference::BEntity_reference() : m_value(0) {};
		bool BEntity_reference::set( BEntity* value )
		{
			m_value = value;
			return true;
		}
		BEntity* BEntity_reference::get_reference()
		{
			return m_value;
		}

	// TRIGGER

		BEntity_trigger::BEntity_trigger()
		{
// // 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};
	
		bool BEntity_trigger::set()
		{
// 			std::cout << "BEntity_trigger::set : " << id() << std::endl;
			onUpdate();
			return true;
		}

		bool BEntity_trigger::apply( BEntity* e )
		{
// 			std::cout << "BEntity_trigger::apply : " << id() << std::endl;
			return e->set();
		}

	// BOOL
		BEntity_bool::BEntity_bool()
		: m_value(false)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};

		bool BEntity_bool::set( const Bbool& value )
		{
			if ( m_value != value )
			{
				m_value = value;
// 				if ( do_update )
					onUpdate();
				return true;
			}
			return false;
		}

		bool BEntity_bool::apply( BEntity* e )
		{
			return e->set( m_value );
		}

		Bbool BEntity_bool::get_bool()
		{
			return m_value;
		}

	// BOOL_PROPERTY
		BEntity_bool_property::BEntity_bool_property()
// 		: m_value(0)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};
		
		bool BEntity_bool_property::set( const Bbool& value )
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->set( name(), value );
// 				if ( parent()->set( name(), value ) )
// 				{
// 					m_value = value;
// 					return true;
// 				}
			}
			return false;
		}

		Bbool BEntity_bool_property::get_bool()
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->get_bool( name() );
			}
			return 0;
		}
		
		bool BEntity_bool_property::apply( BEntity* e )
		{
			// std::cout << "BEntity_float_property::apply" << std::endl;
			if ( parent() )
			{
// 				return e->set( m_value );
				return e->set( parent()->get_bool(name()) );
			}
			return false;
		}

		
	// UINT
		BEntity_uint::BEntity_uint()
		: m_value(0)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};

		bool BEntity_uint::set( const Buint& value )
		{
			if ( m_value != value )
			{
// 				if ( name() == "value" )
// 					std::cout << "BEntity_uint::set( const Buint& value ) " << name() << " " << id() << " to " << value << std::endl;

				m_value = value;
// 				if ( do_update )
					onUpdate();
				return true;
			}
			return false;
		}

// 		bool BEntity_uint::set( BEntity* entity )
// 		{
// 			// std::cout << "BEntity_uint::set( const Buint& value ) " << name() << " " << id() << " to " << value << std::endl;
// 			if ( m_value != entity->get_uint() )
// 			{
// 				m_value = entity->get_uint();
// // 				if ( do_update )
// 					onUpdate();
// 				return true;
// 			}
// 			return false;
// 		}

		bool BEntity_uint::apply( BEntity* e )
		{
// 			std::cout << "BEntity_uint::apply to " << e->id() << " to " << m_value << std::endl;
			return e->set( m_value );
		}

		Buint BEntity_uint::get_uint()
		{
			return m_value;
		}

	// UINT_PROPERTY
		BEntity_uint_property::BEntity_uint_property()
// 		: m_value(0)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};
		
		bool BEntity_uint_property::set( const Buint& value )
		{
			if ( parent() /*&& value != m_value*/ )
			{
// 				std::cout << "BEntity_uint_property::set( const Buint& value ) " << parent()->name() << " " << id() << " to " << value << std::endl;
				return parent()->set( name(), value );
// 				if ( parent()->set( name(), value ) )
// 				{
// 					m_value = value;
// 					return true;
// 				}
			}
			return false;
		}

		Buint BEntity_uint_property::get_uint()
		{
			if ( parent() /*&& value != m_value*/ )
			{
// 				std::cout << "BEntity_uint_property::get_uint() " << parent()->name() << " " << id() << " returns " << parent()->get_uint( name() ) << std::endl;
				return parent()->get_uint( name() );
			}
			return 0;
		}
		
		bool BEntity_uint_property::apply( BEntity* e )
		{
			// std::cout << "BEntity_float_property::apply" << std::endl;
			if ( parent() )
			{
// 				std::cout << "BEntity_uint_property::apply( BEntity* e ) " << parent()->name() << " " << id() << " to " << parent()->get_uint( name() ) << std::endl;
				return e->set( parent()->get_uint( name() ) );
			}
			return false;
		}

		bool BEntity_uint_property::set( BEntity* entity )
		{
// 			std::cout << "BEntity_uint_property::set( BEntity* entity ) " << parent()->name() << " " << id() << " to " << entity->get_uint() << std::endl;
// 			if ( parent()->get_uint( name() ) != entity->get_uint() )
// 			{
				return parent()->set( name(), entity->get_uint() );
// 				onUpdate();
// 				return true;
// 			}
// 			return false;
		}		
// 		void BEntity_uint::adminButtons( BEntity* hboxlayout, BEntity* plugin_manager )
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
// 				BEntity* lineedit_value_prop = lineedit_value->addChild("value", plugin_manager->create( "uint_property") );
// 				connectServerServer(lineedit_value_prop);
// 				lineedit_value_prop->connectServerServer(this);
// 		}

	// INT
		bool BEntity_int::set( const Bint& value )
		{
			if ( compareAndSetValue( m_value, value ) )
			{
				onUpdate();
				return true;
			}
			return false;
		}
		
	// INT_PROPERTY
		BEntity_int_property::BEntity_int_property()
		{
		};
		
		bool BEntity_int_property::set( const Bint& value )
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->set( name(), value );
			}
			return false;
		}

		Bint BEntity_int_property::get_int()
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->get_int( name() );
			}
			return 0;
		}
		
		bool BEntity_int_property::apply( BEntity* e )
		{
			if ( parent() )
			{
				return e->set( parent()->get_int( name() ) );
			}
			return false;
		}

		bool BEntity_int_property::set( BEntity* entity )
		{
			return parent()->set( name(), entity->get_int() );
		}

	// FLOAT
		BEntity_float::BEntity_float()
		: m_value(0.0f)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};

		bool BEntity_float::set( const Bfloat& value )
		{
			if ( m_value != value )
			{
				m_value = value;
// 				if ( do_update )
					onUpdate();
				return true;
			}
			return false;
		}

		bool BEntity_float::apply( BEntity* e )
		{
// 			std::cout << "applying " << m_value << std::endl;
			return e->set( m_value );
		}

		Bfloat BEntity_float::get_float()
		{
			return m_value;
		}

	// FLOAT_PROPERTY
		BEntity_float_property::BEntity_float_property()
// 		: m_value(0.0f)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};
		
		bool BEntity_float_property::set( const Bfloat& value )
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->set( name(), value );
// 				if ( parent()->set( name(), value ) )
// 				{
// 					m_value = value;
// 					return true;
// 				}
			}
			return false;
		}
		
		Bfloat BEntity_float_property::get_float()
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->get_float( name() );
			}
			return 0.0f;
		}
		
		bool BEntity_float_property::apply( BEntity* e )
		{
			if ( parent() )
			{
				return e->set( (Bfloat)parent()->get_float( name() ) );
			}
			return false;
		}

	// DOUBLE
		BEntity_double::BEntity_double()
		: m_value(0.0)
		{
// 			setInput( new BEInput(this) );
// 			setOutput( new BEOutput(this) );
		};

		bool BEntity_double::set( const Bdouble& value )
		{
			if ( m_value != value )
			{
				m_value = value;
// 				if ( do_update )
					onUpdate();
				return true;
			}
			return false;
		}

		bool BEntity_double::apply( BEntity* e )
		{
// 			std::cout << "applying " << m_value << std::endl;
			return e->set( m_value );
		}

		Bdouble BEntity_double::get_double()
		{
			return m_value;
		}
		

// 	// STRING
// 		BEntity_string::BEntity_string()
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
// 		bool BEntity_string::apply( BEntity* e )
// 		{
// 			return e->set( m_value.c_str() );
// 		}
// 
// 		Bstring* BEntity_string::get_string()
// 		{
// 			return &m_value;
// 		}

	// STRING
		BEntity_string::BEntity_string()
		: m_value(0)
		{
		};
		
		BEntity_string::~BEntity_string()
		{
			if ( m_value != 0 )
				free(m_value);
		};


		bool BEntity_string::set( const char* value )
		{
			if (m_value)
			{
				if ( m_value != value )
				{
					free(m_value);
					m_value = strdup(value);
						onUpdate();
					return true;
				}
			}
			else
			{
				m_value = strdup(value);
					onUpdate();
				return true;
			}
			return false;
		}

		bool BEntity_string::apply( BEntity* e )
		{
			return e->set( m_value );
		}

		const char* BEntity_string::get_string()
		{
			return m_value;
		}

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
// 		bool BEntity_string_property::apply( BEntity* e )
// 		{
// 			// std::cout << "BEntity_string_property::apply" << std::endl;
// 			if ( parent() )
// 			{
// 				return e->set( (*parent()->get_string(name())).c_str() );
// 			}
// 			return false;
// 		}		
// 		


	// STRING_PROPERTY
		BEntity_string_property::BEntity_string_property()
		{
		};
		
		const char* BEntity_string_property::get_string()
		{
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->get_string( name() );
			}
			return "";
		}

		bool BEntity_string_property::set( const char* value )
		{
// 			std::cout << "BEntity_string_property::set " << value << std::endl;
			if ( parent() /*&& value != m_value*/ )
			{
				return parent()->set( name(), value );
			}
			return false;
		}

		bool BEntity_string_property::apply( BEntity* e )
		{
			// std::cout << "BEntity_string_property::apply" << std::endl;
			if ( parent() )
			{
				return e->set( parent()->get_string( name()) );
			}
			return false;
		}		
		
