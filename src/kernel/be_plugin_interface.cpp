#include "be_plugin_interface.h"
#include "be_plugin_base_entity_types.h"
// #include "be_lib_handler.h"
// #include "command/be_commands.h"

		void BClassesHelper::addClass( BEntity* parent, Buint id, const std::string& name )
		{
// 			std::cout << "addClass " << id << " name : " << name << std::endl;
// 			BEntity* t_cl = parent->addChildNamed( name, new BEntityType() );
// 			BEntity* t_id = t_cl->addChildNamed( "ID", new BEntity_uint() );
// 			t_id->set( id );

// 			BEntity* t_cl = parent->addChildEvent( BAddChildEvent(name, new BEntity_uint()) );

			BEntity* t_cl = parent->addChild( name, new BEntity_uint() );
// 			BEntity* t_id = t_cl->addChildNamed( "ID", new BEntity_uint() );
			
			
			t_cl->set( id );
		}

	// CONSTRUCTORS / DESTRUCTOR

// 		BEntityClasses::BEntityClasses()
// 		{
// // 			setName("Classes");
// 		}
// 
// 		BEntityClasses::~BEntityClasses()
// 		{
// 		}

// 	// ADD CLASS
// 		void BEntityClasses::addClass( const Buint id, const std::string& name )
// 		{
// 			std::cout << "addClass " << id << " name : " << name << std::endl;
// 			BEntity* t_cl = addChildNamed( name, new BEntityType() );
// 			BEntity* t_id = t_cl->addChildNamed( "ID", new BEntity_uint() );
// 			t_id->set( id );
// 
// // 			/*BEntity* t_de =*/ t_cl->addChild( "Description", new BEntity() );
// 		}

// 		void BEntityType::adminButtons( BEntity* hboxlayout, BEntity* plugin_manager )
// 		{
// // 			BEntity* button = hboxlayout->addChild("button_rm", plugin_manager->create( "qt5_button_draggable") );
// // 			button->set("label", name());
// // 
// // // 			BEntity* cmd_remove = button->addChild("cmd_remove", new CMD_remove() );
// // // 			cmd_remove->set(this);
// // 			
// // // 			button->connectServerServer(cmd_remove);
// 		}
