#include "be_lib_handler.h"
#include "be_entity_core_types.h"
#include <dlfcn.h>
#include <iostream>

	// CLASS TRANSLATION
		void BClassTranslationMap::add( const char* a, const char* b )
		{
			m_translation_map.insert( std::make_pair( a, b ) );
			// m_translation_map.insert( std::make_pair( b, a ) );
		}

		const char* BClassTranslationMap::get_string( const Bstring& id )
		{
			for ( auto it = m_translation_map.begin(); it != m_translation_map.end(); it++ )
			{
				if ( it->first == id )
					return it->second;
			}

			return id.c_str();
		}

	BEntity_Plugin::BEntity_Plugin()
	 : m_sceneLibHandle(0)
	 , m_create_plugin(0)
	 , m_destroy_plugin(0)
	{
	}

	BEntity_Plugin::~BEntity_Plugin()
	{
		// #ifndef NDEBUG
			// NOTE COMMENTING THIS FIXES (<unknown module>) IN DEBUGGING
			if ( m_sceneLibHandle != 0 )
				dlclose(m_sceneLibHandle);
		// #endif
		
		m_create_plugin = 0;
		m_destroy_plugin = 0;
		
	}

	void BEntity_Plugin::destroy( BEntity* e )
	{
		std::cout << "destroying" << std::endl;
		e->clearChildren();
		m_destroy_plugin( e );
	}

	const std::string& BEntity_Plugin::error() const
	{
		return m_error;
	}

	bool BEntity_Plugin::open( const std::string& dir, const std::string& lib )
	{
		m_location = dir;
		m_filename = lib;
		
		if ( !open( m_location+"/lib"+m_filename+".so" ) )
		{ 
			std::cout << error() << std::endl;
			// exit(1);
			return false;
		}
		BEntity* e = addChild("Classes", new BEntity());
		create(e, 0);

		return true;
	}

	bool BEntity_Plugin::open( const std::string& location )
	{
		// LOAD SCENE LIB
			m_sceneLibHandle = dlopen(location.c_str(), RTLD_NOW);
			if (!m_sceneLibHandle)
			{
				m_error = "BeLibHandler::open: " + std::string(dlerror());
				return false;
			}

		// RESET ERRORS
			dlerror();

		// LOAD THE SYMBOLS
			m_create_plugin = (create_t*) dlsym(m_sceneLibHandle, "create");
			const char* dlsym_error = dlerror();
			if (dlsym_error)
			{
				m_error = "BeLibHandler::open: Cannot load symbol 'create': " + std::string(dlsym_error);
				return false;
			}
			
			m_destroy_plugin = (destroy_t*) dlsym(m_sceneLibHandle, "destroy");
			dlsym_error = dlerror();
			if (dlsym_error)
			{
				m_error = "BeLibHandler::open: Cannot load symbol 'destroy': " + std::string(dlsym_error);
				return false;
			}
		return true;
	}

	BEntity* BEntity_Plugin::create( BEntity* parent, const Buint id )
	{
		return m_create_plugin( parent, id ); // FIXME MEMLEAK
	}




	BEntity_Plugin* BEntity_Plugin_Manager::load( const std::string& name, const std::string& dir, const std::string& lib )
	{
		auto t_found = getChild(name.c_str(), 1);
		if ( t_found )
			return 0;

		BEntity_Plugin* t(new BEntity_Plugin());
		addChild(name, t);
		if ( !t->open( dir, lib ) )
		{
			return 0;
		}
		return t;
	}

	Bbool BEntity_Plugin_Manager::onAddChild( BEntity* entity )
	{
		auto tmap = dynamic_cast<BClassTranslationMap*>( entity );
		if ( tmap )
		{
			m_use_translation_map = tmap;
			return true;
		}
		return false;
	}

	Bbool BEntity_Plugin_Manager::onRemoveChild( BEntity* entity )
	{
		if ( m_use_translation_map == entity )
		{
			m_use_translation_map = 0;
			return true;
		}
		return false;
	}
	
	BEntity* BEntity_Plugin_Manager::create( BEntity* parent, const std::string& name )
	{
		return create( parent, "", name );
	}

	BEntity* BEntity_Plugin_Manager::create( BEntity* parent, const std::string& library, const std::string& name )
	{
		// IF TRANSLATION ENTITY FIND NEW NAME
		std::string newName;
		if ( m_use_translation_map != 0 )
		{
			newName = m_use_translation_map->get_string( name );
		}
		else
		{
			newName = name;
		}
		
		// PRIMITIVES
			if ( newName == "entity" )
				return new BEntity();

			if ( newName == "reference" )
				return new BEntity_reference();

			if ( newName == "external_child" )
				return new BEntity_external();

			if ( newName == "trigger" )
				return new BEntity_trigger();

			if ( newName == "bool" )
				return new BEntity_bool();

			if ( newName == "bool_property" )
				return new BEntity_bool_property();

			if ( newName == "uint" )
				return new BEntity_uint();

			if ( newName == "uint_property" )
				return new BEntity_uint_property();
			
			if ( newName == "int" )
				return new BEntity_int();

			if ( newName == "int_property" )
				return new BEntity_int_property();

			if ( newName == "int_property_new" )
				return new BEntity_int_propertyNew();
		
			if ( newName == "float" )
				return new BEntity_float();

			if ( newName == "float_property" )
				return new BEntity_float_property();
			
			if ( newName == "string" )
				return new BEntity_string();

			if ( newName == "string_property" )
				return new BEntity_string_property();
		
		
		// std::cout << "searching for plugin \"" << name << "\"" << std::endl;
		if ( hasChildren() )
		{
			// FIND CLASSES SUBDIR IN PLUGIN INFO
			for_all_children
			{
				// std::cout << "checking child " << (*child)->id() << std::endl;
				if ( library == "" || (*child)->name() == library )
				{
					if ( (*child)->hasChildren() )
					{
						for_all_children_of2( (*child) )
						for ( auto child2((*child)->children().begin()); child2 != (*child)->children().end(); ++child2 )
						{
							// std::cout << "checking Classes " << std::endl;
							if ( (*child2)->name()=="Classes" )
							{
								// std::cout << "FOUND Classes " << std::endl;
								if ( (*child2)->hasChildren() )
								{
									// FIND NAME IN PLUGIN INFO
									for_all_children_of3( (*child2) )
									{
										if ( (*child3)->name() == newName )
										{
											// std::cout << "FOUND " << newName << std::endl;
											BEntity_Plugin* p = dynamic_cast<BEntity_Plugin*>(*child);
											return p->create( parent, (*child3)->get_uint() );
										}
									}
								}
							}
						}
					}
				}
			}
		}

		std::cout << "BEntity_Plugin_Manager::create warning: entity class '" << newName << "' was found" << std::endl;
		return 0;
	}
	
