#include "be_entity_light.h"
#include "kernel/be_entity_core_types.h"
#include "GL/glew.h"
#include "LinearMath/btTransform.h"
// #include <iostream>
 
	BGLLight::BGLLight()
	: m_gl_id( 0 )
	{
		setProcessing();

	};

	void BGLLight::construct()
	{
		m_directional = addChild( "directional", new BEntity_bool() );
		
		m_spot_cutoff = addChild( "spot_cutoff", new BEntity_float() );
		m_spot_exponent = addChild( "spot_exponent", new BEntity_float() );
		m_constant_attenuation = addChild( "constant_attenuation", new BEntity_float() );
		m_linear_attenuation = addChild( "linear_attenuation", new BEntity_float() );
		m_quadratic_attenuation = addChild( "quadratic_attenuation", new BEntity_float() );
		m_shininess = addChild( "shininess", new BEntity_float() );
		
		m_directional->set( Bbool(true) );
		m_spot_cutoff->set( 180.0f );
		m_spot_exponent->set( 0.0f );
		m_constant_attenuation->set( 0.5f );
		m_linear_attenuation->set( 0.0f );
		m_quadratic_attenuation->set( 0.0000f );
		m_shininess->set( 1.0f );
		

		m_model_ambient_r = addChild( "model_ambient_r", new BEntity_float() );
		m_model_ambient_g = addChild( "model_ambient_g", new BEntity_float() );
		m_model_ambient_b = addChild( "model_ambient_b", new BEntity_float() );
		m_model_ambient_a = addChild( "model_ambient_a", new BEntity_float() );
		
		m_color_ambient_r = addChild( "color_ambient_r", new BEntity_float() );
		m_color_ambient_g = addChild( "color_ambient_g", new BEntity_float() );
		m_color_ambient_b = addChild( "color_ambient_b", new BEntity_float() );
		m_color_ambient_a = addChild( "color_ambient_a", new BEntity_float() );

		m_color_diffuse_r = addChild( "color_diffuse_r", new BEntity_float() );
		m_color_diffuse_g = addChild( "color_diffuse_g", new BEntity_float() );
		m_color_diffuse_b = addChild( "color_diffuse_b", new BEntity_float() );
		m_color_diffuse_a = addChild( "color_diffuse_a", new BEntity_float() );

		m_color_specular_r = addChild( "color_specular_r", new BEntity_float() );
		m_color_specular_g = addChild( "color_specular_g", new BEntity_float() );
		m_color_specular_b = addChild( "color_specular_b", new BEntity_float() );
		m_color_specular_a = addChild( "color_specular_a", new BEntity_float() );
	}

	void BGLLight::process()
	{
		// m_gl_id = gl_light_id;
		
		const unsigned int gl_light = GL_LIGHT0 + m_gl_id;
		
// 		GLfloat ambientLight[] = { m_model_ambient.x(), m_model_ambient.y(), m_model_ambient.z(), m_model_ambient.w() };
// 		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
		
		GLfloat ambient[] = { m_color_ambient_r->get_float(), m_color_ambient_g->get_float(), m_color_ambient_b->get_float(), m_color_ambient_a->get_float() };
// 		GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightfv(gl_light, GL_AMBIENT, ambient);

		GLfloat lightColor[] = { m_color_diffuse_r->get_float(), m_color_diffuse_g->get_float(), m_color_diffuse_b->get_float(), m_color_diffuse_a->get_float() };
		glLightfv(gl_light, GL_DIFFUSE, lightColor);

		GLfloat lightSpecular[] = { m_color_specular_r->get_float(), m_color_specular_g->get_float(), m_color_specular_b->get_float(), m_color_specular_a->get_float() };
		glLightfv(gl_light, GL_SPECULAR, lightSpecular);

		btTransform t;
		// if ( !m_transform )
		// {
			// std::cout << "BeClientEntityLight: no transform set" << std::endl;
			t.setIdentity();
		// }
		// else
			// t = m_transform->getProperty_Transform();

		auto p = t.getOrigin();
		// const BEVector3& p( t.getOrigin() );
		
		btVector3 d (
			-t.getBasis()[0][1],
			-t.getBasis()[1][1],
			-t.getBasis()[2][1]);

// 		std::cout << "BeClientEntityLight: " << gl_light << " : position x:" << p.x() << " position y:" << p.y() << " position z:" << p.z() << " directional: " << m_directional << std::endl;

		if ( m_directional->get_bool() )
		{
			GLfloat lightPos[] = { p.x(), p.y()+300.0f, p.z(), 0.0f };
			glLightfv(gl_light, GL_POSITION, lightPos);
			// std::cout << "directional" << std::endl;
		}
		else
		{
			GLfloat lightPos[] = { p.x(), p.y()+300.0f, p.z(), 1.0f };
			glLightfv(gl_light, GL_POSITION, lightPos);
			// std::cout << "not directional" << std::endl;
		}

		GLfloat lightDirection[] = { d.x(), d.y(), d.z() };
		glLightfv(gl_light, GL_SPOT_DIRECTION, lightDirection);

		GLfloat lightCutoff[] = { m_spot_cutoff->get_float() };
		glLightfv(gl_light, GL_SPOT_CUTOFF, lightCutoff);

		GLfloat lightExponent[] = { m_spot_exponent->get_float() };
		glLightfv(gl_light, GL_SPOT_EXPONENT, lightExponent);
		
		GLfloat lightAttenuation[] = { m_constant_attenuation->get_float() };
		glLightfv(gl_light, GL_CONSTANT_ATTENUATION, lightAttenuation);
// 
		GLfloat lightLAttenuation[] = { m_linear_attenuation->get_float() };
		glLightfv(gl_light, GL_LINEAR_ATTENUATION, lightLAttenuation);
// 
		GLfloat lightQAttenuation[] = { m_quadratic_attenuation->get_float() };
		glLightfv(gl_light, GL_QUADRATIC_ATTENUATION, lightQAttenuation);

		glEnable(gl_light);

	}

// 	Bbool BGLLight::get_bool( const Bstring& id )
// 	{
// 		
// 	}
// 
// 	bool BGLLight::set( const Bstring& id, const Bbool& value )
// 	{
// 		
// 	}
// 
// 	Bint BGLLight::get_int( const Bstring& id )
// 	{
// 		
// 	}
// 
// 	Bfloat BGLLight::get_float( const Bstring& id )
// 	{
// 		
// 	}
// 
// 	bool BGLLight::set( const Bstring& id, const Bfloat& value )
// 	{
// 		
// 	}
// 
