#include "be_entity_graphics_model_system.h"
#include "be_graphics_model_resource.h"
#include "be_worker_pool.h"
#include "be_texture_store.h"
#include "graphics/be_graphics_system.h"
#include "math/vector4f.h"
#include "graphics/be_shader.h"

	BGraphicsModelSystem::BGraphicsModelSystem() // FIXME move to cpp
	: BEntity()
	{
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

// 		glewInit();
// 
// 		// SHADERS
// // 		m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine-new/share/sandbox/shaders/crittervision_new.vert", "/projects/bengine-new/share/sandbox/shaders/crittervision_new.frag"));
// 		// m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine3/share/instancing.vert", "/projects/bengine3/share/instancing.frag"));
// 		m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine3/share/vertex_shader.glsl", "/projects/bengine3/share/fragment_shader.glsl"));
// 		{
// 			glUseProgram( m_effect->m_program.get()->handle() );
// 		}
// 
// 		
// 		// SETUP OPENGL
// 		if ( 1 == 1 )
// 		{
// 			//Hint for everything to be nicest
// 			m_graphicsSystem->hint(GL_FOG_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_LINE_SMOOTH_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_POINT_SMOOTH_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
// 			m_graphicsSystem->hint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);
// 
// 			//Smooth shading
// 			m_graphicsSystem->shadeModel(GL_SMOOTH);
// 
// 			//Enable back face culling
// 			m_graphicsSystem->enable(GL_CULL_FACE);
// 			m_graphicsSystem->cullFace(GL_BACK);
// 
// 			//Enable depth test
// 			m_graphicsSystem->enable(GL_DEPTH_TEST);
// 
// 			//Alpha blending
// 			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 			glEnable (GL_BLEND); 
// 
// 			glEnable ( GL_ALPHA_TEST );
// 			glAlphaFunc ( GL_GREATER, 0.5f ) ;
// 
// 			//Set default light model settings
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_AMBIENT, Vector4f(0.5f, 0.5f, 0.5f, 1.0f));
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
// 			m_graphicsSystem->lightModel(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
// 
// 			// Set one directional light by default
// 				// BeDirectionalLight light;
// 				// light.setDirection(Vector3f(1,1,0));
// 				// light.setSpecular(Vector4f(1,1,1,1));
// 				// m_graphicsSystem->applyLight(GL_LIGHT0, &light);
// 		
// 			//Set the default material
// 			m_graphicsSystem->applyMaterial(GL_FRONT_AND_BACK, 0);
// 
// 			//Disable lighting
// 			m_graphicsSystem->disable(GL_LIGHTING);
// 
// 			//Set default matrices
// 			m_graphicsSystem->matrixLoadIdentity(GL_PROJECTION);
// 			m_graphicsSystem->matrixLoadIdentity(GL_MODELVIEW);
// 		}
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
 
