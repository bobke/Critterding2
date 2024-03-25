#include "be_entity_graphics_model_system.h"
#include "be_graphics_model_resource.h"
#include "be_worker_pool.h"
#include "be_texture_store.h"
#include "graphics/be_graphics_system.h"
#include "math/vector4f.h"
#include "graphics/be_shader.h"
#include "be_entity_graphics_model.h"

	BGraphicsModelSystem::BGraphicsModelSystem()
	: BEntity()
	{
		setProcessing();

		m_graphicsSystem = boost::shared_ptr<BeGraphicsSystem>(new BeGraphicsSystem);

		// threads
			unsigned hardwareConcurrency = 0;
			// 0 : autodetect
			if ( hardwareConcurrency == 0 )
			{
				hardwareConcurrency = boost::thread::hardware_concurrency();
				// logDebug << "::WORKERPOOL threads " << hardwareConcurrency << "\n";
			}
		
		m_workerPool = boost::shared_ptr<BeWorkerPool>(new BeWorkerPool(hardwareConcurrency));
		m_textureStore = new Texturestore(m_workerPool);

		// SHADERS
		std::cout << "loading shaders" << std::endl;
// 		m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine-new/share/sandbox/shaders/crittervision_new.vert", "/projects/bengine-new/share/sandbox/shaders/crittervision_new.frag"));
		// m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine3/share/instancing.vert", "/projects/bengine3/share/instancing.frag"));
		m_effect.reset(new BeGraphicsEffect(m_filesystem, "../share/vertex_shader.glsl", "../share/fragment_shader.glsl"));
		m_effect_critter.reset(new BeGraphicsEffect(m_filesystem, "../share/vertex_shader_critter.glsl", "../share/fragment_shader_critter.glsl"));
		m_effect_depthmap.reset(new BeGraphicsEffect(m_filesystem, "../share/vertex_depthmap.glsl", "../share/fragment_depthmap.glsl"));
		m_effect_depthmap_viewer.reset(new BeGraphicsEffect(m_filesystem, "../share/vertex_depthmap_viewer.glsl", "../share/fragment_depthmap_viewer.glsl"));
		// {
		// 	glUseProgram( m_effect_critter->m_program.get()->handle() );
		// }
	}
	
	void BGraphicsModelSystem::construct()
	{
		m_active = addChild("active", "bool" );
		m_active->set( true );
		
		// SHADOWS SETUP
			// Set up the depth map framebuffer
			glGenFramebuffers(1, &depthMapFBO);

			m_depth_map_resolution_x = 2048;
			m_depth_map_resolution_y = 2048;

			// Set up the depth map texture
			glGenTextures(1, &depthMap);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_depth_map_resolution_x, m_depth_map_resolution_y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

			// GLfloat borderColor[] = {1.0, 1.0, 1.0, 1.0};
			// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
			
			// Attach depth texture as FBO's depth buffer
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);  

			// Set up the light's view and projection matrices
			// glm::mat4 lightProjection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
			
			// m_lightSpaceMatrixID = glGetUniformLocation(  m_effect->m_program.get()->handle(), "lightSpaceMatrix" );
			// glUniformMatrix4fv(m_lightSpaceMatrixID, 1, GL_FALSE, glm::value_ptr(m_lightSpaceMatrix));
			
			const float scale_x(106.0f);
			const float scale_y(81.0f);
			glm::mat4 lightProjection = glm::ortho(-scale_x, scale_x, -scale_y, scale_y, 65.0f, 80.0f);
			glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 50.0f, -100.0f), glm::vec3(0.0f, 0.0f, -100.01f), glm::vec3(0.0f, 1.0f, 0.0f));
			
			// glm::mat4 lightProjection = glm::perspective( SIMD_PI / 4, 1.0f, 65.0f, 80.0f );
			// glm::mat4 lightView = glm::mat4(1.0f);
			// lightView = glm::translate(lightView, glm::vec3(0.0f, 50.0f, 0.0f));
			// lightView = (glm::rotate(lightView, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

			// glm::mat4 lightView = (m_base_transform->m_transform * m_transform->m_transform).inverse();
			// m_ViewMatrix.getOpenGLMatrix( m_viewMatrix );
			
			m_lightSpaceMatrix = lightProjection * lightView;
			
			m_lightSpaceMatrixID_depthmap = glGetUniformLocation(  m_effect_depthmap->m_program.get()->handle(), "lightSpaceMatrix" );
			m_lightSpaceMatrixID = glGetUniformLocation(  m_effect->m_program.get()->handle(), "lightSpaceMatrix" );

			m_skyDome = 0;
	
	}
	
	void BGraphicsModelSystem::process()
	{
		if ( m_active->get_bool() )
		{
			if ( !m_skyDome )
			{
				m_skyDome = getChild("GraphicsModel_SkyDome", 1);
			}

			glUseProgram( m_effect_depthmap->m_program.get()->handle() );

			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glViewport(0, 0, m_depth_map_resolution_x, m_depth_map_resolution_y);
			glClear(GL_DEPTH_BUFFER_BIT);
			
			// SHADOWS: render to depthmap
			glUniformMatrix4fv(m_lightSpaceMatrixID_depthmap, 1, GL_FALSE, glm::value_ptr(m_lightSpaceMatrix));

				for_all_children
				{
					if (  (*child) != m_skyDome )
					{
						auto model = dynamic_cast<BGraphicsModel*>( (*child) );
						if ( model )
						{
							model->m_render_to_depth = true; // FIXME REMOVE
							model->process();
							model->m_render_to_depth = false;
						}
					}
				}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			// SWITCH TO NORMAL SHADER
			glUseProgram( m_effect->m_program.get()->handle() );
			glUniformMatrix4fv(m_lightSpaceMatrixID, 1, GL_FALSE, glm::value_ptr(m_lightSpaceMatrix));
			
			glUniform1i(glGetUniformLocation(m_effect->m_program.get()->handle(), "depthMap"), 1); // Assuming you use texture unit 0 for the depth map
			// Bind the depth map texture
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			glActiveTexture(GL_TEXTURE0);
		}
	}
	
	BGraphicsModelSystem::~BGraphicsModelSystem()
	{
		delete m_textureStore;
	};

	boost::shared_ptr<BeGraphicsModelResource> BGraphicsModelSystem::load(const std::string& filename, boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BGraphicsModelSystem* instance, const btVector3& scale, const btTransform& transform)
	{
	// 	// account for scale and transform
	// 	btScalar rotX, rotY, rotZ;
	// 	transform.getBasis().getEulerZYX(rotX, rotY, rotZ);
	// 	std::stringstream sscacheName;
	// 	sscacheName << filename << scale.x() << scale.y() << scale.z();
	// 	sscacheName << transform.getOrigin().getX() << transform.getOrigin().getY() << transform.getOrigin().getZ();
	// 	sscacheName << rotX << rotY << rotZ;
	// 
	// 	std::string cacheName(sscacheName.str());
	// 	if ( m_resources[cacheName] )
	// 	{
	// 		return m_resources[cacheName];
	// 	}
	// 	else
		{
			boost::shared_ptr<BeGraphicsModelResource> m(new BeGraphicsModelResource( m_filesystem, m_workerPool, filename, graphicsSystem, instance, scale, transform ));
	// 		m_resources[cacheName]=m;
			return m;
		}
	}
 
