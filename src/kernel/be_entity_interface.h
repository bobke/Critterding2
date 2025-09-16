#pragma once

	#include "be_types.h"
	#include <map>

	class BeLibHandler;
	class BEntity_Plugin_Manager;
	class B_Children_Handler;
	class B_IO_Handler;
	class BEInput;
	class BEOutput;

	class BEntity
	{
		// CONSTRUCTORS / DESTRUCTOR
			public:
				BEntity();
				virtual ~BEntity() {};
				virtual void construct() {};
				virtual void destruct() {};
				virtual const char* class_id() const { return "entity"; }

			private:
				Buint m_id;
				BEntity* m_be_parent;
				B_IO_Handler* m_io_handler;
				char m_flagbits;

		// SET VALUES
			public:
				virtual bool set();
				virtual bool set( BEntity* value );
				virtual bool set( const Bbool& value );
				virtual bool set( const Buint& value );
				virtual bool set( const Bint& value );
				virtual bool set( const Bfloat& value );
				virtual bool set( const Bdouble& value );
				// virtual bool set( const Bstring& value );
				virtual bool set( const char* value );
				// virtual bool set( void* value );

				virtual bool set( const Bstring& id, BEntity* value );
				virtual bool set( const Bstring& id, const Bbool& value );
				virtual bool set( const Bstring& id, const Buint& value );
				virtual bool set( const Bstring& id, const Bint& value );
				virtual bool set( const Bstring& id, const Bfloat& value );
				virtual bool set( const Bstring& id, const Bdouble& value );
				// virtual bool set( const Bstring& id, const Bstring& value );
				virtual bool set( const Bstring& id, const char* value );

		// GET VALUES
			public:
				virtual BEntity* get_reference();
				virtual Bbool get_bool();
				virtual Buint get_uint();
				virtual Bint get_int();
				virtual Bfloat get_float();
				virtual Bdouble get_double();
				// virtual Bstring* get_string();
				virtual const char* get_string();

				virtual BEntity* get_reference( const Bstring& id );
				virtual Bbool get_bool( const Bstring& id );
				virtual Buint get_uint( const Bstring& id );
				virtual Bint get_int( const Bstring& id );
				virtual Bfloat get_float( const Bstring& id );
				virtual Bdouble get_double( const Bstring& id );
				// virtual Bstring* get_string( const Bstring& id );
				virtual const char* get_string( const Bstring& id );
				// virtual void* get_binary( const Bstring& id );

				template <typename T>
				bool compareAndSetValue (T& original, T const& value);
				bool compareAndSetValue (BEntity*& original, BEntity* value);

		// NAME
			public:
				virtual void setName(const std::string& entityName);
				virtual void addName(BEntity* entity, const std::string& entityName);
				virtual void removeName();
				virtual void removeName(BEntity* entity);
				virtual const std::string& name();
				virtual const std::string nameFullPath();
				virtual std::string& name(BEntity* entity);

		// FPS
			public:
				virtual void setFps(const Buint fps);
				virtual void addFps(BEntity* entity, const Buint fps);
				virtual void removeFps();
				virtual void removeFps(BEntity* entity);
				virtual Buint fps();
				virtual Buint fps(BEntity* entity);

		// ID
			public:
				Buint64 id() const;
				void setID(const Buint64 t_id);
				void setIDRecyclable();
				Bbool isIDRecyclable() const;
				Bbool hasDelayReuseID() const;
			private:
				void setDelayReuseID();

		// PROCESSING
			public:
				virtual void process_general();
				virtual void process() {};
				// virtual void process_post() {}; // no longer works with processor
				void process_children() const;
// 				void process_children_post() const;
				Bbool hasProcessing() const;
				void setProcessing();
				Bbool hasDeferredProcessing() const;
				virtual void addProcessing();
				virtual void addProcessing(BEntity* entity);
				virtual void removeProcessing();
				virtual void removeProcessing(BEntity* entity);

		// CHILDREN
			public:
				virtual B_Children_Handler* childHandler() const;
				const BEntityVector& children() const;

				BEntity* addChild( BEntity* const entity );
				virtual BEntity* addChild( const std::string& name, BEntity* const entity );
				BEntity* addChild( const std::string& name, const std::string& entityClass );
				BEntity* addChild( const std::string& name, const std::string& library, const std::string& entityClass );
				virtual Bbool onAddChild( BEntity* entity );

				bool removeChild( BEntity* const entity );
				virtual Bbool onRemoveChild( BEntity* entity );

				BEntity* getChild(const char* name, const unsigned int max_levels=100000000) const; // FIXME 1 seems best
				BEntity* getChildWithID(const unsigned int id, const BEntity* parent) const;
				virtual BEntity* getChildCustom( BEntity* parent, const char* name = "" ) { (void)parent; (void)name; return 0; };
				// virtual BEntity* genericFunction( const char* id, BEntity* entity ) { (void)id; (void)entity; return 0; }; // TO USE, can do anything?, FIXME but can be done through ::set(string id, entity*) too ???

				Buint numChildren() const; 
				Buint numTotalChildren() const; 

				void clearChildren();

				virtual Bbool hasChildren() const;
				void setHasChildren( const bool value );

		// ADMIN WINDOW
				virtual void setAdminWindow( BEntity* entity );
				virtual BEntity* getAdminWindow();

		// BUILTIN FLAGS
			public:
				void setIsAdmin();
				void unsetIsAdmin();
				bool isAdmin() const;
				void setHasAdmin();
				void unsetHasAdmin();
				bool hasAdmin() const;
				
		// PLUGIN_MANAGER
			public:
				virtual BEntity_Plugin_Manager* pluginManager() const;

		// PARENT INFO
			public:
				BEntity* parent() const; // FIXME be_parent()
				void setParent( BEntity* const parent );
				virtual bool hasParent() const;
				// virtual bool hasParent( const Buint64 t_id ) const;
				virtual bool hasParent( const BEntity* entity ) const;
				BEntity* topParent() const;
		// TOP FUNCTIONS
				virtual BEntity* getNearestTop();
				virtual bool getNearestTopConnectionType();

		// BUILTIN FLAG
			public:
				void setBuiltin();
				bool isBuiltin() const;
				void markBuiltinChildren();

		// INPUT / OUTPUT
			public:
				bool hasIOHandler() const;
				void deleteIOHandler();
				bool hasInput() const;
				bool hasOutput() const;
				void spawnInput();
				BEInput* getInput() const;
				BEOutput* getOutput() const;
				virtual bool apply( BEntity* e );

				void connectServerServer( BEntity* entity_with_input, const bool force_local=false );
				void conn( BEntity* entity_with_output, BEntity* entity_with_input );  // FIXME implement
// 				void disconnectServerServer( BEntity* entity_with_input );
				virtual bool onUpdate() const;

		// FLAG OPERATIONS
			protected:
				Bbool getNthBit(const char packedValue, const int selectedBitIndex) const;
				void setNthBit(char & packedValue, const int selectedBitIndex, const bool value=true) const;

		// CUSTOM COPY COMMAND
			public:
				virtual BEntity* customCopy( BEntity* to_parent, BEntity* entity, std::map<BEntity*, BEntity*>& translation_map ) { return 0; }

		// COMMAND BUFFER
			public:
				virtual BEntity* getCommandBuffer();
	};

	// OPTIMIZATION ENTITIES

// 		// ENTITY WITH CHILDREN  // FIXME
// 		class BEntityWithChildren : public BEntity
// 		{
// 			// CONSTRUCTORS / DESTRUCTOR
// 				public:
// 					BEntityWithChildren();
// 					virtual ~BEntityWithChildren();
// 					
// 					BEntityVector* m_children;
// 		};
