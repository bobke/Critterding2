#ifndef BE_LIB_HANDLER_H_INCLUDED
#define BE_LIB_HANDLER_H_INCLUDED

#include "be_entity_interface.h"

	// CLASS FACTORIES
		typedef BEntity* create_t( BEntity* parent, const Buint type );
		typedef void destroy_t( BEntity* );

	class BeLibHandler
	{
		public:
			BeLibHandler();
			virtual ~BeLibHandler();

			bool open( const std::string& dir, const std::string& lib );
			BEntity* create( BEntity* parent, const Buint id );
			void destroy( BEntity* e );
			const std::string& error() const;
		private:
			bool open( const std::string& location );
			void* m_sceneLibHandle;
			create_t* m_create_plugin;
			destroy_t* m_destroy_plugin;
			std::string m_error;
	};

	class BEntity_Plugin : public BEntity
	{
		public:
			BEntity_Plugin();
			virtual ~BEntity_Plugin();
			
			bool open( const std::string& dir, const std::string& lib );
			BEntity* create( BEntity* parent, const Buint id );
			void destroy( BEntity* e );
			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager ) { (void)hboxlayout; (void) plugin_manager; }
		private:
			BeLibHandler m_libHandler;
	};

	class BEntity_Plugin_Manager : public BEntity
	{
		public:
			BEntity_Plugin_Manager();
			virtual ~BEntity_Plugin_Manager();
			BEntity_Plugin* load( const std::string& name, const std::string& dir, const std::string& lib );
// 			Buint findType( const std::string& name ) const;
			BEntity* create( BEntity* parent, const std::string& name );
			BEntity* create( BEntity* parent, const std::string& library, const std::string& name );
			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager ) { (void)hboxlayout; (void) plugin_manager; }
		private:
	};

#endif
