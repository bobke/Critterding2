#ifndef BE_ENTITY_GRAPHICS_MODEL_H_INCLUDED
#define BE_ENTITY_GRAPHICS_MODEL_H_INCLUDED

#include "kernel/be_entity_interface.h"
#include "LinearMath/btVector3.h"
#include <boost/shared_ptr.hpp>

	class BeGraphicsModelResource;
	class btTransform;

	class BGraphicsModel : public BEntity
	{
		public:
			BGraphicsModel();
			const char* class_id() const { return "GraphicsModel"; }
			virtual ~BGraphicsModel() {};

			void setModel( boost::shared_ptr<BeGraphicsModelResource> model );
			boost::shared_ptr<BeGraphicsModelResource> getModel() const;
			virtual bool set( const Bstring& id, const char* value );
// 			virtual bool set( const Bstring& id, const Bfloat& value );

			virtual void process();
			
// 			void onAdd(BEntity* entity);

		private:
			boost::shared_ptr<BeGraphicsModelResource> m_model;
			std::string loaded_path;
// 			btVector3 m_pre_scale;
// 			btVector3 m_pre_position;
// 			btVector3 m_pre_rotation;
// 			btScalar m_matrix[16];
// 			btVector3 m_scale;
	}; 

	// TRANSFORM
		class glTransform: public BEntity
		{
			public:
				glTransform();
				const char* class_id() const { return "Transform"; }
				virtual ~glTransform() {};
				void construct();
				virtual bool apply( BEntity* const e ) const;
				virtual bool set( const char* value );
				virtual const char* get_string();
				float m_value[16];
				BEntity* m_scale_x;
				BEntity* m_scale_y;
				BEntity* m_scale_z;
			private:
// 				char m_value_chars[64];
		};	
#endif
