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

		// SHADERS
		std::cout << "loading shaders" << std::endl;
// 		m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine-new/share/sandbox/shaders/crittervision_new.vert", "/projects/bengine-new/share/sandbox/shaders/crittervision_new.frag"));
		// m_effect.reset(new BeGraphicsEffect(m_filesystem, "/projects/bengine3/share/instancing.vert", "/projects/bengine3/share/instancing.frag"));
		m_effect.reset(new BeGraphicsEffect(m_filesystem, "../share/vertex_shader.glsl", "../share/fragment_shader.glsl"));
		m_effect_critter.reset(new BeGraphicsEffect(m_filesystem, "../share/vertex_shader_critter.glsl", "../share/fragment_shader_critter.glsl"));
		// {
		// 	glUseProgram( m_effect_critter->m_program.get()->handle() );
		// }
	}
	
	void BGraphicsModelSystem::construct()
	{
		addChild("active", "bool" )->set( true );
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
 
