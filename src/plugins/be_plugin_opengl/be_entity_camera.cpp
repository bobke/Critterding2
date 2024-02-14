#include "be_entity_camera.h"
#include "be_entity_graphics_model.h"
#include <GL/gl.h>
// #include <iostream>

	BCamera::BCamera()
	: BEntity()
	, m_s_elapsed(0)
	{
		setProcessing();
	}

	void BCamera::construct()
	{
		m_fov_y = addChild( "fov_y", new BEntity_float() );
		m_fov_y->set( SIMD_PI / 4 );
		m_aspect_ratio = addChild( "aspect_ratio", new BEntity_float() );
		m_aspect_ratio->set( 1280.0f/800.0f );
		m_z_near = addChild( "z_near", new BEntity_float() );
		m_z_near->set( 0.1f );
		m_z_far = addChild( "z_far", new BEntity_float() );
		m_z_far->set( 10000.0f );
		m_sensitivity_move = addChild( "sensitivity_move", new BEntity_float() );
		m_sensitivity_move->set( 7.0f );
		m_sensitivity_look = addChild( "sensitivity_look", new BEntity_float() );
		m_sensitivity_look->set( 1.0f );
		// m_transform = addChild( "transform", "Bullet_Transform" );
		m_transform = new BBulletTransform();
		addChild( "transform", m_transform );
		m_base_transform = new BBulletTransform();
		addChild( "base_transform", m_base_transform );
		
		auto movement = addChild( "movement", new BEntity() );
		m_forward = movement->addChild( "forward", new BEntity_bool() );
		m_backward = movement->addChild( "backward", new BEntity_bool() );
		m_left = movement->addChild( "left", new BEntity_bool() );
		m_right = movement->addChild( "right", new BEntity_bool() );
		m_up = movement->addChild( "up", new BEntity_bool() );
		m_down = movement->addChild( "down", new BEntity_bool() );

		auto looking = addChild( "looking", new BEntity() );
		m_look_left = looking->addChild( "left", new BEntity_bool() );
		m_look_right = looking->addChild( "right", new BEntity_bool() );
		m_look_up = looking->addChild( "up", new BEntity_bool() );
		m_look_down = looking->addChild( "down", new BEntity_bool() );
		m_look_roll_left = looking->addChild( "roll_left", new BEntity_bool() );
		m_look_roll_right = looking->addChild( "roll_right", new BEntity_bool() );
	}

	// FIXME do this in the transform itself?
	void BCamera::process()
	{
		if ( m_s_elapsed == 0 )
			m_s_elapsed = topParent()->getChild("sys", 1)->getChild("timer", 1)->getChild("s_elapsed", 1);

		// process movement
			if ( m_forward->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( 0.0f, 0.0f, -m_sensitivity_move->get_float() * m_s_elapsed->get_float() ));
			}
			if ( m_backward->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( 0.0f, 0.0f, m_sensitivity_move->get_float() * m_s_elapsed->get_float() ));
			}
			if ( m_left->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( -m_sensitivity_move->get_float() * m_s_elapsed->get_float(), 0.0f, 0.f ));
			}
			if ( m_right->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( m_sensitivity_move->get_float() * m_s_elapsed->get_float(), 0.0f, 0.f ));
			}
			if ( m_up->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( 0.0f, m_sensitivity_move->get_float() * m_s_elapsed->get_float(), 0.f ));
			}
			if ( m_down->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, 0.0f ), btVector3( 0.0f, -m_sensitivity_move->get_float() * m_s_elapsed->get_float(), 0.f ));
			}

		// process looking
			if ( m_look_left->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( m_sensitivity_look->get_float() * m_s_elapsed->get_float(), 0.0f, 0.0f ));
			}
			if ( m_look_right->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( -m_sensitivity_look->get_float() * m_s_elapsed->get_float(), 0.0f, 0.0f ));
			}
			if ( m_look_up->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, m_sensitivity_look->get_float() * m_s_elapsed->get_float(), 0.0f ));
			}
			if ( m_look_down->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, -m_sensitivity_look->get_float() * m_s_elapsed->get_float(), 0.0f ));
			}
			if ( m_look_roll_left->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, m_sensitivity_look->get_float() * m_s_elapsed->get_float() ));
			}
			if ( m_look_roll_right->get_bool() )
			{
				m_transform->m_transform = m_transform->m_transform * btTransform(btQuaternion( 0.0f, 0.0f, -m_sensitivity_look->get_float() * m_s_elapsed->get_float() ));
			}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		// FRUSTRUM
		const float frustumHalfHeight = tan( m_fov_y->get_float() * 180 / M_PI * M_PI / 360.0 ) * m_z_near->get_float();
		const float frustumHalfWidth = frustumHalfHeight * m_aspect_ratio->get_float();
		glFrustum( -frustumHalfWidth, frustumHalfWidth, -frustumHalfHeight, frustumHalfHeight, m_z_near->get_float(), m_z_far->get_float() );
		
		// CREATE AND APPLY INVERSE MATRIX
		m_sum_transform.m_transform = m_base_transform->m_transform * m_transform->m_transform;
		m_sum_transform.m_transform.inverse().getOpenGLMatrix( m_gl_transform.m_value );
		glMultMatrixf( m_gl_transform.m_value );

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	btVector3 BCamera::getScreenDirection(const int win_x, const int win_y, const int mouse_x, const int mouse_y)
	{
		btVector3 rayForward( -m_transform->m_transform.getBasis()[0][2], -m_transform->m_transform.getBasis()[1][2], -m_transform->m_transform.getBasis()[2][2]); 
		rayForward.normalize();
		rayForward *= m_z_far->get_float();

		btVector3 rayUp( m_transform->m_transform.getBasis()[0][1], m_transform->m_transform.getBasis()[1][1], m_transform->m_transform.getBasis()[2][1]); 
		btVector3 hor( rayForward.cross(rayUp) );
		hor.normalize();

		btVector3 vertical( hor.cross(rayForward) );
		vertical.normalize();

		const float tanfov( tanf( 0.5f * m_fov_y->get_float() ) );
		const float mult = 2.f * m_z_far->get_float() * tanfov;

		hor *= mult * (float)win_x / win_y;
		vertical *= mult;

		btVector3 rayTo = (m_transform->m_transform.getOrigin() + rayForward) - 0.5f * hor + 0.5f * vertical;

		rayTo += mouse_x * hor * 1.f / win_x;
		rayTo -= mouse_y * vertical * 1.f / win_y;

		return rayTo;
	}

