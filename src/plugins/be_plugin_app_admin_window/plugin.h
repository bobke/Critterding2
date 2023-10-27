#ifndef PLUGIN_H_INCLUDED
#define PLUGIN_H_INCLUDED

#include "kernel/be_plugin_interface.h"
#include "admin_lookup_buffer.h"
#include "kernel/be_entity_ops_copy.h"

	// SCENE
		class Scene: public BEntity
		{
			public:
				Scene() : BEntity() {};
				virtual ~Scene() {};
				
				virtual void construct();
// 			private:
// 			void add_admin_entity_list( BEntity* parent, BEntity* entity );
// 			void add_admin_entity_groupbox( BEntity* parent, BEntity* entity );
		};

	// ADMIN WINDOW
		class BAdminWindow: public BEntity
		{
			public:
				BAdminWindow() : BEntity() {};
				virtual ~BAdminWindow();
				
				virtual void construct();
				virtual bool set( const Bstring& id, BEntity* value );
			private:
				void add_admin_entity_list( BEntity* parent, BEntity* entity );
				void add_admin_entity_groupbox( BEntity* parent, BEntity* entity );
				void add_admin_item( BEntity* parent, BEntity* entity );
			
				BAdminLookupBuffer m_lookup_buffer;
				BEntityLoad m_entityLoad;
				
				void add_admin_genButtons( BEntity* to_layout, BEntity* entity );
				void add_admin_genButtonsWindow( BEntity* to_layout, BEntity* entity );
				void add_admin_genValueFields( BEntity* to_layout, BEntity* entity );
		};


#endif
