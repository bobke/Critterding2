#include "be_entity_graphics_model.h"
// #include "be_client_entity_system_qt.h"
// #include "scenes/sandbox/sc_netmessages.h"
#include "be_graphics_model_resource.h"
#include "be_entity_graphics_model_system.h"

#include "kernel/be_entity_core_types.h"
#include "be_model_system.h"
// #include "be_entity_camera.h"

#include "graphics/be_mesh.h"
#include "graphics/be_graphics_system.h"
#include "be_shader_uniform_vec4.h"
#include "be_shader_uniform_vec3.h"
#include "be_texture_2d_resource.h"
#include <glm/gtc/type_ptr.hpp>


	BGraphicsModel::BGraphicsModel()
		: BEntity()
	{
		setProcessing();
	}

	void BGraphicsModel::construct()
	{
		m_pre_scale_x = addChild( "pre_scale_x", new BEntity_float() );
		m_pre_scale_y = addChild( "pre_scale_y", new BEntity_float() );
		m_pre_scale_z = addChild( "pre_scale_z", new BEntity_float() );
		m_pre_position_x = addChild( "pre_position_x", new BEntity_float() );
		m_pre_position_y = addChild( "pre_position_y", new BEntity_float() );
		m_pre_position_z = addChild( "pre_position_z", new BEntity_float() );
		m_pre_rotation_x = addChild( "pre_rotation_x", new BEntity_float() );
		m_pre_rotation_y = addChild( "pre_rotation_y", new BEntity_float() );
		m_pre_rotation_z = addChild( "pre_rotation_z", new BEntity_float() );
		
		m_pre_scale_x->set( 1.0f );
		m_pre_scale_y->set( 1.0f );
		m_pre_scale_z->set( 1.0f );
		
		m_pre_position_x->set( 0.0f );
		m_pre_position_y->set( 0.0f );
		m_pre_position_z->set( 0.0f );

		m_pre_rotation_x->set( 0.0f );
		m_pre_rotation_y->set( 0.0f );
		m_pre_rotation_z->set( 0.0f );
		
		// COLOR UNIFORM
		m_uniform_color = dynamic_cast<BShaderUniformVec4*>( parent()->getChild("shaders", 1)->getChild("u_Color", 1) );
		// m_color_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "u_Color" );
		// glUniform4f( m_color_location, 0.2f, 0.8f, 0.4f, 1.0f );
		
		m_ModelMatrixID = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ModelMatrix_Model" );
		// m_ViewModelMatrixID = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ViewModelMatrix_Model" );
		// m_ProjectionViewMatrixID = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ProjectionViewMatrix_Model" );
		// m_ProjectionViewModelMatrixID = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ProjectionViewModelMatrix_Model" );
		// m_ProjectionMatrixID = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ProjectionMatrix_Model" );
		// m_ViewMatrixID = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ViewMatrix_Model" );
		// m_uniform_scale = dynamic_cast<BShaderUniformVec3*>( parent()->getChild("shaders", 1)->getChild("u_Scale", 1) );
		m_scale_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "u_Scale" );

		m_uniform_textureSample = parent()->getChild("shaders", 1)->getChild("u_textureSample", 1);
		// m_textureSample_location = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "u_textureSample" );

		m_scale_x_current = parent()->getChild("shaders", 1)->getChild("e_scale_x", 1);
		m_scale_y_current = parent()->getChild("shaders", 1)->getChild("e_scale_y", 1);
		m_scale_z_current = parent()->getChild("shaders", 1)->getChild("e_scale_z", 1);
		
		// PREPARE SCALE BUFFER: ONLY 0, 5, 10 TO ALTER
			m_ScaleBuffer[0] = 1.0f;
			m_ScaleBuffer[1] = 0.0f;
			m_ScaleBuffer[2] = 0.0f;
			m_ScaleBuffer[3] = 0.0f;
			
			m_ScaleBuffer[4] = 0.0f;
			m_ScaleBuffer[5] = 1.0f;
			m_ScaleBuffer[6] = 0.0f;
			m_ScaleBuffer[7] = 0.0f;
			
			m_ScaleBuffer[8] = 0.0f;
			m_ScaleBuffer[9] = 0.0f;
			m_ScaleBuffer[10] = 1.0f;
			m_ScaleBuffer[11] = 0.0f;
			
			m_ScaleBuffer[12] = 0.0f;
			m_ScaleBuffer[13] = 0.0f;
			m_ScaleBuffer[14] = 0.0f;
			m_ScaleBuffer[15] = 1.0f;
		
// 		// std::cout << "// Create the VAO" << std::endl;
// 		// !!!!!!!! FIXME ?
// 		// Create the VAO
// 		glGenVertexArrays(1, &m_vao);
// 		glBindVertexArray(m_vao);
// 
// 		// Create the VBO for transforms
// 		auto maxInstances  = 10000;
// 		glGenBuffers(1, &m_transformBuffer);
// 		glBindBuffer(GL_ARRAY_BUFFER, m_transformBuffer);
// 		glBufferData(GL_ARRAY_BUFFER, maxInstances * sizeof(float[16]), nullptr, GL_DYNAMIC_DRAW);
// 			
// 		// Set up vertex attribute pointers for the transform matrix
// 		for (int i = 0; i < 4; ++i) {
// 			glEnableVertexAttribArray(3 + i);
// 			glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(float[16]), (void*)(i * sizeof(float[16])));
// 			glVertexAttribDivisor(3 + i, 1);
// 		}
// 
// 		// Create the VBO for scales
// 		glGenBuffers(1, &m_scaleBuffer);
// 		glBindBuffer(GL_ARRAY_BUFFER, m_scaleBuffer);
// 		glBufferData(GL_ARRAY_BUFFER, maxInstances * sizeof(float[3]), nullptr, GL_DYNAMIC_DRAW);
// 		
// 		// Set up vertex attribute pointer for the scale vector
// 		glEnableVertexAttribArray(7);
// 		glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(float[3]), (void*)0);
// 		glVertexAttribDivisor(7, 1);
// 
// 		// Unbind
// 		glBindBuffer(GL_ARRAY_BUFFER, 0);
// 		glBindVertexArray(0);
	}

	void BGraphicsModel::setModel( boost::shared_ptr<BeGraphicsModelResource> model )
	{
		m_model=model;
	}

	boost::shared_ptr<BeGraphicsModelResource> BGraphicsModel::getModel() const
	{
		return m_model;
	}

	void BGraphicsModel::process()
	{
		if( getModel() && getModel()->isReady() )
		{
			bool found_child(false);

			// SET COLOR HACK
			const auto& ambient = getModel()->get()->matlist.begin()->second.m_material.getAmbient();
			// glUniform4f( m_color_location, ambient.x(), ambient.y(), ambient.z(), 1.0f );
			m_uniform_color->setValue( ambient.x(), ambient.y(), ambient.z(), 1.0f );

			for_all_children
			{
				auto t = dynamic_cast<glTransform*>(*child);
				if ( (t) )
				{
					// transform value
					// m_modelMatrix = glGetUniformLocation(  dynamic_cast<BGraphicsModelSystem*>( parent() )->m_effect->m_program.get()->handle(), "ModelMatrix" );
					// glUniformMatrix4fv( m_modelMatrix, 1, GL_FALSE, t->m_value );

					// m_ViewModelMatrix.setFromOpenGLMatrix( t->m_value );

					// FIXME m_useCamera->m_ProjectionMatrix
					
					// m_useCamera->m_ProjectionMatrix.getOpenGLMatrix( m_ViewModelBuffer );
					// std::cout << "z" << m_ViewModelBuffer[14] << std::endl;
					
					// MODEL
						// m_ModelMatrix.setFromOpenGLMatrix( t->m_value );
						// m_ModelMatrix.getOpenGLMatrix( m_ModelBuffer );
						// glUniformMatrix4fv( m_ModelMatrixID, 1, GL_FALSE, m_ModelBuffer );
						glUniformMatrix4fv( m_ModelMatrixID, 1, GL_FALSE, t->m_value );

// 					// VIEW
// 						m_useCamera->m_ViewMatrix.getOpenGLMatrix( m_ViewModelBuffer );
// 						glUniformMatrix4fv( m_ViewMatrixID, 1, GL_FALSE, m_ViewModelBuffer );
// 
// 					// MODEL VIEW
// 						m_ViewModelMatrix = m_useCamera->m_ViewMatrix * m_ModelMatrix;
// 						m_ViewModelMatrix.getOpenGLMatrix( m_ViewModelBuffer );
// 						glUniformMatrix4fv( m_ViewModelMatrixID, 1, GL_FALSE, m_ViewModelBuffer );
// 
// 					// PROJECTION FIXME WTF
// 						// m_useCamera->m_ProjectionMatrix.getOpenGLMatrix( m_ViewModelBuffer );
// 						// glUniformMatrix4fv( m_ProjectionMatrixID, 1, GL_FALSE, m_ViewModelBuffer );
// 						
// 						// btTransform tr;
// 						// tr.setFromOpenGLMatrix( m_useCamera->m_projectionMatrix );
// 						// float buffer[16];
// 						// tr.getOpenGLMatrix( buffer );
// 						// glUniformMatrix4fv( m_ProjectionMatrixID, 1, GL_FALSE, buffer );
// 
// 						glUniformMatrix4fv( m_ProjectionMatrixID, 1, GL_FALSE, m_useCamera->m_projectionMatrix );
// 
// 					// PROJECTION VIEW
// 						m_ProjectionViewMatrix = m_useCamera->m_ProjectionMatrix * m_useCamera->m_ViewMatrix;
// 						m_ProjectionViewMatrix.getOpenGLMatrix( m_ViewModelBuffer );
// 						glUniformMatrix4fv( m_ProjectionViewMatrixID, 1, GL_FALSE, m_ViewModelBuffer );
// 
// 					// PROJECTION VIEW MODEL
// 						m_ProjectionViewModelMatrix = m_ProjectionViewMatrix * m_ModelMatrix;
// 						m_ProjectionViewModelMatrix.getOpenGLMatrix( m_ViewModelBuffer );
// 						glUniformMatrix4fv( m_ProjectionViewModelMatrixID, 1, GL_FALSE, m_ViewModelBuffer );

					// SCALE
						scale( t->m_scale_x->get_float(), t->m_scale_y->get_float(), t->m_scale_z->get_float() );

					// DRAW
					// 		std::cout << "BeGraphicsModel::draw():: " << std::endl;
							draw( getModel()->get() );
							// getModel()->get()->draw();
					
					found_child = true;
				}
			}

			// just draw it once on 0,0,0 if we did not find a child above, basically a skybox hack
			if ( !found_child )
			{
				scale( 1.0f, 1.0f, 1.0f );
				draw( getModel()->get() );
				// getModel()->get()->draw();
			}
		}
	}

	void BGraphicsModel::processWhenInSight( const btTransform* transformHead, float sightrange )	
	{
		if ( name() == "GraphicsModel_SkyDome" )
		{
			return;
		}

		// FIXME add a bool "update_instanced_vector" so we only update vector all once  per frame (important when crittervision is implemented)
		if( getModel() && getModel()->isReady() )
		{
			// FORCES THE SCALE UNIFORM UPLOAD
			// m_ScaleBuffer[0] = 0.0f;
			
			bool always_render(false);
			if ( name() == "graphics_entity_map" )
			{
				always_render = true;
			}

			// SET COLOR HACK
			const auto& ambient = getModel()->get()->matlist.begin()->second.m_material.getAmbient();
			// glUniform4f( m_color_location, ambient.x(), ambient.y(), ambient.z(), 1.0f );
			m_uniform_color->setValue( ambient.x(), ambient.y(), ambient.z(), 1.0f );

			bool found_child(false);
			btVector3 position = transformHead->getOrigin();
			btVector3 positionB;
			for_all_children
			{
				auto t = dynamic_cast<glTransform*>(*child);
				if ( (t) )
				{
					positionB = btVector3( t->m_value[12], t->m_value[13], t->m_value[14] );
					
					// check if position is in vicinity of mouth
					if ( always_render || position.distance( positionB ) < sightrange )
					{
						// check if position is in front of mouth
						positionB -=  position;
						positionB.normalize();

						// dot of forwardVector
						if( always_render || positionB.dot( btVector3( transformHead->getBasis()[0][2], transformHead->getBasis()[1][2], transformHead->getBasis()[2][2] ) ) >= 0.5 )
						{
							// std::cout << "  drawing : " << t->name() << std::endl;

							// MODEL MATRIX
								glUniformMatrix4fv( m_ModelMatrixID, 1, GL_FALSE, t->m_value );

							// SCALE
								scale( t->m_scale_x->get_float(), t->m_scale_y->get_float(), t->m_scale_z->get_float() );

							// DRAW
								draw( getModel()->get(), false );
								// getModel()->get()->draw();
						}
						// else
						// {
							// std::cout << "skip" << std::endl;
						// }
					}
					found_child = true;
				}
			}

			// just draw it once on 0,0,0 if we did not find a child above, basically a skybox hack
			if ( !found_child )
			{
				draw( getModel()->get() );
				// getModel()->get()->draw();
			}
		}
	}	

	void BGraphicsModel::scale( const float x, const float y, const float z )
	{
		if ( x != m_scale_x_current->get_float() || y != m_scale_y_current->get_float() || z != m_scale_z_current->get_float() )
		{
			m_ScaleBuffer[0] = x;
			m_ScaleBuffer[5] = y;
			m_ScaleBuffer[10] = z;

			m_scale_x_current->set( x );
			m_scale_y_current->set( y );
			m_scale_z_current->set( z );

			glUniformMatrix4fv( m_scale_location, 1, GL_FALSE, m_ScaleBuffer );
			// std::cout << " DO";
		}
		// else
		// {
		// 	std::cout << " SKIP";
		// }
	}
	
	void BGraphicsModel::draw( boost::shared_ptr<BeGraphicsModel> model, bool doTextures )
	{
		glBindVertexArray(model->m_vertexArray.get() ? model->m_vertexArray.get()->handle() : 0);

		if ( model->matlist.size() > 0 )
		{
			// glEnable(GL_TEXTURE_2D);
			
			BeGraphicsMaterial* material;
			auto it = model->matlist.begin();
			
			size_t minPriority=0;
			size_t maxPriority=0;

			while( it != model->matlist.end() )
			{
				size_t priority = 0;
				material = model->m_system->getEffect( (*it).first );
				if ( material )
				{
					priority = material->getPriority();
				}
				if( priority < minPriority )
					minPriority = priority;
				if( priority > maxPriority )
					maxPriority = priority;

				++it;
			}

			for( size_t priority = minPriority; priority <= maxPriority; ++priority )
			{
				size_t i = 0;
				it = model->matlist.begin();
				while( it != model->matlist.end() )
				{
					size_t pr = 0;
					// // bool sort = false; 
					// int depthMask=1;
					// int depthTest=1;
					// int blend = 0;
					material = model->m_system->getEffect( (*it).first );
					if ( material )
					{
						// // sort = material->getSort();
						pr = (int)material->getPriority();
						// depthMask = material->getDepthMask();
						// depthTest = material->getDepthTest();
						// blend = material->getBlend();
					}

					if( pr == priority )
					{
// 						// // DEPTH AND BLEND, COMMENTED OUT FOR CRITTERDING PERFORMANCE
// 						// DEPTH
// 							glDepthMask( depthMask );
// 							if ( depthTest )
// 							{
// 								// std::cout << "dt+";
// 								glEnable(GL_DEPTH_TEST);
// 							}
// 							else
// 							{
// 								// std::cout << "dt-";
// 								glDisable(GL_DEPTH_TEST);
// 							}
// 						
// 						// BLEND
// 							if ( blend )
// 							{
// 								if ( !m_draw_blend_is_disabled )
// 								{
// 									// std::cout << "bl+";
// 									glEnable(GL_BLEND);
// 									glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
// 									m_draw_blend_is_disabled = false;
// 								}
// 							}
// 							else
// 							{
// 								if ( m_draw_blend_is_disabled )
// 								{
// 									// std::cout << "bl-";
// 									glDisable(GL_BLEND);
// 									glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
// 									m_draw_blend_is_disabled = true;
// 								}
// 							}

						if ( doTextures == true )
						{
							const Material& material = (*it).second;

							if ( material.m_imageTexture2D != 0 )
							{
								if ( material.m_imageTexture2D->get().get() )
								{
									glBindTexture(GL_TEXTURE_2D, material.m_imageTexture2D->get().get()->handle());
									m_uniform_textureSample->set( 1 );
									// glUniform1i( m_textureSample_location, 1 );
								}
							}
							else
							{
								glBindTexture(GL_TEXTURE_2D, 0); // THINK IT'S OK TO COMMENT THIS?
								m_uniform_textureSample->set( 0 );
								// glUniform1i( m_textureSample_location, 0 );
							}
						}
						else
						{
							glBindTexture(GL_TEXTURE_2D, 0);
							m_uniform_textureSample->set( 0 );
							// glUniform1i( m_textureSample_location, 0 );
						}

						// // SPECIFIC MATERIALS, COMMENTED OUT FOR CRITTERDING PERFORMANCE
						// {
						// 	const auto& ambient = material.m_material.getAmbient();
						// 	const float f_a[4] = { ambient.x(), ambient.y(), ambient.z(), 1.0f };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, f_a );
						// }
						// {
						// 	const auto& diffuse = material.m_material.getDiffuse();
						// 	const float f_d[4] = { diffuse.x(), diffuse.y(), diffuse.z(), 1.0f };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, f_d );
						// }
						// {
						// 	const auto& specular = material.m_material.getSpecular();
						// 	const float f_s[4] = { specular.x(), specular.y(), specular.z(), 1.0f };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, f_s );
						// }
						// {
						// 	const auto& emission = material.m_material.getEmission();
						// 	const float f_s[4] = { emission.x(), emission.y(), emission.z(), 1.0f };
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, f_s );
						// }
						// {
						// 	const auto& shininess = material.m_material.getShininess();
						// 	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, &shininess );
						// }

						auto& drawCall = model->m_drawCalls[i];
						glDrawElements( GL_TRIANGLES, drawCall.m_count, GL_UNSIGNED_INT, (char *)NULL + ((drawCall.m_first)*sizeof(GLint)) );
					}

					++it;
					++i;
				}

			}
			// glDisable(GL_TEXTURE_2D);
		}
		else
		{
	// 		m_graphicsSystem.bindTexture2D(0);
			//m_graphicsSystem.applyMaterial(GL_FRONT_AND_BACK, 0);

			glDrawElements(GL_TRIANGLES, model->elementArrayBuffer.size(), GL_UNSIGNED_INT, NULL);
		}

		glBindVertexArray(0);
	}
	
	
	const char* BGraphicsModel::get_string( const Bstring& id )
	{
		if ( id == "filename" )
		{
			return m_loaded_path.c_str();
		}
		return 0;
	}

	bool BGraphicsModel::set( const Bstring& id, const char* value )
	// bool BGraphicsModel::setProperty( const std::string& caller_name, const std::string& value, const bool do_update )
	{
		if ( id == "filename" && m_loaded_path != value )
		{
	//	std::cout << "PATH CALLED!!!!!!!!!!!!!" << std::endl;
			btVector3 scale( m_pre_scale_x->get_float(), m_pre_scale_y->get_float(), m_pre_scale_z->get_float() );
			// btTransform transform;
			// transform.setIdentity();

			// FIXME REMOVE THIS BY MAKING IT A TRANSFORM BY DEFAULT
			btTransform geometry_transform;
			geometry_transform.setIdentity();
			geometry_transform.setOrigin( btVector3( m_pre_position_x->get_float(), m_pre_position_y->get_float(), m_pre_position_z->get_float() ) );
			geometry_transform.getBasis().setEulerZYX( m_pre_rotation_x->get_float(), m_pre_rotation_y->get_float(), m_pre_rotation_z->get_float() );

			
			
			BGraphicsModelSystem* scene = dynamic_cast<BGraphicsModelSystem*>(parent());
			if ( scene )
			{
				boost::shared_ptr<BeGraphicsModelResource> new_model( scene->load(value, scene->m_graphicsSystem, scene, scale, geometry_transform) );
				if ( new_model )
				{
					setModel( new_model );
					m_loaded_path = value;
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
	// 						m_loaded_path = value;
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
			// Assume that transformMatrix is a float array of size 16 that contains the transform matrix
			// float x = transformMatrix[12]; // Extract the x-coordinate from the last column, first row
			// float y = transformMatrix[13]; // Extract the y-coordinate from the last column, second row
			// float z = transformMatrix[14]; // Extract the z-coordinate from the last column, third row			
			
			addChild( "position_x", new BEntity_float_property() );
			addChild( "position_y", new BEntity_float_property() );
			addChild( "position_z", new BEntity_float_property() );
			addChild( "rotation_euler_x", new BEntity_float_property() );
			addChild( "rotation_euler_y", new BEntity_float_property() );
			addChild( "rotation_euler_z", new BEntity_float_property() );

			m_scale_x = addChild( "scale_x", new BEntity_float() );
			m_scale_y = addChild( "scale_y", new BEntity_float() );
			m_scale_z = addChild( "scale_z", new BEntity_float() );
			m_scale_x->set( 1.0f );
			m_scale_y->set( 1.0f );
			m_scale_z->set( 1.0f );

		}

		
	bool glTransform::set( const Bstring& id, const Bfloat& value )
	{
		
		if ( id == "position_x" )
		{
			if ( m_value[12] != value )
			{
				m_value[12] = value;
				onUpdate();
				return true;
			}
		}
		else if ( id == "position_y" )
		{
			if ( m_value[13] != value )
			{
				m_value[13] = value;
				onUpdate();
				return true;
			}
		}
		else if ( id == "position_z" )
		{
			if ( m_value[14] != value )
			{
				m_value[14] = value;
				onUpdate();
				return true;
			}
		}
		
		else if ( id == "rotation_euler_x" )
		{
			// Assume that the existing transform matrix is stored in a float array called "transformMatrix" of size 16
			// Also assume that the new rotation angles around x, y, and z axes are stored in variables "angleX", "angleY", and "angleZ" (in radians)
			auto x = get_float( "rotation_euler_x" );
			auto y = get_float( "rotation_euler_y" );
			auto z = get_float( "rotation_euler_z" );

			// set identity on our matrix first;
			m_value[0] = 1.0f;
			m_value[1] = 0.0f;
			m_value[2] = 0.0f;
			m_value[4] = 0.0f;
			m_value[5] = 1.0f;
			m_value[6] = 0.0f;
			m_value[8] = 0.0f;
			m_value[9] = 0.0f;
			m_value[10] = 1.0f;			

			float cosX = cos( value );
			float sinX = sin( value );
			float cosY = cos( y );
			float sinY = sin( y );
			float cosZ = cos( z );
			float sinZ = sin( z );

			// Create a rotation matrix for each axis
			float rotX[16] = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cosX, -sinX, 0.0f,
				0.0f, sinX, cosX, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float rotY[16] = {
				cosY, 0.0f, sinY, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sinY, 0.0f, cosY, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float rotZ[16] = {
				cosZ, -sinZ, 0.0f, 0.0f,
				sinZ, cosZ, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			// Compose the new rotation matrix by multiplying the rotation matrices for each axis
			float newRotationMatrix[16];
			memcpy(newRotationMatrix, rotX, sizeof(float) * 16);
			matMul(newRotationMatrix, rotY);
			matMul(newRotationMatrix, rotZ);

			// Multiply the new rotation matrix with the existing transform matrix to get the updated transform matrix
			matMul(m_value, newRotationMatrix);
			return true;

		}
		else if ( id == "rotation_euler_y" )
		{
			// Assume that the existing transform matrix is stored in a float array called "transformMatrix" of size 16
			// Also assume that the new rotation angles around x, y, and z axes are stored in variables "angleX", "angleY", and "angleZ" (in radians)
			auto x = get_float( "rotation_euler_x" );
			auto y = get_float( "rotation_euler_y" );
			auto z = get_float( "rotation_euler_z" );

			// set identity on our matrix first;
			m_value[0] = 1.0f;
			m_value[1] = 0.0f;
			m_value[2] = 0.0f;
			m_value[4] = 0.0f;
			m_value[5] = 1.0f;
			m_value[6] = 0.0f;
			m_value[8] = 0.0f;
			m_value[9] = 0.0f;
			m_value[10] = 1.0f;

			float cosX = cos( x );
			float sinX = sin( x );
			float cosY = cos( value );
			float sinY = sin( value );
			float cosZ = cos( z );
			float sinZ = sin( z );

			// Create a rotation matrix for each axis
			float rotX[16] = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cosX, -sinX, 0.0f,
				0.0f, sinX, cosX, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float rotY[16] = {
				cosY, 0.0f, sinY, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sinY, 0.0f, cosY, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float rotZ[16] = {
				cosZ, -sinZ, 0.0f, 0.0f,
				sinZ, cosZ, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			// Compose the new rotation matrix by multiplying the rotation matrices for each axis
			float newRotationMatrix[16];
			memcpy(newRotationMatrix, rotX, sizeof(float) * 16);
			matMul(newRotationMatrix, rotY);
			matMul(newRotationMatrix, rotZ);

			// Multiply the new rotation matrix with the existing transform matrix to get the updated transform matrix
			matMul(m_value, newRotationMatrix);
			return true;
		}
		else if ( id == "rotation_euler_z" )
		{
			// Assume that the existing transform matrix is stored in a float array called "transformMatrix" of size 16
			// Also assume that the new rotation angles around x, y, and z axes are stored in variables "angleX", "angleY", and "angleZ" (in radians)
			auto x = get_float( "rotation_euler_x" );
			auto y = get_float( "rotation_euler_y" );
			auto z = get_float( "rotation_euler_z" );

			// set identity on our matrix first;
			m_value[0] = 1.0f;
			m_value[1] = 0.0f;
			m_value[2] = 0.0f;
			m_value[4] = 0.0f;
			m_value[5] = 1.0f;
			m_value[6] = 0.0f;
			m_value[8] = 0.0f;
			m_value[9] = 0.0f;
			m_value[10] = 1.0f;

			float cosX = cos( x );
			float sinX = sin( x );
			float cosY = cos( y );
			float sinY = sin( y );
			float cosZ = cos( value );
			float sinZ = sin( value );

			// Create a rotation matrix for each axis
			float rotX[16] = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cosX, -sinX, 0.0f,
				0.0f, sinX, cosX, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float rotY[16] = {
				cosY, 0.0f, sinY, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sinY, 0.0f, cosY, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			float rotZ[16] = {
				cosZ, -sinZ, 0.0f, 0.0f,
				sinZ, cosZ, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};

			// Compose the new rotation matrix by multiplying the rotation matrices for each axis
			float newRotationMatrix[16];
			memcpy(newRotationMatrix, rotX, sizeof(float) * 16);
			matMul(newRotationMatrix, rotY);
			matMul(newRotationMatrix, rotZ);

			// Multiply the new rotation matrix with the existing transform matrix to get the updated transform matrix
			matMul(m_value, newRotationMatrix);
			return true;
		}

		return false;
	}

	void glTransform::matMul(float* a, float* b)
	{
		float result[16];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result[i*4 + j] = 0.0f;
				for (int k = 0; k < 4; k++) {
					result[i*4 + j] += a[i*4 + k] * b[k*4 + j];
				}
			}
		}
		memcpy(a, result, sizeof(float) * 16);
	}
	
	Bfloat glTransform::get_float( const Bstring& id )
	{
		if ( id == "position_x" )
		{
			return m_value[12];
		}
		else if ( id == "position_y" )
		{
			return m_value[13];
		}
		else if ( id == "position_z" )
		{
			return m_value[14];
		}
		else if ( id == "rotation_euler_x" )
		{
			// Calculate the rotation for x
			float sinX = m_value[9];
			if (sinX >= 1.0f) {
				// Special case: if sin(x) is 1, then x = 90 degrees and cos(x) = 0
				return M_PI / 2.0f; // x is in radians
			}
			else if (sinX <= -1.0f) {
				// Special case: if sin(x) is -1, then x = -90 degrees and cos(x) = 0
				return -M_PI / 2.0f; // x is in radians
			}
			else {
				// General case
				return asin(sinX);
			}
   // 
			// float sx, sy, sz;
			// sy = asinf(m_value[8]);
			// if (sy < M_PI / 2) {
			// 	if (sy > -M_PI / 2) {
			// 		sx = atan2f(-m_value[9], m_value[10]);
			// 		sz = atan2f(-m_value[4], m_value[0]);
			// 	} else {
			// 		sx = -atan2f(m_value[6], m_value[5]);
			// 		sz = 0;
			// 	}
			// } else {
			// 	sx = atan2f(m_value[6], m_value[5]);
			// 	sz = 0;
			// }
			// return sx;
		}
		else if ( id == "rotation_euler_y" )
		{
			// Calculate the rotation for y
			float sinY = -m_value[8];
			float cosY = m_value[10];
			return atan2(sinY, cosY);

			// float sx, sy, sz;
			// sy = asinf(m_value[8]);
			// if (sy < M_PI / 2) {
			// 	if (sy > -M_PI / 2) {
			// 		sx = atan2f(-m_value[9], m_value[10]);
			// 		sz = atan2f(-m_value[4], m_value[0]);
			// 	} else {
			// 		sx = -atan2f(m_value[6], m_value[5]);
			// 		sz = 0;
			// 	}
			// } else {
			// 	sx = atan2f(m_value[6], m_value[5]);
			// 	sz = 0;
			// }
			// return sy;
		}
		else if ( id == "rotation_euler_z" )
		{
			// Calculate the rotation for z
			float sinZ = m_value[4];
			if (sinZ >= 1.0f) {
				// Special case: if sin(z) is 1, then z = 90 degrees and cos(z) = 0
				return M_PI / 2.0f; // z is in radians
			}
			else if (sinZ <= -1.0f) {
				// Special case: if sin(z) is -1, then z = -90 degrees and cos(z) = 0
				return -M_PI / 2.0f; // z is in radians
			}
			else {
				// General case
				return asin(sinZ);
			}

			// float sx, sy, sz;
			// sy = asinf(m_value[8]);
			// if (sy < M_PI / 2) {
			// 	if (sy > -M_PI / 2) {
			// 		sx = atan2f(-m_value[9], m_value[10]);
			// 		sz = atan2f(-m_value[4], m_value[0]);
			// 	} else {
			// 		sx = -atan2f(m_value[6], m_value[5]);
			// 		sz = 0;
			// 	}
			// } else {
			// 	sx = atan2f(m_value[6], m_value[5]);
			// 	sz = 0;
			// }
			// return sz;
		}
		return 0.0f;
	}
		
		bool glTransform::apply( BEntity* e )
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
