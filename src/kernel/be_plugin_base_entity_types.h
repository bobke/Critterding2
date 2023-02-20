#ifndef BE_PLUGIN_BASE_ENTITY_TYPES_H_INCLUDED
#define BE_PLUGIN_BASE_ENTITY_TYPES_H_INCLUDED

#include "be_plugin_interface.h"
#include "kernel/be_entity_core_types.h"

// 	class BEntity_reference : public BEntity
// 	{
// 		public:
// 			BEntity_reference();
// 			virtual ~BEntity_reference() {};
// 
// 			virtual bool set( BEntity* value );
// 			virtual BEntity* get_reference();
// 		private:
// 			BEntity* m_value;
// 	};

// 	class BEntity_trigger : public BEntity
// 	{
// 		public:
// 			BEntity_trigger();
// 			virtual ~BEntity_trigger() {};
// 			virtual bool set();
// 			virtual bool apply( BEntity* const e ) const;
// 	};
// 	
// 	// FIXME BEntity_trigger_property?
// 	// FIXME BOOLeans
// 
// 	class BEntity_bool : public BEntity
// 	{
// 		public:
// 			BEntity_bool();
// 			virtual ~BEntity_bool() {};
// 
// 			virtual bool set( const Bbool& value );
// 			virtual Bbool get_bool();
// 			virtual bool apply( BEntity* const e ) const;
// // 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// 		private:
// 			Bbool m_value;
// 	};
// 
// 	class BEntity_bool_property : public BEntity
// 	{
// 		public:
// 			BEntity_bool_property();
// 			virtual ~BEntity_bool_property() {};
// 			virtual bool set( const Bbool& value );
// 			virtual Bbool get_bool();
// 			virtual bool apply( BEntity* const e );
// 	};
// 
// 	class BEntity_uint : public BEntity
// 	{
// 		public:
// 			BEntity_uint();
// 			virtual ~BEntity_uint() {};
// 
// 			virtual bool set( const Buint& value );
// 			virtual Buint get_uint();
// 			virtual bool apply( BEntity* const e ) const;
// // 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// 		private:
// 			Buint m_value;
// 	};
// 
// 	class BEntity_uint_property : public BEntity
// 	{
// 		public:
// 			BEntity_uint_property();
// 			virtual ~BEntity_uint_property() {};
// 			virtual bool set( const Buint& value );
// 			virtual Buint get_uint();
// 			virtual bool apply( BEntity* const e );
// 		private:
// // 			Buint m_value;
// 	};
// 
// 	class BEntity_float : public BEntity
// 	{
// 		public:
// 			BEntity_float();
// 			virtual ~BEntity_float() {};
// 
// 			virtual bool set( const Bfloat& value );
// 			virtual Bfloat get_float();
// 			virtual bool apply( BEntity* const e ) const;
// // 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// 		private:
// 			Bfloat m_value;
// 	};
// 
// 	class BEntity_float_property : public BEntity
// 	{
// 		public:
// 			BEntity_float_property();
// 			virtual ~BEntity_float_property() {};
// 			virtual bool set( const Bfloat& value );
// // 			virtual Bfloat* get_float();
// 			virtual bool apply( BEntity* const e );
// 		private:
// // 			Bfloat m_value;
// 	};
// 
// 	class BEntity_double : public BEntity
// 	{
// 		public:
// 			BEntity_double();
// 			virtual ~BEntity_double() {};
// 
// 			virtual bool set( const Bdouble& value );
// 			virtual Bdouble get_double();
// 			virtual bool apply( BEntity* const e ) const;
// // 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// 		private:
// 			Bdouble m_value;
// 	};	
// 	
// 	class BEntity_string : public BEntity
// 	{
// 		public:
// 			BEntity_string();
// 			virtual ~BEntity_string() {};
// 
// 			virtual bool set( const char* value );
// 			virtual Bstring* get_string();
// 			virtual bool apply( BEntity* const e ) const;
// // 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// 		private:
// 			Bstring m_value;
// 	};
// 
// 	class BEntity_string_property : public BEntity
// 	{
// 		public:
// 			BEntity_string_property();
// 			virtual ~BEntity_string_property() {};
// 			virtual bool set( const char* value );
// // 			virtual Bstring* get_string();
// 			virtual bool apply( BEntity* const e );
// 		private:
// // 			Bstring m_value;
// 	};
	
#endif
 
