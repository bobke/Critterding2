#include "be_entity_interface.h"
#include "be_entity_core_types.h"
// #include "be_timer.h"
#include "be_entity_io_handler.h"

#include "be_entity_children_handler.h"
#include "be_lib_handler.h"
#include <iostream>
// #include <sstream>

		BEntity::BEntity() 
		: m_id(0)
		, m_be_parent(0)
		, m_io_handler(0)
		, m_flagbits(0)
		{
		}

	// SET VALUES
		// bool BEntity::set() { return false; }
		bool BEntity::set()
		{
			// special case for copying non primitives
			return onUpdate();
		}
		
		bool BEntity::set( BEntity* value )
		{ 
			std::cout << "WARNING: BEntity::set(BEntity*) not overloaded for entity " << id() << "(" << name() << ")" << " to " << value->id() << "(" << value->name() << ")" << std::endl;
			return false;
		}

		bool BEntity::set( const bool& value )
		{
			std::cout << "WARNING: BEntity::set( const Bbool value ) not overloaded for entity " << id() << " to " << class_id() << std::endl;
			(void)value; return false;
		}

		bool BEntity::set( const Buint& value )
		{
			std::cout << "WARNING: BEntity::set( const Buint& value ) not overloaded for entity " << id() << " to " << class_id() << std::endl;
			(void)value; return false;
		}

		bool BEntity::set( const Bint& value )
		{
			std::cout << "WARNING: BEntity::set( const Bint& value ) not overloaded for entity " << id() << " to " << class_id() << std::endl;
			(void)value; return false;
		}

		bool BEntity::set( const Bfloat& value )
		{
			std::cout << "WARNING: BEntity::set( const Bfloat& value ) not overloaded for entity " << id() << " to " << class_id() << std::endl;
			(void)value; return false;
		}

		bool BEntity::set( const Bdouble& value )
		{
			std::cout << "WARNING: BEntity::set( const Bdouble& value ) not overloaded for entity " << id() << " to " << class_id() << std::endl;
			(void)value; return false;
		}

// 		bool BEntity::set( const Bstring& value )
// 		{
// 			set( value.c_str() );
// 		}

		bool BEntity::set( const char* value )
		{
// 			std::cout << "WARNING: BEntity::set( const char* value ) not overloaded for entity " << id() << "(" << name() << ")" << " to " << value << std::endl;
			(void)value; return false;
		}

	// GET VALUES
		BEntity* BEntity::get_reference()
		{
			std::cout << "BEntity::get_reference(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return 0;
		}

		Bbool BEntity::get_bool()
		{
			std::cout << "BEntity::get_bool(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return false;
		}

		Buint BEntity::get_uint()
		{
			std::cout << "BEntity::get_uint(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return 0;
		}

		Bint BEntity::get_int()
		{
			std::cout << "BEntity::get_int(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return 0;
		}

		Bfloat BEntity::get_float()
		{
			std::cout << "BEntity::get_float(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return 0.0f;
		}

		Bdouble BEntity::get_double()
		{
			std::cout << "BEntity::get_double(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return 0.0;
		}

// 		Bstring* BEntity::get_string()
// 		{
// 			std::cout << "BEntity::get_string(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
// 			return 0;
// 		}

		const char* BEntity::get_string()
		{
			std::cout << "BEntity::get_string(): should be overriding this entity " << id() << "(" << class_id() << ")" << std::endl;
			return 0;
		}

		
		BEntity* BEntity::get_reference( const Bstring& id )
		{
			std::cout << "BEntity::get_reference(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0;
		}

		Bbool BEntity::get_bool( const Bstring& id )
		{
			std::cout << "BEntity::get_uint(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0;
		}

		Buint BEntity::get_uint( const Bstring& id )
		{
			std::cout << "BEntity::get_uint(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0;
		}

		Bint BEntity::get_int( const Bstring& id )
		{
			std::cout << "BEntity::get_int(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0;
		}

		Bfloat BEntity::get_float( const Bstring& id )
		{
			std::cout << "BEntity::get_float(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0.0f;
		}

		Bdouble BEntity::get_double( const Bstring& id )
		{
			std::cout << "BEntity::get_double(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0.0f;
		}
// 		Bstring* BEntity::get_string( const Bstring& id )
// 		{
// 			std::cout << "BEntity::get_string(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
// 			(void)id;
// 			return 0;
// 		}

		const char* BEntity::get_string( const Bstring& id )
		{
			std::cout << "BEntity::get_string(id): wrong type for entity " << id << "(" << class_id() << ")" << std::endl;
			(void)id;
			return 0;
		}

	// SET NAMED VALUES
		bool BEntity::set( const Bstring& id, BEntity* value )
		{
			std::cout << "BEntity::set( const Bstring& id, BEntity* value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}

		bool BEntity::set( const Bstring& id, const Bbool& value ) // FIXME KILLS SHIT WHEN UNCOMMENTED
		{
			std::cout << "BEntity::set( const Bstring& id, const Bbool& value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}

		bool BEntity::set( const Bstring& id, const Buint& value )
		{
			std::cout << "BEntity::set( const Bstring& id, const Buint& value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}

		bool BEntity::set( const Bstring& id, const Bint& value )
		{
			std::cout << "BEntity::set( const Bstring& id, const Bint& value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}

		bool BEntity::set( const Bstring& id, const Bfloat& value )
		{
			std::cout << "BEntity::set( const Bstring& id, const Bfloat& value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}

		bool BEntity::set( const Bstring& id, const Bdouble& value )
		{
			std::cout << "BEntity::set( const Bstring& id, const Bdouble& value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}

// 		bool BEntity::set( const Bstring& id, const Bstring& value )
// 		{
// 			set( id, value.c_str() );
// 		}

		bool BEntity::set( const Bstring& id, const char* value )
		{
			std::cout << "BEntity::set( const Bstring& id, const char* value ): should be overriding this entity " << id << std::endl;
			(void)id; (void)value; return false;
		}


		template <typename T>
		bool BEntity::compareAndSetValue (T& original, T const& value)
		{
			if ( original != value )
			{
				original = value;
				return true;
			}
			return false;
		}

		template bool BEntity::compareAndSetValue<Bbool>(Bbool&, const Bbool&);
		template bool BEntity::compareAndSetValue<Buint>(Buint&, const Buint&);
		template bool BEntity::compareAndSetValue<Bint>(Bint&, const Bint&);
		template bool BEntity::compareAndSetValue<Bfloat>(Bfloat&, const Bfloat&);
		template bool BEntity::compareAndSetValue<Bdouble>(Bdouble&, const Bdouble&);
		template bool BEntity::compareAndSetValue<Bstring>(Bstring&, const Bstring&);

		// BEntity* exception
		bool BEntity::compareAndSetValue (BEntity*& original, BEntity* value)
		{
			if ( original != value )
			{
				original = value;
				return true;
			}
			return false;
		}

	// PROCESSING
		void BEntity::process_general()
		{
// 				if ( hasAdminInfo() )
// 				{
// 					BEntityPt admin_window( topParent()->get("bengine admin window") );
// 					B_Admin_Handler admin_handler;
// 					admin_handler.highlight(this, m_admin_info->getSection(), admin_window);
// 
// 					// PROCESS
// 						process_local();
// // 						usleep(200000);
// 					
// 					admin_handler.lowlight(this, m_admin_info->getSection(), admin_window);
// 				}
// 				else
// 				{
				
					// PROCESS
						process();
				
					// CHILDREN
						process_children();
						
					// POST PROCESS
// 						process_post();
		}

// 		void BEntity::process_children_post() const
// 		{
// 			if ( m_child_handler != 0 )
// 				m_child_handler->process_post();
// 		}

		void BEntity::process_children() const
		{
			if ( hasChildren() )
			{
				for_all_children
				{
					(*child)->process_general();
				}
			}
		}

		Bbool BEntity::hasProcessing() const
		{
			return getNthBit(m_flagbits, 2);
// 			return m_has_processing;
		}

		void BEntity::setProcessing()
		{
			setNthBit(m_flagbits, 2);
		}
		
		Bbool BEntity::hasDeferredProcessing() const
		{
			return getNthBit(m_flagbits, 3);
// 			return m_has_deferred_processing;
		}

		void BEntity::addProcessing()
		{
				addProcessing( this );
		}
		
		void BEntity::addProcessing(BEntity* entity)
		{
			parent()->addProcessing( entity );
		}

		void BEntity::removeProcessing()
		{
			if ( hasProcessing() )
				removeProcessing( this );
		}
		
		void BEntity::removeProcessing(BEntity* entity)
		{
			parent()->removeProcessing( entity );
		}

	// NAME
		void BEntity::setName(const std::string& entityName)
		{
			addName( this, entityName );
			//if ( isProxyEntity() )
			//	m_message_server->send( net_message_change_name(BEUInt(id()), BEString(m_be_name.c_str())) );
		}
		void BEntity::addName(BEntity* entity, const std::string& entityName)
		{
			parent()->addName( entity, entityName );
			//if ( isProxyEntity() )
			//	m_message_server->send( net_message_change_name(BEUInt(id()), BEString(m_be_name.c_str())) );
		}

		void BEntity::removeName()
		{
			removeName( this );
		}
		
		void BEntity::removeName(BEntity* entity)
		{
			parent()->removeName( entity );
		}

		const std::string& BEntity::name()
		{
			return name( this );
		}

		std::string& BEntity::name(BEntity* entity)
		{
			return parent()->name( entity );
		}
		
	// FPS
		void BEntity::setFps(const Buint fps)
		{
			addFps( this, fps );
		}
		void BEntity::addFps(BEntity* entity, const Buint fps)
		{
			parent()->addFps( entity, fps );
		}

		void BEntity::removeFps()
		{
			removeFps( this );
		}
		
		void BEntity::removeFps(BEntity* entity)
		{
			parent()->removeFps( entity );
		}

		Buint BEntity::fps()
		{
			return fps( this );
		}

		Buint BEntity::fps(BEntity* entity)
		{
			return parent()->fps( entity );
		}		
		
	// ID
		Buint64 BEntity::id() const { return m_id; }
		void BEntity::setID(const Buint64 t_id) { m_id = t_id; }

		void BEntity::setIDRecyclable()
		{
			setNthBit(m_flagbits, 0);
		}
		
		Bbool BEntity::isIDRecyclable() const
		{
			return getNthBit(m_flagbits, 0);
		}

		void BEntity::setDelayReuseID()
		{
			setNthBit(m_flagbits, 1);
		}

		Bbool BEntity::hasDelayReuseID() const
		{
			return getNthBit(m_flagbits, 1);
		}

	// ADMIN WINDOW
		BEntity* BEntity::getAdminWindow()
		{
			return parent()->getAdminWindow();
		}
		void BEntity::setAdminWindow( BEntity* entity )
		{
			parent()->setAdminWindow( entity );
		}

	// IS ADMIN FLAG
		void BEntity::setIsAdmin()
		{
			setNthBit(m_flagbits, 6);
		}

		void BEntity::unsetIsAdmin()
		{
			setNthBit(m_flagbits, 6, false);
		}

		bool BEntity::isAdmin() const
		{
			return getNthBit(m_flagbits, 6);
		}

	// HAS ADMIN FLAG
		void BEntity::setHasAdmin()
		{
			setNthBit(m_flagbits, 7);
		}

		void BEntity::unsetHasAdmin()
		{
			setNthBit(m_flagbits, 7, false);
		}
		
		bool BEntity::hasAdmin() const
		{
			return getNthBit(m_flagbits, 7);
		}
		
	// CHILDREN
		B_Children_Handler* BEntity::childHandler() const
		{
			return parent()->childHandler();
		}

		BEntity* BEntity::addChild( const std::string& name, const std::string& entityClass )
		{
			return addChild( name, "", entityClass );
		}

		BEntity* BEntity::addChild( const std::string& name, const std::string& library, const std::string& entityClass )
		{
			// PRIMITIVES
				if ( entityClass == "entity" )
					return addChild(name, new BEntity());

				if ( entityClass == "reference" )
					return addChild(name, new BEntity_reference());

				if ( entityClass == "external_child" )
					return addChild(name, new BEntity_external());

				if ( entityClass == "trigger" )
					return addChild(name, new BEntity_trigger());

				if ( entityClass == "bool" )
					return addChild(name, new BEntity_bool());

				if ( entityClass == "bool_property" )
					return addChild(name, new BEntity_bool_property());

				if ( entityClass == "uint" )
					return addChild(name, new BEntity_uint());

				if ( entityClass == "uint_property" )
					return addChild(name, new BEntity_uint_property());
				
				if ( entityClass == "int" )
					return addChild(name, new BEntity_int());

				if ( entityClass == "int_property" )
					return addChild(name, new BEntity_int_property());

				if ( entityClass == "float" )
					return addChild(name, new BEntity_float());

				if ( entityClass == "float_property" )
					return addChild(name, new BEntity_float_property());
				
				if ( entityClass == "string" )
					return addChild(name, new BEntity_string());

				if ( entityClass == "string_property" )
					return addChild(name, new BEntity_string_property());

			return addChild(name, pluginManager()->create( this, library, entityClass ));
		}

		BEntity* BEntity::addChild( const std::string& name, BEntity* const entity )
		{
			if ( entity != 0 )
			{
				// std::cout << "name: " << name << " being added to " << this->name() << std::endl;

				addChild( entity );
				if (!name.empty())
				{
					if ( name == "_external_child" )
					{
						std::cout << "!!!!!!!!!!!" << this->name() << " got a _external_child" << std::endl;
						exit(0);
					}
					entity->setName( name );
				}
				entity->construct();

				// set all children builtin
				entity->markBuiltinChildren();

				// admin
				if ( entity->parent()->hasAdmin() )
				{
					if ( topParent() )
					{
						auto admin_app = entity->parent()->getAdminWindow();
						if ( admin_app )
						{
							admin_app->set( "add", entity );
						}
					}
				}

// 				if ( topParent() )
// 				{
// 					auto scene = topParent()->getChild("Scene", 1);
// 					if ( scene )
// 					{
// 						auto admin_app = scene->getChild("Admin App", 2);
// 						if ( admin_app )
// 						{
// 							auto admin_app_search_entity = admin_app->getChild("qt vboxlayout", 6);
// 							
// 							if ( admin_app_search_entity )
// 							{
// 								auto cmdbuffer = topParent()->getChild("_command_buffer", 1);
// 								
// 								// FIXME SLOW AF
// 								std::stringstream stream;
// 								stream << "admin_section_" << this->id() << "_" << this->name();
// 								auto admin_section = admin_app_search_entity->getChild( stream.str().c_str() );
// 								if ( admin_section )
// 								{
// 									auto groupbox = admin_section->getChild("qt groupbox entities", 1);
// 									if ( groupbox )
// 									{
// 										auto vlayout = groupbox->getChild("qt vboxlayout", 1);
// 										if ( vlayout )
// 										{
// 											auto cmdref = cmdbuffer->addChild("admin_entity_add", new BEntity_reference() );
// 											cmdref->set( entity );
// 											cmdref->addChild("vlayout", new BEntity_reference() )->set( vlayout );
// 										}
// 									}
// 								}
// 								
// 							}
// 							
// 						}
// 					}
// 				}

			}
			return entity;
		}

		BEntity* BEntity::addChild( BEntity* const entity )
		{
			if ( childHandler()->addChild( this, entity ) )
			{
				return entity;
			}
			return 0;
		}

		Bbool BEntity::onAddChild( BEntity* entity )
		{
			if (entity)
				return true;
			return false;
		}

		bool BEntity::removeChild( BEntity* const entity )
		{
// 			// REMOVE ADMIN ITEMS
// 			// FIXME SLOW AF
// 				if ( topParent() )
// 				{
// 					auto scene = topParent()->getChild("Scene", 1); // FIXME DOING IT TWICE? (getadminwindow)
// 					if ( scene )
// 					{
// 						auto admin_app = scene->getChild("Admin App", 2);
// 
// 						// auto admin_app = getAdminWindow();
// 						if ( admin_app )
// 						{
// 							admin_app->set( "rm", entity );
// 							
// // 							// if ( entity->parent()->name() != "_command_buffer")
// // 							{
// // 								auto admin_app_search_entity = admin_app->getChild("qt vboxlayout", 6);
// // 							
// // 								if ( admin_app_search_entity )
// // 								{
// // 									std::stringstream stream;
// // 									stream << "admin_section_" << entity->id() << "_" << entity->name();
// // 									auto admin_section = admin_app_search_entity->getChild( stream.str().c_str() );
// // 									if ( admin_section )
// // 									{
// // 										// std::cout << "SHOULD REMOVE " << stream.str() << std::endl;
// // 										admin_section->parent()->removeChild( admin_section );
// // 									}
// // 								}
// // 							}
// 							
// 						}
// 					}
// 				}

			return childHandler()->removeChild( this, entity );
		}

		Bbool BEntity::onRemoveChild( BEntity* entity )
		{
			if (entity)
				return true;
			return false;
		}

		void BEntity::clearChildren()
		{
			if ( hasChildren() )
			{
				childHandler()->clearChildren( this );
			}
		}

		Bbool BEntity::hasChildren() const
		{
			return getNthBit(m_flagbits, 4);
		}

		void BEntity::setHasChildren( const bool value )
		{
			setNthBit(m_flagbits, 4, value);
		}

		const BEntityVector& BEntity::children() const
		{
			return childHandler()->children( this );
		}

		BEntity* BEntity::getChild(const char* name, const unsigned int max_levels)
		{
			// std::cout << "getChild::" << name << " " << std::endl;
			if ( max_levels > 0 && hasChildren() )
			{
				// first try to find on this level
				const auto& children_vector = childHandler()->children(this);
				const auto& begin(children_vector.begin());
				const auto& end(children_vector.end());
				for ( auto it(begin); it != end; ++it )
				{
					if ( std::string((*it)->name()) == std::string(name) )
					{
						return (*it);
					}
				}

				// reloop and pass on to children, but level -1
				if ( max_levels > 1 )
				{
					for ( auto it(begin); it != end; ++it )
					{
						BEntity* found_entity = (*it)->getChild(name, max_levels - 1);
						if ( found_entity )
						{
							return found_entity;
						}
					}
				}
			}

			return 0;
		}

	// NUMBER OF CHILDREN
		Buint BEntity::numChildren() const
		{
			return childHandler()->numChildren( this );
		}

		Buint BEntity::numTotalChildren() const
		{
			return childHandler()->numTotalChildren( this );
		}

	// PLUGIN_MANAGER
		BEntity_Plugin_Manager* BEntity::pluginManager() const
		{
			return parent()->pluginManager();
		}

	// PARENT INFO
		// FIXME be_parent()
		BEntity* BEntity::parent() const
		{
			return m_be_parent;
		}

		void BEntity::setParent( BEntity* const parent )
		{
			// std::cout << "BEntity::setParent:" << id() << " has parent " << parent->id() << std::endl;
			m_be_parent = parent;
		}
	
		bool BEntity::hasParent() const
		{
			BEntity* e = parent();
			if ( e != 0 )
				return true;
			return false;
		}

		bool BEntity::hasParent( const Buint64 t_id ) const
		{
			BEntity* e = parent();
			if ( e != 0 )
			{
				if ( e->id() == t_id )
				{
					return true;
				}

				while ( e->parent() != 0 )
				{
					if ( e->id() == t_id )
					{
						return true;
					}
					e = e->parent();
				}
			}
			return false;
		}
		
		BEntity* BEntity::topParent() const
		{
			// FIXME CHECK if this is the topparent
			if ( m_be_parent != 0 )
			{
				BEntity* top_parent = m_be_parent;
				while ( top_parent->parent() != 0 )
					top_parent = top_parent->parent();
				return top_parent;
			}
			return 0;

		}

	// TOP FUNCTIONS
		BEntity* BEntity::getNearestTop()
		{
			return parent()->getNearestTop();
		}
		bool BEntity::getNearestTopConnectionType()
		{
			return parent()->getNearestTopConnectionType();
		}

		
	// BUILTIN FLAG
		void BEntity::setBuiltin()
		{
			setNthBit(m_flagbits, 5);
			markBuiltinChildren();

// 			m_builtin = true;
		}

		bool BEntity::isBuiltin() const
		{
			return getNthBit(m_flagbits, 5);
// 			return m_builtin;
		}

		void BEntity::markBuiltinChildren()
		{
			for_all_children
			{
				(*child)->setBuiltin();		// MARK child as a builtin, so it doesn't copy when entity_copy_callback			
				
				// and external children
				if ( dynamic_cast<BEntity_external*>( *child ) )
				{
					(*child)->get_reference()->setBuiltin();
				}
			}
		}

	// INPUT / OUTPUT
		bool BEntity::hasIOHandler() const
		{
			if ( m_io_handler != 0 )
			{
				return true;
			}
			return false;
		}

		void BEntity::deleteIOHandler()
		{
			if ( m_io_handler != 0 )
			{
				delete m_io_handler;
				m_io_handler = 0;
			}
		}

		void BEntity::connectServerServer(BEntity* entity_with_input, const bool force_local)
		{
			// CREATE AN OUTPUT HERE
				if ( m_io_handler == 0 )
				{
					m_io_handler = new B_IO_Handler();
				}
				m_io_handler->connectServerServer(this, entity_with_input, force_local);
		}
		
// 		void BEntity::disconnectServerServer( BEntity* entity_with_input )
// 		{
// 			if ( m_io_handler != 0 )
// 			{
// 				m_io_handler->disconnectServerServer(this, entity_with_input);
// 			}
// 			else
// 				std::cout << "BEntity::disconnectServerServer::IO handler is missing" << std::endl;
// 		}

		bool BEntity::hasInput() const
		{
			if ( m_io_handler != 0 )
			{
				return m_io_handler->hasInput();
			}
			return false;
		}

		bool BEntity::hasOutput() const
		{
			if ( m_io_handler != 0 )
			{
				return m_io_handler->hasOutput();
			}
			return false;
		}

		void BEntity::spawnInput()
		{
			if ( m_io_handler == 0 )
			{
				m_io_handler = new B_IO_Handler();
			}
			if ( !m_io_handler->getInput() ) // FIXME move this stuff into io_handler connectServerServer
			{
				m_io_handler->setInput( new BEInput(this) );
			}
		}

		BEInput* BEntity::getInput() const
		{
			if ( m_io_handler != 0 )
			{
				return m_io_handler->getInput();
			}
			return 0;
		}

		BEOutput* BEntity::getOutput() const
		{
			if ( m_io_handler != 0 )
			{
				return m_io_handler->getOutput();
			}
			return 0;
		}
		
		bool BEntity::apply( BEntity* e )
		{
			(void)e; // this avoids a compile warning
			return false;
		}

		bool BEntity::onUpdate() const
		{
			if ( hasOutput() )
			{
				getOutput()->commit();

// 				bool committed = getOutput()->commit();
// 				if ( !committed )
// 				{
// 					std::cout << "BEntity::onUpdate() : ENTITY HAS OUTPUT BUT IS NOT A BASE TYPE / COMPONENT : signal to copy binary" << std::endl;
// 					// FIXME hackish
// 					return false;
// 				}
			}
			return true;
		}

	// COMMAND BUFFER
		BEntity* BEntity::getCommandBuffer()
		{
			return parent()->getCommandBuffer();
		}
		
	// FLAG OPERATIONS
		Bbool BEntity::getNthBit(char packedValue, const int selectedBitIndex) const
		{ 
			return packedValue & (1<<selectedBitIndex); 
		}

		void BEntity::setNthBit(char & packedValue, const int selectedBitIndex, const bool value) const
		{
			if ( value )
				packedValue = packedValue | (1<<selectedBitIndex); 
			else
				packedValue = packedValue & ~(1<<selectedBitIndex);
		} 
		
		
