#ifndef BE_ENTITY_CORE_TYPES_H_INCLUDED
#define BE_ENTITY_CORE_TYPES_H_INCLUDED
#include "be_entity_interface.h"

	class BEntity_reference : public BEntity
	{
		public:
			BEntity_reference() : m_value(0) {};
			const char* class_id() const { return "reference"; }
			virtual ~BEntity_reference() {};

			virtual bool set( BEntity* value );
			virtual BEntity* get_reference();
		protected:
			BEntity* m_value;
	};
	
	// FIXME APPLY THIS
	// FIXME APPLY THIS
	// FIXME APPLY THIS
	class BEntity_external : public BEntity_reference
	{
		public:
			BEntity_external() {};
			const char* class_id() const { return "external_child"; }
			virtual bool set( BEntity* value );
			virtual ~BEntity_external() {};
	};
	

	class BEntity_trigger : public BEntity
	{
		public:
			BEntity_trigger() {};
			const char* class_id() const { return "trigger"; }
			virtual ~BEntity_trigger() {};
			virtual bool set();
			virtual bool apply( BEntity* e );
	};
	
	// FIXME BEntity_trigger_property?
	// FIXME BOOLeans

	class BEntity_bool : public BEntity
	{
		public:
			BEntity_bool() : m_value(false) {};;
			const char* class_id() const { return "bool"; }
			virtual ~BEntity_bool() {};

			virtual bool set( const Bbool& value );
			virtual Bbool get_bool();
			virtual bool apply( BEntity* e );
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
		protected:
			Bbool m_value;
	};

	class BEntity_bool_property : public BEntity
	{
		public:
			BEntity_bool_property();
			const char* class_id() const { return "bool_property"; }
			virtual ~BEntity_bool_property() {};
			virtual bool set( const Bbool& value );
			virtual Bbool get_bool();
			virtual bool apply( BEntity* e );
	};

	class BEntity_uint : public BEntity
	{
		public:
			BEntity_uint() : m_value(0) {};
			const char* class_id() const { return "uint"; }
			virtual ~BEntity_uint() {};

			virtual bool set( const Buint& value );
// 			virtual bool set( BEntity* entity );
			virtual Buint get_uint();
			virtual bool apply( BEntity* e );
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
		protected:
			Buint m_value;
	};

	class BEntity_uint_property : public BEntity
	{
		public:
			BEntity_uint_property();
			const char* class_id() const { return "uint_property"; }
			virtual ~BEntity_uint_property() {};
			virtual bool set( const Buint& value );
			virtual bool set( BEntity* entity );
			virtual Buint get_uint();
			virtual bool apply( BEntity* e );
		private:
// 			Buint m_value;
	};

	class BEntity_int : public BEntity
	{
		public:
			BEntity_int() : m_value(0) {};
			const char* class_id() const { return "int"; }
			virtual ~BEntity_int() {};

			virtual bool set( const Bint& value );
// 			virtual bool set( BEntity* entity );
			virtual Bint get_int() { return m_value; }
			virtual bool apply( BEntity* e ) { return e->set( m_value ); };
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
		protected:
			Bint m_value;
	};

	class BEntity_int_propertyNew : public BEntity_int
	{
		public:
			BEntity_int_propertyNew() : BEntity_int() {};
			const char* class_id() const { return "_int_propertyNew"; }
			virtual ~BEntity_int_propertyNew() {};

			virtual bool set( const Bint& value )
			{
				if ( compareAndSetValue( m_value, value ) )
				{
					parent()->set( name(), value );
					onUpdate();
					return true;
				}
				return false;
			};
			virtual bool apply( BEntity* e ) { return e->set( m_value ); };
		protected:
	};

	class BEntity_int_property : public BEntity
	{
		public:
			BEntity_int_property();
			const char* class_id() const { return "int_property"; }
			virtual ~BEntity_int_property() {};
			virtual bool set( const Bint& value );
			virtual bool set( BEntity* entity );
			virtual Bint get_int();
			virtual bool apply( BEntity* e );
	};

	class BEntity_float : public BEntity
	{
		public:
			BEntity_float() : m_value(0.0f) {};
			const char* class_id() const { return "float"; }
			virtual ~BEntity_float() {};

			virtual bool set( const Bfloat& value );
			virtual Bfloat get_float();
			virtual bool apply( BEntity* e );
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
		protected:
			Bfloat m_value;
	};

	class BEntity_float_property : public BEntity
	{
		public:
			BEntity_float_property();
			const char* class_id() const { return "float_property"; }
			virtual ~BEntity_float_property() {};
			virtual bool set( const Bfloat& value );
			virtual Bfloat get_float();
			virtual bool apply( BEntity* e );
		private:
// 			Bfloat m_value;
	};

	class BEntity_double : public BEntity
	{
		public:
			BEntity_double() : m_value(0.0) {};
			const char* class_id() const { return "double"; }
			virtual ~BEntity_double() {};

			virtual bool set( const Bdouble& value );
			virtual Bdouble get_double();
			virtual bool apply( BEntity* e );
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
		protected:
			Bdouble m_value;
	};	
	
// 	class BEntity_string : public BEntity
// 	{
// 		public:
// 			BEntity_string();
// 			virtual ~BEntity_string() {};
// 
// 			virtual bool set( const char* value );
// 			virtual Bstring* get_string();
// 			virtual bool apply( BEntity* e );
// // 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
// 		private:
// 			Bstring m_value;
// 	};

	class BEntity_string : public BEntity
	{
		public:
			BEntity_string() : m_value(0) {};
			const char* class_id() const { return "string"; }
			virtual ~BEntity_string();

			virtual bool set( const char* value );
// 			virtual Bstring* get_string();
			virtual const char* get_string();
			virtual bool apply( BEntity* e );
// 			void adminButtons( BEntity* hboxlayout, BEntity* plugin_manager );
		protected:
			char* m_value;
	};
	
	
	class BEntity_string_property : public BEntity
	{
		public:
			BEntity_string_property();
			const char* class_id() const { return "string_property"; }
			virtual ~BEntity_string_property() {};
			virtual bool set( const char* value );
			virtual const char* get_string();
			virtual bool apply( BEntity* e );
		private:
			// char* m_value;
	};
#endif
