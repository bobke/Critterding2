#include "be_entity_graphics_model.h"
// #include "be_client_entity_system_qt.h"
// #include "scenes/sandbox/sc_netmessages.h"
#include "be_graphics_model_resource.h"
#include "be_entity_graphics_model_system.h"
#include "LinearMath/btTransform.h"

#include "kernel/be_entity_core_types.h"
#include "be_model_system.h"

		BGraphicsModel::BGraphicsModel()
		 : BEntity()
// 		 , m_pre_scale(1.0f, 1.0f, 1.0f)
// 		 , m_pre_position(0.0f, 0.0f, 0.0f)
// 		 , m_pre_rotation(0.0f, 0.0f, 0.0f)
// 		 , m_scale(1.0f, 1.0f, 1.0f)
		{
			setProcessing();
		}

		void BGraphicsModel::setModel( boost::shared_ptr<BeGraphicsModelResource> model )
		{
			m_model=model;
		}
		boost::shared_ptr<BeGraphicsModelResource> BGraphicsModel::getModel() const
		{
			return m_model;
		}

// 		bool BGraphicsModel::setProperty( const std::string& caller_name, const btVector3& value, const bool do_update )
// 		{
//  			// std::cout << "BeServerEntityPhysicsMesh:VECTOR3: " << caller_name << ":" << value.x() << std::endl;
// 			if ( caller_name == "pre_scale" )
// 			{
// 				if ( m_pre_scale != value )
// 				{
// 					m_pre_scale = value;
// 					if ( do_update )
// 						onUpdate(entity_history);
// 					return true;
// 				}
// 			}
// 			else if ( caller_name == "pre_position" )
// 			{
// 				if ( m_pre_position != value )
// 				{
// 					m_pre_position = value;
// 					if ( do_update )
// 						onUpdate(entity_history);
// 					return true;
// 				}
// 			}
// 			else if ( caller_name == "pre_rotation" )
// 			{
// 				if ( m_pre_rotation != value )
// 				{
// 					m_pre_rotation = value;
// 					if ( do_update )
// 						onUpdate(entity_history);
// 					return true;
// 				}
// 			}
// 			return false;
// 		}
	
	
	
	
	

// 		void BGraphicsModel::onAdd(BEntity* entity)
// 		{
// 			if ( entity->name() == "sight_distance" )
// 			{
// 				m_sight_distance = entity;
// 			}
// 		}


// 	bool BGraphicsModel::set( const Bstring& id, const Bfloat& value )
// 	{
// 		if ( id == "scale_x" )
// 		{
// 			if ( m_scale.x() != value )
// 			{
// 				m_scale.setX( value );
// // 				onUpdate();
// 				return true;
// 			}
// 		}
// 		else if ( id == "scale_y" )
// 		{
// 			if ( m_scale.y() != value )
// 			{
// 				std::cout << "setting y " << value << std::endl;
// 				m_scale.setY( value );
// // 				onUpdate();
// 				return true;
// 			}
// 		}
// 		else if ( id == "scale_z" )
// 		{
// 			if ( m_scale.z() != value )
// 			{
// 				m_scale.setZ( value );
// // 				onUpdate();
// 				return true;
// 			}
// 		}
// 		return false;
// 	}

	void BGraphicsModel::process()
	{
		
// 		btTransform t1;
// 		t1.setIdentity();
// 		t1.setOrigin(btVector3(0.0f, -1.0f, -4.5f));
// 		t1.getOpenGLMatrix( m_matrix );

		// FIXME COLORS HACK
		// std::cout << name() << std::endl;
		if ( name() == "graphics_entity_critter" )
		{
			glEnable(GL_LIGHTING);
			glColor4f(0.0f, 0.0f, 0.1f, 1.0f);
		}
		else if ( name() == "graphics_entity_food" )
		{
			glEnable(GL_LIGHTING);
			glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
		}
		else if ( name() == "GraphicsModel_SkyDome" )
		{
			glDisable(GL_LIGHTING);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			glEnable(GL_LIGHTING);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if( getModel() && getModel()->isReady() )
		{
			bool found_child(false);
			for_all_children
			{
				auto t = dynamic_cast<glTransform*>(*child);
				if ( (t) )
				{
					glPushMatrix();
						glMultMatrixf( t->m_value );
						
						// auto scale_x = t->getChild( "scale_x", 1 );
						// auto scale_y = t->getChild( "scale_y", 1 );
						// auto scale_z = t->getChild( "scale_z", 1 );
						if ( t->m_scale_x->get_float() != 1.0f || t->m_scale_y->get_float() != 1.0f || t->m_scale_z->get_float() != 1.0f )
						{
							glScalef( t->m_scale_x->get_float(),  t->m_scale_y->get_float(),  t->m_scale_z->get_float() );
						}
						// std::cout << "G " << id() << " " << t->m_value[0] << " " << t->m_value[1] << " " << t->m_value[2] << " " << t->m_value[3] << " " << t->m_value[4] << " " << t->m_value[5] << " " << t->m_value[6] << " " << t->m_value[7] << " " << t->m_value[8] << " " << t->m_value[9] << " " << t->m_value[10] << " " << t->m_value[11] << " " << t->m_value[12] << " " << t->m_value[13] << " " << t->m_value[14] << " " << t->m_value[15] << std::endl;
						getModel()->get()->draw();
					glPopMatrix();
					found_child = true;
				}
			}
			
			// just draw it once on 0,0,0 if we did not find a child above, basically a skybox hack
			if ( !found_child )
			{
				glPushMatrix();
					getModel()->get()->draw();
				glPopMatrix();
			}
			
			
			
// 			// MAKE IT ROTATE FIXME so yeah a transform entity and do this elsewhere
// 				btTransform tr;
// 				tr.setIdentity();
// 	// 			tr.setOrigin(btVector3(-600.0f, -40.0f, 0.0f));
// 	// 			tr.setOrigin(btVector3(-570.0f, -40.0f, -20.0f));
// 	// 			tr.getBasis().setEulerZYX( 2.14f, -0.0f, 0.0f );
// 
// 				
// 				// debug counter
// // 					std::cout << f_count << std::endl;
// 
// 				// FIXME using timer does not seem to smooth opengl...
// 					t.mark();
// 					f_count++;
// 
// 				// archer + Medieval_City3
// 					tr.setOrigin(btVector3(0.0f, -1.0f, -4.5f));
// 					tr.getBasis().setEulerZYX( 0.0f, 0.001f * t.getTotalMilliSeconds(), 0.0f );
// // 					tr.getBasis().setEulerZYX( 0.0f, 0.0001f * f_count, 0.0f );
// 				
// 					
// 				// FIXME difference to last frame, 
// 				// frame time debug, at 60 should not be more than 17 with only opengl running, come on
// // 					if ( (t.getTotalMilliSeconds() - t_diff) > 20 )
// // 						std::cout << "DIFF MODEL" << id() << " " << (t.getTotalMilliSeconds() - t_diff) << std::endl;
// // 					t_diff = t.getTotalMilliSeconds();
// 					
// 				// Sirius
// // 					tr.setOrigin(btVector3(0.0f, -70.0f, -4.5f));
// // 					tr.getBasis().setEulerZYX( 0.0f, -0.002f * f_count, 0.0f );
// 					
// 				// PARIS
// // 					tr.setOrigin(btVector3(-125, -100.0f, -125.0f));
// // 					tr.getBasis().setEulerZYX( 0.0f, -0.0001f * t.getTotalMilliSeconds(), 0.0f );
// 					
// 				tr.getOpenGLMatrix( m_matrix );
// 
// 			glPushMatrix();
// 				glMultMatrixf( m_matrix );
// 				getModel()->get()->draw();
// 			glPopMatrix();
		}
	}


	bool BGraphicsModel::set( const Bstring& id, const char* value )
	// bool BGraphicsModel::setProperty( const std::string& caller_name, const std::string& value, const bool do_update )
	{
		if ( id == "filename" && loaded_path != value )
		{
	//	std::cout << "PATH CALLED!!!!!!!!!!!!!" << std::endl;
	// 		BEVector3 scale(1.0f,1.0f,1.0f);
	// 		btTransform transform;
	// 		transform.setIdentity();

			// FIXME REMOVE THIS BY MAKING IT A TRANSFORM BY DEFAULT
			btTransform geometry_transform;
			geometry_transform.setIdentity();
// 			geometry_transform.setOrigin( m_pre_position );
// 			geometry_transform.getBasis().setEulerZYX( m_pre_rotation.x(), m_pre_rotation.y(), m_pre_rotation.z() );
// // 			geometry_transform.setOrigin( btVector3(0, 0, -200) );
// // 			geometry_transform.getBasis().setEulerZYX( 0.2f, m_pre_rotation.y(), m_pre_rotation.z() );

			
			
			BGraphicsModelSystem* scene = dynamic_cast<BGraphicsModelSystem*>(parent());
			if ( scene )
			{
				boost::shared_ptr<BeGraphicsModelResource> new_model( scene->load(value, scene->m_graphicsSystem, scene, btVector3( 1.0f, 1.0f, 1.0f ), geometry_transform) );
				if ( new_model )
				{
					setModel( new_model );
					loaded_path = value;
					return true;
				}
				else
				{
					std::cout << "BGraphicsModel: model could not be loaded '" << value << "'" << std::endl;
				}
			}
			
			
			// FIXME DISABLED FOR NOW
	// 		BEntity* p(parent());
	// 		while ( p != topParent() )
	// 		{
	// 			p = parent();
	// 
	// 			if ( p->entityType() == entityType_QGRAPHICSSCENE )
	// 			{
	// 				BeClientEntityQGraphicsScene* scene = dynamic_cast<BeClientEntityQGraphicsScene*>(p);
	// 				if ( scene )
	// 				{
	// 					boost::shared_ptr<BeGraphicsModelResource> new_model( scene->m_graphicsmeshSystem->load(value, scene->m_graphicsSystem, scene->m_graphicsmeshSystem, m_pre_scale, geometry_transform) );
	// 					if ( new_model )
	// 					{
	// 						setModel( new_model );
	// 						loaded_path = value;
	// 						return true;
	// 					}
	// 					else
	// 					{
	// 						std::cout << "BGraphicsModel: model could not be loaded '" << value << "'" << std::endl;
	// 					}
	// 				}
	// 			}
	// 		}
		}
		return false;
	}


// const BEVector3& BGraphicsModel::getProperty_Vector3(const std::string& caller_name) const
// {
// 	if ( caller_name == "scale" )
// 		return m_scale;
// }



// 			const btVector3& BGraphicsModel::getProperty_Vector3(const std::string& caller_name) const
// 			{
// 				if ( caller_name == "pre_scale" )
// 				{
// 					return m_pre_scale;
// 				}
// 				else if ( caller_name == "pre_position" )
// 				{
// 					return m_pre_position;
// 				}
// 				else if ( caller_name == "pre_rotation" )
// 				{
// 					return m_pre_rotation;
// 				}
// 				exit(1);
// 			}
// 			
//  

		// yeah the .01 gives you a mantissa without a null byte in it, so it can actually print it. If you actually want to print the binary you can bit_cast it to uint32_t and either print that manually or make a bitset<32> from it and print that.

		glTransform::glTransform() : BEntity()
		{
// 			 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
			m_value[0] =  1.0f;
			m_value[1] =  0.0f;
			m_value[2] =  0.0f;
			m_value[3] =  0.0f;
			m_value[4] =  0.0f;
			m_value[5] =  1.0f;
			m_value[6] =  0.0f;
			m_value[7] =  0.0f;
			m_value[8] =  0.0f;
			m_value[9] =  0.0f;
			m_value[10] =  1.0f;
			m_value[11] =  0.0f;
			m_value[12] =  0.0f;
			m_value[13] =  0.0f;
			m_value[14] =  0.0f;
			m_value[15] =  1.0f;
		}

		void glTransform::construct()
		{
			m_scale_x = addChild( "scale_x", new BEntity_float() );
			m_scale_y = addChild( "scale_y", new BEntity_float() );
			m_scale_z = addChild( "scale_z", new BEntity_float() );
			m_scale_x->set( 1.0f );
			m_scale_y->set( 1.0f );
			m_scale_z->set( 1.0f );

		}

		bool glTransform::apply( BEntity* const e ) const
		{
			return e->set( reinterpret_cast<const char*>(m_value) );
		}

		bool glTransform::set( const char* value )
		{ 
			float m_buffer[16];
			std::memcpy(m_buffer, value, 16 * sizeof(float));
			if
			(
				m_buffer[0] !=m_value[0]
				|| m_buffer[1] !=m_value[1]
				|| m_buffer[2] !=m_value[2]
				|| m_buffer[3] !=m_value[3]
				|| m_buffer[4] !=m_value[4]
				|| m_buffer[5] !=m_value[5]
				|| m_buffer[6] !=m_value[6]
				|| m_buffer[7] !=m_value[7]
				|| m_buffer[8] !=m_value[8]
				|| m_buffer[9] !=m_value[9]
				|| m_buffer[10] !=m_value[10]
				|| m_buffer[11] !=m_value[11]
				|| m_buffer[12] !=m_value[12]
				|| m_buffer[13] !=m_value[13]
				|| m_buffer[14] !=m_value[14]
				|| m_buffer[15] !=m_value[15]
			)
			{
				std::memcpy(m_value, m_buffer, 16 * sizeof(float));
				onUpdate();
				return true;
			}
			// else
			// {
			// 	std::cout << "opengl: skipping update " << std::endl;
			// }
			
			// FIXME
// 			if ( std::strcmp( reinterpret_cast<const char*>(m_value), value ) != 0 )
// 			{
// 				std::memcpy(m_value, value, 16 * sizeof(float));
// 				onUpdate();
// 			}
			
			// SPECIAL CASE ALWAYS RETURN TRUE, else io_hander passes it on to set(BEntity*), FIXME?  this should be fixed now
// 			return true;
			return false;
		}

		const char* glTransform::get_string()
		{
			return reinterpret_cast<const char*>(m_value);
		}
