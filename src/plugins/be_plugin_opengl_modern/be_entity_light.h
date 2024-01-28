#ifndef BE_ENTITY_LIGHT_H_INCLUDED
#define BE_ENTITY_LIGHT_H_INCLUDED

#include "kernel/be_entity_interface.h"
 
class BGLLight : public BEntity
{
	public:
		BGLLight();
		virtual ~BGLLight() {};
		void construct();

		// virtual Bbool get_bool( const Bstring& id );
		// virtual bool set( const Bstring& id, const Bbool& value );
  // 
		// virtual Bint get_int( const Bstring& id );
  // 
		// virtual Bfloat get_float( const Bstring& id );
		// virtual bool set( const Bstring& id, const Bfloat& value );

		void process();
		// void positionLight( const unsigned int gl_light );

		// virtual void onAdd( BeEntity::ptr entity )
		// {
		// 	if ( entity->name() == "transform" )
		// 	{
		// 		m_transform = entity;
		// 	}
		// }

	private:

		Bint m_gl_id;

		BEntity* m_model_ambient_r;
		BEntity* m_model_ambient_g;
		BEntity* m_model_ambient_b;
		BEntity* m_model_ambient_a;

		BEntity* m_color_ambient_r;
		BEntity* m_color_ambient_g;
		BEntity* m_color_ambient_b;
		BEntity* m_color_ambient_a;
		
		BEntity* m_color_diffuse_r;
		BEntity* m_color_diffuse_g;
		BEntity* m_color_diffuse_b;
		BEntity* m_color_diffuse_a;
		
		BEntity* m_color_specular_r;
		BEntity* m_color_specular_g;
		BEntity* m_color_specular_b;
		BEntity* m_color_specular_a;
		
		// BeEntity::ptr m_transform;

		BEntity* m_directional;

		BEntity* m_spot_cutoff;
		BEntity* m_spot_exponent;
		BEntity* m_constant_attenuation;
		BEntity* m_linear_attenuation;
		BEntity* m_quadratic_attenuation;
		BEntity* m_shininess;
};

#endif
