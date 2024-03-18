#pragma once

#include "kernel/be_entity_interface.h"
#include "filesystem/be_filesystem.h"
#include <boost/shared_ptr.hpp>
// #include "LinearMath/btTransform.h"
#include "be_model_system.h"
#include <glm/gtc/type_ptr.hpp>

	class BeGraphicsModelResource;
	class BeWorkerPool;
	class Texturestore;
	class BeGraphicsSystem;

	class BGraphicsModelSystem : public BEntity
	{
		friend class BeGraphicsModelResource;
		public:
			BGraphicsModelSystem();
			virtual ~BGraphicsModelSystem();

			void construct();
			void process();

			boost::shared_ptr<BeGraphicsModelResource> load( const std::string& filename, boost::shared_ptr<BeGraphicsSystem> graphicsSystem, BGraphicsModelSystem* instance, const btVector3& scale, const btTransform& transform );
			boost::shared_ptr<BeGraphicsSystem> m_graphicsSystem;
			boost::shared_ptr<BeGraphicsEffect> m_effect;
			boost::shared_ptr<BeGraphicsEffect> m_effect_critter;
			boost::shared_ptr<BeGraphicsEffect> m_effect_depthmap;

			// depthmap viewer
			boost::shared_ptr<BeGraphicsEffect> m_effect_depthmap_viewer;

			GLuint depthMap;
		private:
			BeFilesystem m_filesystem;
			boost::shared_ptr<BeWorkerPool> m_workerPool;
			Texturestore* m_textureStore;
			BEntity* m_active;
	// 		typedef std::unordered_map<std::string, boost::shared_ptr<BeGraphicsModelResource> > ResourceMap;
	// 		ResourceMap m_resources;
			GLuint depthMapFBO;
			GLuint m_lightSpaceMatrixID;
			GLuint m_lightSpaceMatrixID_depthmap;
			glm::mat4 m_lightSpaceMatrix;
			BEntity* m_skyDome;
			
			unsigned int m_depth_map_resolution_x;
			unsigned int m_depth_map_resolution_y;
		
			// depthmap viewer
			GLuint VAO;
			GLuint VBO;
	}; 

