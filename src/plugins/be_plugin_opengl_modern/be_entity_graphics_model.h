#ifndef BE_ENTITY_GRAPHICS_MODEL_H_INCLUDED
#define BE_ENTITY_GRAPHICS_MODEL_H_INCLUDED

#include "be_entity_graphics_model_system.h"
// #include "kernel/be_entity_interface.h"
// #include "LinearMath/btTransform.h"
// #include <boost/shared_ptr.hpp>

	class BeGraphicsModelResource;
	class btTransform;
	class BCamera;
	class BShaderUniformVec4;
	class BShaderUniformVec3;

	class BGraphicsModel : public BEntity
	{
		public:
			BGraphicsModel();
			const char* class_id() const { return "GraphicsModel"; }
			virtual ~BGraphicsModel() {};
			virtual void construct();

			void setModel( boost::shared_ptr<BeGraphicsModelResource> model );
			boost::shared_ptr<BeGraphicsModelResource> getModel() const;
			virtual bool set( const Bstring& id, const char* value );
			virtual const char* get_string( const Bstring& id );
// 			virtual bool set( const Bstring& id, const Bfloat& value );

			virtual void process();
			virtual void processWhenInSight( const btTransform* transformHead, float sightrange );
// 			void onAdd(BEntity* entity);
			// BCamera* m_useCamera;

		private:
			virtual void draw( boost::shared_ptr<BeGraphicsModel> model, bool doTextures=true );
			void scale( const float x, const float y, const float z );

			boost::shared_ptr<BeGraphicsModelResource> m_model;
			std::string m_loaded_path;
			BEntity* m_pre_scale_x;
			BEntity* m_pre_scale_y;
			BEntity* m_pre_scale_z;
			BEntity* m_pre_position_x;
			BEntity* m_pre_position_y;
			BEntity* m_pre_position_z;
			BEntity* m_pre_rotation_x;
			BEntity* m_pre_rotation_y;
			BEntity* m_pre_rotation_z;
			
			BEntity* m_scale_x_current;
			BEntity* m_scale_y_current;
			BEntity* m_scale_z_current;

// 			btScalar m_matrix[16];
// 			btVector3 m_scale;

			// GLuint m_vao;
			// GLuint m_transformBuffer;
			GLuint m_scaleBuffer;
			GLuint m_ModelMatrixID;
			// GLuint m_ViewModelMatrixID;
			// GLuint m_ProjectionViewMatrixID;
			// GLuint m_ProjectionViewModelMatrixID;
			// GLuint m_ViewMatrixID;
			// GLuint m_ProjectionMatrixID;
			
			GLuint m_scale_location;
			// GLuint m_color_location;
			// GLuint m_textureSample_location;

			// btTransform m_ModelMatrix;
			// btTransform m_ViewModelMatrix;
			// btTransform m_ProjectionViewMatrix;
			// btTransform m_ProjectionViewModelMatrix;
			// float m_ViewModelBuffer[16];
			float m_ScaleBuffer[16];
			
			// float m_ModelBuffer[16];
			
			BShaderUniformVec4* m_uniform_color;
			BEntity* m_uniform_textureSample;
			BShaderUniformVec3* m_uniform_scale;
			
	}; 

	// TRANSFORM
		class glTransform: public BEntity
		{
			public:
				glTransform();
				const char* class_id() const { return "Transform"; }
				virtual ~glTransform() {};
				void construct();
				virtual bool apply( BEntity* e );
				virtual bool set( const char* value );
				bool set( const Bstring& id, const Bfloat& value );
				virtual const char* get_string();
				Bfloat get_float( const Bstring& id );
				void matMul(float* a, float* b);
				float m_value[16];
				BEntity* m_scale_x;
				BEntity* m_scale_y;
				BEntity* m_scale_z;
			private:
// 				char m_value_chars[64];
				
		};	
#endif
