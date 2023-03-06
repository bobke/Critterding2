#ifndef BE_ENTITY_TOP_H_INCLUDED
#define BE_ENTITY_TOP_H_INCLUDED

// #define ADMIN_WINDOW

#include "be_entity_interface.h"
#include "be_entity_processor.h"  // keeping this here for easy processor access for inheriting top entities
#include "kernel/be_entity_ops_copy.h"

class BEntity_Plugin;
class BEntity_Plugin_Manager;
class B_Children_Handler;

class BEntityTop : public BEntity
{
	// CONSTRUCTORS / DESTRUCTOR
		public:
			BEntityTop( bool connection_type=false) ;
			virtual ~BEntityTop();
			
			virtual void construct();

		// PROCESSING
			public:
				void process_general();
				virtual void reConstructProcessList( BEntity* entity );
				Buint processorListSize() const;
				virtual void addProcessing(BEntity* entity);
				virtual void removeProcessing(BEntity* entity);
			protected:
				BProcessor* m_processor;
				bool m_reconstruct_list;

		// TOP FUNCTIONS
				virtual BEntity* getNearestTop();
				virtual bool getNearestTopConnectionType();
			protected:
				bool m_connection_type;

		// NAME
			public:
				virtual void addName(BEntity* entity, const std::string& entityName);
				virtual void removeName(BEntity* entity);
				virtual std::string& name(BEntity* entity);
			private:
				// id to name map
				std::unordered_map<BEntity*, std::string> m_be_name_map;

		// FPS
			public:
				virtual void addFps(BEntity* entity, const Buint fps);
				virtual void removeFps(BEntity* entity);
				virtual Buint fps(BEntity* entity);

		// CHILDREN
			public:
				void spawnChildrenManager();
				virtual B_Children_Handler* childHandler() const;
				void print( BEntity* entity, const Buint max_levels );
			private:
				B_Children_Handler* m_child_handler;

		// PLUGIN_MANAGER
			public:
				void spawnPluginManager();
				virtual BEntity_Plugin_Manager* pluginManager() const;

		// LOOP MANAGER
			public:
				void enableLoopManager() { m_isLoopManager=true; };
				Buint numLoops() { return m_numLoops; };
				Bbool isLoopManager() { return m_isLoopManager; }
// 				Buint numLoops() { return m_numLoops; }
			protected:
				Buint m_numLoops;
			private:
				Bbool m_isLoopManager;

		// COMMAND BUFFER
			public:
				void spawnCommandBuffer(); // FIXME command not needed, do it in the construct
				void process_and_clear_command_buffer();
// 				bool process_command(BEntity* command);
				virtual BEntity* getCommandBuffer();
			private:
				BEntity* m_command_buffer;

		// PROCESSING
			protected:
// 				virtual void process_local();
		// ----- COMMAND HANDLING
// 			public:
// 				BEntity_Plugin_Manager* getPluginManager() { return m_plugin_manager; }
// 			virtual bool process_command(BEntityPt command);
			private:
				BEntity_Plugin_Manager* m_plugin_manager;
				
		// ADMIN WINDOW
			private:
				BEntity* getAdminWindow();
				void setAdminWindow( BEntity* entity );
				BEntity* m_admin_window; // FIXME : REMOVE
				
		// OPS
			private:
				BEntityCopy m_entityCopy;
				BEntitySave m_entitySave;
};

	
#endif
 
